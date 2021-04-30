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
#include "RF24LogLevel.h"
#include "ArduinoPrintLogger.h"


ArduinoPrintLogger::ArduinoPrintLogger(Print *stream)
{
    this->stream = stream;
}

void ArduinoPrintLogger::write(uint8_t logLevel,
                               const char *vendorId,
                               const char *message,
                               va_list *args)
{
    descTimeLevel(logLevel);
    stream->print(vendorId);
    stream->print(RF24LOG_DELIMITER);

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
    uint32_t now = millis();
    int16_t w = howWide(now);
    appendPadding(' ', 10 - w - !w);
    stream->print(now, DEC);
    stream->print(RF24LOG_DELIMITER);
}

void ArduinoPrintLogger::appendLogLevel(uint8_t logLevel)
{
    uint8_t subLevel = logLevel & 0x07;

    if (logLevel >= RF24LogLevel::ERROR && logLevel <= RF24LogLevel::DEBUG + 7)
    {
        uint8_t logIndex = ((logLevel & 0x38) >> 3) - 1;
        stream->print(RF24LogDescLevels[logIndex]);

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
        stream->print(RF24LogDescLevel);
        appendPadding(' ', logLevel < 010 ? 3 : 1 + (logLevel < 0100));
        stream->print(logLevel, OCT);
    }
    stream->print(RF24LOG_DELIMITER);
}

void ArduinoPrintLogger::appendFormattedMessage(const char *format, va_list *args)
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
            int16_t w = howWide(temp, 10);
            appendPadding(flags->fill, flags->width - w);
        }
        stream->print(temp, DEC);
    }

    else if (format == 'x' || format == 'X')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (flags->width)
        {
            int16_t w = howWide(temp, 16);
            appendPadding(flags->fill, flags->width - w);
        }
        stream->print(temp, HEX);
    }

    else if (format == 'o')
    {
        // print as integer
        int temp = va_arg(*args, int);
        if (flags->width)
        {
            int16_t w = howWide(temp, 8);
            appendPadding(flags->fill, flags->width - w);
        }
        stream->print(temp, OCT);
    }

    else if (format == 'b')
    {
        // print as integer
        unsigned int temp = va_arg(*args, int);
        if (flags->width)
        {
            int16_t w = howWide(temp, 2);
            appendPadding(flags->fill, flags->width - w);
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
    descTimeLevel(logLevel);
    stream->print(vendorId);
    stream->print(RF24LOG_DELIMITER);

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
            while (flags.isFlagged(c))
            {
                c = pgm_read_byte(p++);
            }
            while (flags.isPaddPrec(c))
            {
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
