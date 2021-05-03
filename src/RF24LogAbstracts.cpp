/**
 * @file RF24LogAbstracts.cpp
 * @date Created 2 Oct 2020
 * @author Witold Markowski (wmarkow)
 * @copyright Copyright (C)
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include <RF24LogAbstracts.h>
#ifdef ARDUINO
#include <Arduino.h> // isAlpha()
#define isalpha(c) isAlpha(c)
#else
#include <cctype> // isalpha()
#endif

/* *************************** Abstract global function defs **************************** */

uint16_t howWide(int64_t numb, uint8_t base)
{
    int64_t mask = (numb < 0 ? numb * -1 : numb);
    uint16_t i = 0;
    while (mask)
    {
        if (base == 2)
        {
            mask >>= 1;
        }
        else if (base == 8)
        {
            mask >>= 3;
        }
        else if (base == 16)
        {
            mask >>= 4;
        }
        else // assume base is default value of 10
        {
            mask /= 10;
        }
        i++;
    }
    if (numb <= 0)
    {
        i += 1 + (bool)numb; // compensate for the negative sign (and zero char)
    }
    return i;
}

/* *************************** AbstractHandler defs **************************** */

RF24LogAbstractHandler::RF24LogAbstractHandler()
{
    this->logLevel = RF24LogLevel::INFO;
}

void RF24LogAbstractHandler::log(uint8_t logLevel,
                                 const char *vendorId,
                                 const char *message,
                                 va_list *args)
{
    if (isLevelEnabled(logLevel))
    {
        write(logLevel, vendorId, message, args);
    }
}

void RF24LogAbstractHandler::setLogLevel(uint8_t logLevel)
{
    this->logLevel = logLevel;
}

bool RF24LogAbstractHandler::isLevelEnabled(uint8_t logLevel)
{
    return logLevel <= this->logLevel;
}

#if defined (ARDUINO_ARCH_AVR)
void RF24LogAbstractHandler::log(uint8_t logLevel,
                                 const __FlashStringHelper *vendorId,
                                 const __FlashStringHelper *message,
                                 va_list *args)
{
    if (isLevelEnabled(logLevel))
    {
        write(logLevel, vendorId, message, args);
    }
}

void RF24LogPrintfParser::write(uint8_t logLevel,
                               const __FlashStringHelper *vendorId,
                               const __FlashStringHelper *message,
                               va_list *args)
{
    PGM_P p = reinterpret_cast<PGM_P>(message);
    char c = pgm_read_byte(p++);
    while (c)
    {
        // print header
        descTimeLevel(logLevel);
        appendStr(vendorId);
        appendChar(RF24LOG_DELIMITER);

        // print formatted message (or at least 1 line at a time)
        while (c != 0 && c !='\n')
        {
            if (c == '\t')
            {
                appendChar(' ', 8);
            }
            else if (c == '%')
            {
                SpecifierParsing fmt_parser;
                c = pgm_read_byte(p++); // get ready to feed the parser
                while (c && fmt_parser.isFlagged(c)) { c = pgm_read_byte(p++); }
                while (c && fmt_parser.isPaddPrec(c)) { c = pgm_read_byte(p++); }
                while (c && fmt_parser.isFmtOption(c)) { c = pgm_read_byte(p++); }
                if (fmt_parser.specifier)
                {
                    appendFormat(&fmt_parser, args);
                    // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char only
                    // if the `while(isFmtOption())` loop above iterated more than once, then
                    // we have to prevent disposing of the left over char here
                    if (fmt_parser.specifier != c)
                    {
                        p--; // let the next iteration handle it
                    }
                }
                else
                {
                    appendChar(c);
                }
            }
            else
            {
                appendChar(c);
            }
            c = pgm_read_byte(p++);
        }
        if (c == '\n')
        {
            c = pgm_read_byte(p++); // dispose char; we control the new line feeds ourselves
        }
        #ifndef RF24LOG_NO_EOL
        appendChar('\n');
        #endif
    }
}
#endif

void RF24LogPrintfParser::write(uint8_t logLevel,
                               const char *vendorId,
                               const char *message,
                               va_list *args)
{
    char *c = (char*)message;
    while (*c)
    {
        // print header
        descTimeLevel(logLevel);
        appendStr(vendorId);
        appendChar(RF24LOG_DELIMITER);

        // print formatted message (or at least 1 line at a time)
        while (*c != 0 && *c !='\n')
        {
            if (*c == '\t')
            {
                appendChar(' ', 8);
            }
            else if (*c == '%')
            {
                SpecifierParsing fmt_parser;
                ++c; // get ready to feed the parser
                while (fmt_parser.isFlagged(*c)) { ++c; }
                while (fmt_parser.isPaddPrec(*c)) { ++c; }
                while (fmt_parser.isFmtOption(*c)) { ++c; }
                // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char
                if (fmt_parser.specifier)
                {
                    appendFormat(&fmt_parser, args);
                    // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char only
                    // if the `while(isFmtOption())` loop above iterated more than once, then
                    // we have to prevent disposing of the left over char here
                    if (fmt_parser.specifier != *c)
                    {
                        --c; // let the next iteration handle it
                    }
                }
                else
                {
                    appendChar(*c);
                }
            }
            else
            {
                appendChar(*c);
            }
            ++c;
        }
        if (*c == '\n')
        {
            ++c; // dispose char; we control the new line feeds ourselves
        }
        #ifndef RF24LOG_NO_EOL
        appendChar('\n');
        #endif
    }
}

/* *************************** AbstractStream defs **************************** */

