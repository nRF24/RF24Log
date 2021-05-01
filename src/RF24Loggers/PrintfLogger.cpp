/**
 * @file PrintfLogger.cpp
 * @date Created 2021-04-24
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C)
 *     2021    Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#ifdef ARDUINO
    #ifdef ARDUINO_ARCH_AVR
    #include <WString.h> // sprintf()
    #else
    #include <string.h> // sprintf()
    #endif
#else
#include <cstdio> // sprintf()
#endif

#ifdef ARDUINO
#include <Arduino.h> // millis()
#elif defined (PICO_BUILD)
#include <pico-sdk/stdlib.h> // to_us_since_boot(), absolute_time()
#else
#include <ctime> // for time_t, struct tm*, time(), localtime(), strftime()
#endif

#include "PrintfLogger.h"

PrintfLogger::PrintfLogger(int (*_stream)(const char *, ...))
{
    stream = _stream;
}

void PrintfLogger::write(uint8_t logLevel,
                         const char *vendorId,
                         const char *message,
                         va_list *args)
{
    descTimeLevel(logLevel);
    stream(vendorId);
    stream(reinterpret_cast<const char*>(RF24LOG_DELIMITER));

    // print formatted message
    appendFormattedMessage(message, args);
    #ifndef RF24LOG_NO_EOL
    stream("\n");
    #endif
}

void PrintfLogger::appendTimestamp()
{
    #if defined (ARDUINO)
    stream("%10lu;", millis());
    #elif defined(PICO_BUILD)
    stream("%10lu;", to_ms_since_boot(absolute_time()));
    #else // !defined (PICO_BUILD) && !defined (ARDUINO)
    char buffer[21];
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 20, "%F:%H:%M:%S", timeinfo);
    buffer[20] = RF24LOG_DELIMITER;
    stream(buffer);
    #endif // defined (PICO_BUILD) && !defined (ARDUINO)
}

void PrintfLogger::appendChar(char data, int16_t depth)
{
    while (depth > 0)
    {
        --depth;
        stream(reinterpret_cast<const char*>(data));
    }
}

void PrintfLogger::appendInt(long data, uint8_t base)
{
    if (base == 2)
    {
        if (!data)
        {
            stream("0"); // output a zero
            return;
        }
        char buffer[64];
        uint8_t index = 0;
        while (data)
        {
            // get representation as a reversed string
            buffer[index] = (data & 1) + 48;
            data >>= 1;
            ++index;
        }
        while (--index)
        {
            appendChar(buffer[index]); // dump reversed string 1 char at a time
        }
    }
    else if (base == 8)
    {
        stream("%o", data);
    }
    else if (base == 16)
    {
        stream("%X", data);
    }
    else
    {
        stream("%lu", data);
    }
}

void PrintfLogger::appendUInt(unsigned long data, uint8_t base)
{
    if (base == 2)
    {
        if (!data)
        {
            stream("0"); // output a zero
            return;
        }
        char buffer[64];
        uint8_t index = 0;
        while (data)
        {
            // get representation as a reversed string
            buffer[index] = (data & 1) + 48;
            data >>= 1;
            ++index;
        }
        while (--index)
        {
            appendChar(buffer[index]); // dump reversed string 1 char at a time
        }
    }
    else if (base == 8)
    {
        stream("%o", data);
    }
    else if (base == 16)
    {
        stream("%X", data);
    }
    else
    {
        stream("%l", data);
    }
}

void PrintfLogger::appendDouble(double data, uint8_t precision)
{
    char fmt_buf[64];
    sprintf(fmt_buf, "%%.%dD", precision); // prepares a fmt str ("%.nD")
    stream(reinterpret_cast<const char*>(fmt_buf), data);
}

void PrintfLogger::appendStr(const char* data)
{
    stream(data);
}
