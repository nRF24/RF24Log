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

/* *************************** Abstract global function defs **************************** */

uint16_t howWide(int64_t numb, uint8_t base)
{
    int64_t mask = (numb < 0 ? numb * -1 : numb);
    uint16_t i = 0;
    while (mask)
    {
        if      (base == 2)  { mask >>= 1; }
        else if (base == 8)  { mask >>= 3; }
        else if (base == 16) { mask >>= 4; }
        else  /*base == 10*/ { mask /= 10; }
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
    do
    {
        // print header
    #if defined (RF24LOG_NO_EOL)
        appendChar(RF24LOG_DELIMITER);
    #endif
        descTimeLevel(logLevel);
        PGM_P id = reinterpret_cast<PGM_P>(vendorId);
        char v = pgm_read_byte(id++);
        if (v)
        {
            appendStr(vendorId);
            appendChar(RF24LOG_DELIMITER);
        }

        // print formatted message (or at least 1 line at a time)
        while (c
    #if !defined(RF24LOG_NO_EOL)
               && c !='\n'
    #endif
                )
        {
    #if defined (RF24LOG_TAB_SIZE)
            if (c == '\t')
            {
                appendChar(' ', RF24LOG_TAB_SIZE);
            }
            else
    #endif
            if (c == '%')
            {
                SpecifierParsing fmt_parser;
                c = pgm_read_byte(p++); // get ready to feed the parser
                while (c && fmt_parser.isFlagged(c))   { c = pgm_read_byte(p++); }
                while (c && fmt_parser.isPaddPrec(c))  { c = pgm_read_byte(p++); }
                while (c && fmt_parser.isFmtOption(c)) { c = pgm_read_byte(p++); }
                if (fmt_parser.specifier)
                {
                    appendFormat(&fmt_parser, args);
                    // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char
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
        #if defined(RF24LOG_NO_EOL)
            if (c != '\n') // dispose char; we control new line feeds ourselves
        #endif
            {
                appendChar(c);
            }
            c = pgm_read_byte(p++);
        }
        #if !defined(RF24LOG_NO_EOL)
        if (c == '\n') { c = pgm_read_byte(p++); } // dispose char; we control new line feeds ourselves
        appendChar('\n');
        #endif
    } while (c);
}
#endif

void RF24LogPrintfParser::write(uint8_t logLevel,
                               const char *vendorId,
                               const char *message,
                               va_list *args)
{
    char *c = (char*)message;
    do
    {
        // print header
    #if defined (RF24LOG_NO_EOL)
        appendChar(RF24LOG_DELIMITER);
    #endif
        descTimeLevel(logLevel);
        if (*vendorId)
        {
            appendStr(vendorId);
            appendChar(RF24LOG_DELIMITER);
        }

        // print formatted message (or at least 1 line at a time)
        while (*c
    #if !defined(RF24LOG_NO_EOL)
                && *c !='\n'
    #endif
                )
        {
    #if defined (RF24LOG_TAB_SIZE)
            if (*c == '\t')
            {
                appendChar(' ', RF24LOG_TAB_SIZE);
            }
            else
    #endif
            if (*c == '%')
            {
                SpecifierParsing fmt_parser;
                ++c; // get ready to feed the parser
                while (*c && fmt_parser.isFlagged(*c))   { ++c; }
                while (*c && fmt_parser.isPaddPrec(*c))  { ++c; }
                while (*c && fmt_parser.isFmtOption(*c)) { ++c; }
                // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char
                if (fmt_parser.specifier)
                {
                    appendFormat(&fmt_parser, args);
                    // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char
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
        #if defined(RF24LOG_NO_EOL)
            if (*c != '\n') // dispose char; we control the new line feeds ourselves
        #endif
            {
                appendChar(*c);
            }
            ++c;
        }
        #if !defined(RF24LOG_NO_EOL)
        if (*c == '\n') { ++c; } // dispose char; we control the new line feeds ourselves
        appendChar('\n');
        #endif
    } while (*c);
}

/* *************************** AbstractStream defs **************************** */

void RF24LogAbstractStream::descTimeLevel(uint8_t logLevel)
{
    if (!logLevel) { return; } // skip level description for level 0
    #if !defined(RF24LOG_NO_TIMESTAMP)
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
    #if !defined(RF24LOG_TERSE_DESC) && !defined(RF24LOG_SHORT_DESC)
            appendChar(' ', 2);
    #else
            appendChar(' ');
    #endif
        }
        else
        {
    #if !defined(RF24LOG_TERSE_DESC) && !defined(RF24LOG_SHORT_DESC)
            appendChar('+');
    #endif
            appendUInt(subLevel, 8);
        }
    }
    else {
        appendStr(RF24LogDescLevel);
        appendChar(' ', logLevel < 010 ? 2 : (logLevel < 0100));
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
        double temp = va_arg(*args, double);

        // printf() traditionally reserves a precision of 0 to avoid printing a value of 0
        // so, if precision is 0 and value is 0.0, then don't print and just consume arg
        if (fmt_parser->precis == 0 && temp == 0.0) { return; }

        if (fmt_parser->precis >= 0)
        {
            appendDouble(temp, fmt_parser->precis);
        }
        else
        {
            appendDouble(temp);
        }
    }
    else
    {
        // print as integer
        uint8_t base = 3; // use 3 as a invalid sentinel
        if (fmt_parser->specifier == 'd' || fmt_parser->specifier == 'i')      { base = 10; }
        else if (fmt_parser->specifier == 'x' || fmt_parser->specifier == 'X') { base = 16; }
        else if (fmt_parser->specifier == 'o') { base = 8; }
        else if (fmt_parser->specifier == 'b') { base = 2; }
        if (base != 3) // if it was a supported char
        {
            long temp = va_arg(*args, int);
            if (fmt_parser->width)
            {
                uint16_t w = howWide(temp, base);
                appendChar(fmt_parser->fill, (fmt_parser->width > w ? fmt_parser->width - w : 0));
            }
            if (fmt_parser->specifier == 'u' ||
                    fmt_parser->specifier == 'x' || fmt_parser->specifier == 'X' ||
                    fmt_parser->specifier == 'o' || fmt_parser->specifier == 'b')
            {
                appendUInt(temp, base);
            }
            else
            {
                appendInt(temp, base);
            }
        }
        else
        {
            appendChar(fmt_parser->specifier);
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
            precis = 0; // 0.0 value will not be output
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
        if (c == 'u' || c == 'x' || c == 'X' || c == 'o' || c == 'b')
        {
            isUnsigned = true;
        }
        if (c != 'u' ||c != 'h') { specifier = c; } // don't record modifiers
        return false; // no second option supported
    }
    else if (c == 'd' ||
            c == 'i' ||
            c == 'l' ||
            c == 'h')
    {
        if (c != 'h' && c != 'l') { specifier = c; } // don't record modifiers
        return true; // can also support a second option (like 'u')
    }
    return false;
}