void RF24LogAbstractStream::descTimeLevel(uint8_t logLevel)
{
    #ifndef RF24LOG_NO_TIMESTAMP
    appendTimestamp();
    #endif
    appendLogLevel(logLevel);
}

void RF24LogAbstractStream::appendLogLevel(uint8_t logLevel)
{
    uint8_t subLevel = logLevel & 0x07;

    if (logLevel >= RF24LogLevel::ERROR && logLevel <= RF24LogLevel::DEBUG + 7)
    {
        uint8_t logIndex = ((logLevel & 0x38) >> 3) - 1;
        appendStr(RF24LogDescLevels[logIndex]);

        if(subLevel == 0)
        {
            appendStr("  ");
        }
        else
        {
            appendChar('+');
            appendUInt(subLevel, 8);
        }
    }
    else {
        appendStr(RF24LogDescLevel);
        appendChar(' ', logLevel < 010 ? 3 : 1 + (logLevel < 0100));
        appendUInt(logLevel, 8);
    }
    appendChar(RF24LOG_DELIMITER);
}

void RF24LogAbstractStream::appendFormat(SpecifierParsing* fmt_parser, va_list *args)
{
    if (fmt_parser->specifier == 's')
    {
        // print text from RAM
        #ifdef Arduino
        // warning: ISO C++17 does not allow 'register' storage class specifier [-Wregister]
        register char *str_p = (char *)va_arg(*args, int);
        #else
        char *str_p = (char *)va_arg(*args, int);
        #endif
        appendStr(str_p);
    }

#ifdef ARDUINO_ARCH_AVR
    else if (fmt_parser->specifier == 'S')
    {
        // print text from FLASH
        register __FlashStringHelper *s = (__FlashStringHelper *)va_arg(*args, int);
        appendStr(s);
    }
#endif

    else if (fmt_parser->specifier == 'c')
    {
        if (fmt_parser->width)
        {
            appendChar(fmt_parser->fill, fmt_parser->width - 1);
        }
        appendChar((char)va_arg(*args, int));
    }

    else if (fmt_parser->specifier == 'D' || fmt_parser->specifier == 'F')
    {
        // print as double
        if (fmt_parser->precis >= 0)
        {
            appendDouble(va_arg(*args, double), fmt_parser->precis);
        }
        else
        {
            appendDouble(va_arg(*args, double));
        }
    }

    else if (fmt_parser->specifier == 'd' || fmt_parser->specifier == 'i' || fmt_parser->specifier == 'l' || fmt_parser->specifier == 'u')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (fmt_parser->width)
        {
            uint16_t w = howWide(temp, 10);
            appendChar(fmt_parser->fill, (fmt_parser->width > w ? fmt_parser->width - w : 0));
        }
        if (fmt_parser->isUnsigned)
        {
            appendUInt(temp, 10);
        }
        else
        {
            appendInt(temp, 10);
        }
    }

    else if (fmt_parser->specifier == 'x' || fmt_parser->specifier == 'X')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (fmt_parser->width)
        {
            uint16_t w = howWide(temp, 16);
            appendChar(fmt_parser->fill, (fmt_parser->width > w ? fmt_parser->width - w : 0));
        }
        if (fmt_parser->isUnsigned)
        {
            appendUInt(temp, 16);
        }
        else
        {
            appendInt(temp, 16);
        }
    }
    else if (fmt_parser->specifier == 'o')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (fmt_parser->width)
        {
            uint16_t w = howWide(temp, 8);
            appendChar(fmt_parser->fill, (fmt_parser->width > w ? fmt_parser->width - w : 0));
        }
        if (fmt_parser->isUnsigned)
        {
            appendUInt(temp, 8);
        }
        else
        {
            appendInt(temp, 8);
        }
    }

    else if (fmt_parser->specifier == 'b')
    {
        // print as integer
        unsigned int temp = va_arg(*args, int);
        if (fmt_parser->width)
        {
            uint16_t w = howWide(temp, 2);
            appendChar(fmt_parser->fill, (fmt_parser->width > w ? fmt_parser->width - w : 0));
        }
        if (fmt_parser->isUnsigned)
        {
            appendUInt(temp, 2);
        }
        else
        {
            appendInt(temp, 2);
        }
    }
}


/* *************************** SpecifierParsing defs **************************** */

bool SpecifierParsing::isFlagged(char c)
{
    if (c == '0')
    {
        fill = '0';
    }
    return (bool)(c == '-' || c == '+' || c == ' ' || c == '0');
}

bool SpecifierParsing::isPaddPrec(char c)
{
    if (c == '.' || (c > 47 && c < 58))
    {
        if (c == '.')
        {
            precis = 0;
        }
        else
        {
            if (precis >=0)
            {
                precis = (precis * 10) + (c - 48);
            }
            else
            {
                width = (width * 10) + (c - 48);
            }
        }
        return true;
    }
    return false;

}

bool SpecifierParsing::isFmtOption(char c)
{

    if (c == 's' ||
    #ifdef ARDUINO_ARCH_AVR
            c == 'S' ||
    #endif
            c == 'c' ||
            c == 'D' ||
            c == 'F' ||
            c == 'x' ||
            c == 'X' ||
            c == 'o' ||
            c == 'u' ||
            c == 'b')
    {
        specifier = c;
        isUnsigned = (c == 'u');
        return false; // no second option supported
    }
    else if (c == 'd' ||
            c == 'i' ||
            c == 'l')
    {
        specifier = c;
        return true; // can also be specified as unsigned with 'u'
    }
    return false;
}
