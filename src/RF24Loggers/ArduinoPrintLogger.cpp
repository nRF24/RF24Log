/**
 * @file ArduinoPrintLogger.cpp
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
#include <Arduino.h>

#include "ArduinoPrintLogger.h"

/** description of the @ref ERROR base level */
const char rf24logLevelError[] = "ERROR";
/** description of the @ref WARN base level */
const char rf24logLevelWarn[] = " WARN";
/** description of the @ref INFO base level */
const char rf24logLevelInfo[] = " INFO";
/** description of the @ref DEBUG base level */
const char rf24logLevelDebug[] = "DEBUG";
/** collection of the base level descriptions */
const char *const rf24LogLevels[] = {rf24logLevelError,
                                     rf24logLevelWarn,
                                     rf24logLevelInfo,
                                     rf24logLevelDebug};

ArduinoPrintLogger::ArduinoPrintLogger(Print *stream)
{
    this->stream = stream;
}

void ArduinoPrintLogger::write(uint8_t logLevel,
                                 const char *vendorId,
                                 const char *message,
                                 va_list *args)
{
    appendTimestamp();
    appendLogLevel(logLevel);
    stream->print(vendorId);
    stream->print(";");

    // print formatted message
    appendFormattedMessage(message, args);
    #ifndef RF24LOG_NO_EOL
    stream->print("\n");
    #endif
}

void ArduinoPrintLogger::appendTimestamp()
{
    // this seems to cost more resources
    // char c[11];
    // sprintf(c, "%10lu;", millis());
    // stream->print(c);

    // this costs less by using in-house tools
    unsigned long temp, now(millis());
    temp = now;
    uint16_t i = 0;
    while (temp)
    {
        temp /= 10;
        i++;
    }
    appendPadding(' ', 10 - i - !i);
    stream->print(now);
    stream->print(";");
}

void ArduinoPrintLogger::appendLogLevel(uint8_t logLevel)
{
    uint8_t subLevel = logLevel & 0x07;

    if (logLevel >= RF24LogLevel::ERROR && logLevel <= RF24LogLevel::DEBUG + 7)
    {
        uint8_t logIndex = ((logLevel & 0x38) >> 3) - 1;
        stream->print(rf24LogLevels[logIndex]);

        if(subLevel == 0)
        {
            stream->print("  ");
        }
        else
        {
            stream->print("+");
            stream->print(subLevel);
        }
    }
    else {
        stream->print("Lvl");
        appendPadding(' ', logLevel < 010 ? 3 : 1 + (logLevel < 0100));
        stream->print(logLevel, OCT);
    }
    stream->print(";");
}

void ArduinoPrintLogger::appendFormattedMessage(const char *format, va_list *args)
{
    for (; *format != 0; ++format)
    {
        if (*format == '%')
        {
            ++format;
            SpecifierFlags flags;
            while (*format == '-' || *format == '+' || *format == ' ' || *format == '0')
            {
                if (*format == '0')
                {
                    flags.fill = *format;
                }
                ++format;
            }
            while (isDigit(*format) || *format == '.')
            {
                if (*format == '.')
                {
                    flags.precis = 0;
                }
                else
                {
                    if (flags.precis >=0) {
                        flags.precis = (flags.precis * 10) + (*format - 48);
                    }
                    else
                    {
                        flags.width = (flags.width * 10) + (*format - 48);
                    }
                }
                ++format;
            }
            if (isAlpha(*format))
            {
                appendFormat(&flags, *format, args);
            }
            else
            {
                if (*format != '%')
                {
                    stream->print("%");
                }
                stream->print(*format);
            }
        }
        else
        {
            stream->print(*format);
        }
    }
}

