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

#endif

/* *************************** AbstractStream defs **************************** */

int16_t RF24LogAbstractStream::howWide(int64_t numb, uint8_t base)
{
    int64_t mask = (numb > 0 ? numb : numb * -1);
    int16_t i = 0;
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

void RF24LogAbstractStream::appendFormat(SpecifierFlags* flags, char format, va_list *args)
{
    if (format == 's')
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
    else if (format == 'S')
    {
        // print text from FLASH
        register __FlashStringHelper *s = (__FlashStringHelper *)va_arg(*args, int);
        appendStr(s);
    }
#endif

    else if (format == 'c')
    {
        if (flags->width)
        {
            appendChar(flags->fill, flags->width - 1);
        }
        appendChar((char)va_arg(*args, int));
    }

    else if (format == 'D' || format == 'F')
    {
        // print as double
        if (flags->precis >= 0)
        {
            appendDouble(va_arg(*args, double), flags->precis);
        }
        else
        {
            appendDouble(va_arg(*args, double));
        }
    }

    else if (format == 'd' || format == 'i' || format == 'l' || format == 'u')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (flags->width)
        {
            int16_t w = howWide(temp, 10);
            appendChar(flags->fill, flags->width - w);
        }
        appendInt(temp, 10);
    }

    else if (format == 'x' || format == 'X')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (flags->width)
        {
            int16_t w = howWide(temp, 16);
            appendChar(flags->fill, flags->width - w);
        }
        appendInt(temp, 16);
    }

    else if (format == 'o')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (flags->width)
        {
            int16_t w = howWide(temp, 8);
            appendChar(flags->fill, flags->width - w);
        }
        appendInt(temp, 8);
    }

    else if (format == 'b')
    {
        // print as integer
        unsigned int temp = va_arg(*args, int);
        if (flags->width)
        {
            int16_t w = howWide(temp, 2);
            appendChar(flags->fill, flags->width - w);
        }
        appendInt(temp, 2);
    }
    else
    {
        appendChar(format);
        if (flags->width)
        {
            appendUInt(flags->width, 10);
        }
    }
}

void RF24LogAbstractStream::appendFormattedMessage(const char *format, va_list *args)
{
    for (; *format != 0; ++format)
    {
        if (*format == '%')
        {
            ++format;
            SpecifierFlags flags;
            while (flags.isFlagged(*format))
            {
                ++format;
            }
            while (flags.isPaddPrec(*format))
            {
                ++format;
            }
            if (isalpha(*format))
            {
                appendFormat(&flags, *format, args);
            }
            else
            {
                if (*format != '%')
                {
                    appendChar('%', 1);
                }
                appendChar(*format, 1);
            }
        }
        else
        {
            appendChar(*format, 1);
        }
    }
}

#if defined (ARDUINO_ARCH_AVR)

void RF24LogAbstractStream::appendFormattedMessage(const __FlashStringHelper *format, va_list *args)
{
    PGM_P p = reinterpret_cast<PGM_P>(format);
    char c = pgm_read_byte(p++);
    for (; c != 0; c = pgm_read_byte(p++))
    {
        if (c == '%')
        {
            c = pgm_read_byte(p++);
            SpecifierFlags flags;
            while (flags.isFlagged(c))
            {
                c = pgm_read_byte(p++);
            }
            while (flags.isPaddPrec(c))
            {
                c = pgm_read_byte(p++);
            }
            if (isalpha(c))
            {
                appendFormat(&flags, c, args);
            }
            else
            {
                if (c != '%')
                {
                    appendChar('%');
                }
                appendChar(c);
            }
        }
        else
        {
            appendChar(c);
        }
    }
}
#endif

/* *************************** SpecifierFlags defs **************************** */

bool SpecifierFlags::isFlagged(char c)
{
    if (c == '0')
    {
        fill = '0';
    }
    return (bool)(c == '-' || c == '+' || c == ' ' || c == '0');
}

bool SpecifierFlags::isPaddPrec(char c)
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
