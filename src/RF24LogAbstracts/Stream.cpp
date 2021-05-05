/**
 * @file Stream.cpp
 * @date Created 4 May 2021
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C)
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include <RF24LogAbstracts/BaseHandler.h> // RF24LOG_DELIMITER
#include <RF24LogAbstracts/Stream.h>
#include <RF24LogLevel.h>


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
        // print a char
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
                uint16_t w = numbCharsToPrint(temp, base);
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