void ArduinoPrintLogger::appendFormat(SpecifierFlags* flags, char format, va_list *args)
{
    if (format == 's')
    {
        // print text from RAM
        register char *s = (char *)va_arg(*args, int);
        stream->print(s);
    }

#ifdef ARDUINO_ARCH_AVR
    else if (format == 'S')
    {
        // print text from FLASH
        register __FlashStringHelper *s = (__FlashStringHelper *)va_arg(*args, int);
        stream->print(s);
    }
#endif

    else if (format == 'c')
    {
        if (flags->width)
        {
            appendPadding(flags->fill, flags->width - 1);
        }
        stream->print((char)va_arg(*args, int));
    }

    else if (format == 'D' || format == 'F')
    {
        // print as double
        if (flags->precis >= 0)
        {
            stream->print(va_arg(*args, double), flags->precis);
        }
        else
        {
            stream->print(va_arg(*args, double));
        }
    }

    else if (format == 'd' || format == 'i' || format == 'l' || format == 'u')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (flags->width)
        {
            int mask = temp;
            int16_t i = 0;
            while (mask)
            {
                mask /= 10;
                i++;
            }
            if (temp < 0)
            {
                i++; // compensate for the negative sign
            }
            appendPadding(flags->fill, flags->width - i);
        }
        stream->print(temp, DEC);
    }

    else if (format == 'x' || format == 'X')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (flags->width)
        {
            int mask = temp;
            int16_t i = 0;
            while (mask)
            {
                mask >>= 4;
                i++;
            }
            if (temp < 0)
            {
                i++; // compensate for the negative sign
            }
            appendPadding(flags->fill, flags->width - i);
        }
        stream->print(temp, HEX);
    }

    else if (format == 'o')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (flags->width)
        {
            int mask = temp;
            int16_t i = 0;
            while (mask)
            {
                mask >>= 3;
                i++;
            }
            if (temp < 0)
            {
                i++; // compensate for the negative sign
            }
            appendPadding(flags->fill, flags->width - i);
        }
        stream->print(temp, OCT);
    }

    else if (format == 'b')
    {
        // print as integer
        unsigned int temp = va_arg(*args, int);
        if (flags->width)
        {
            unsigned int mask = temp;
            int16_t i = 0;
            while (mask)
            {
                mask >>= 1;
                i++;
            }
            appendPadding(flags->fill, flags->width - i);
        }
        stream->print(temp, BIN);
    }
    else
    {
        stream->print(format);
        if (flags->width)
        {
            stream->print(flags->width, DEC);
        }
    }
}

void ArduinoPrintLogger::appendPadding(char padding, int16_t depth)
{
    while (depth > 0)
    {
        --depth;
        stream->print((char)padding);
    }
}

#if defined (ARDUINO_ARCH_AVR)
void ArduinoPrintLogger::write(uint8_t logLevel,
                                 const __FlashStringHelper *vendorId,
                                 const __FlashStringHelper *message,
                                 va_list *args)
{
    appendTimestamp();
    appendLogLevel(logLevel);
    stream->print(vendorId);
    stream->print(";");

    // print formatted message
    appendFormattedMessage(message, args);
    #ifndef RF24LOG_NO_EOL
    stream->print("\n");
    #endif
}

void ArduinoPrintLogger::appendFormattedMessage(const __FlashStringHelper *format, va_list *args)
{
    PGM_P p = reinterpret_cast<PGM_P>(format);
    char c = pgm_read_byte(p++);
    for (; c != 0; c = pgm_read_byte(p++))
    {
        if (c == '%')
        {
            c = pgm_read_byte(p++);
            SpecifierFlags flags;
            while (c == '-' || c == '+' || c == ' ' || c == '0')
            {
                if (c == '0')
                {
                    flags.fill = '0';
                }
                c = pgm_read_byte(p++);
            }
            while (isDigit(c) || c == '.')
            {
                if (c == '.')
                {
                    flags.precis = 0;
                }
                else
                {
                    if (flags.precis >=0) {
                        flags.precis = (flags.precis * 10) + (c - 48);
                    }
                    else
                    {
                        flags.width = (flags.width * 10) + (c - 48);
                    }
                }
                c = pgm_read_byte(p++);
            }
            if (isAlpha(c))
            {
                appendFormat(&flags, c, args);
            }
            else
            {
                if (c != '%')
                {
                    stream->print("%");
                }
                stream->print(c);
            }
        }
        else
        {
            stream->print(c);
        }
    }
}
#endif
