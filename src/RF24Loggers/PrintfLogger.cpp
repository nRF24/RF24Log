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
#if defined (ARDUINO)
    #if defined (ARDUINO_ARCH_AVR)
    #include <WString.h> // __FlashStringHelper sprintf()
    #else
    #include <string.h> // sprintf()
    #endif
#else
#include <cstdio> // sprintf()
#endif

#if defined (ARDUINO)
#include <Arduino.h> // millis()
#elif defined (PICO_BUILD)
#include <pico/stdlib.h> // to_ms_since_boot(), get_absolute_time()
#else
#include <ctime> // time_t, struct tm*, time(), localtime(), strftime()
#endif

#include <RF24Loggers/PrintfLogger.h>

PrintfLogger::PrintfLogger()
{
    _stream = nullptr;
}

PrintfLogger::PrintfLogger(char* buffer)
{
    _stream = buffer;
}

void PrintfLogger::appendTimestamp()
{
    #if defined (ARDUINO)
    printf_P(PSTR("%10lu;"), millis());
    #elif defined(PICO_BUILD)
    printf_P(PSTR("%10lu;"), to_ms_since_boot(get_absolute_time()));
    #else // !defined (PICO_BUILD) && !defined (ARDUINO)
    char buffer[21];
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 20, "%F:%H:%M:%S", timeinfo);
    buffer[20] = RF24LOG_DELIMITER;
    printf_P(PSTR(buffer));
    #endif // defined (PICO_BUILD) && !defined (ARDUINO)
}

void PrintfLogger::appendChar(char data, uint16_t depth)
{
    while (depth > 0)
    {
        --depth;
        printf_P(PSTR("%c"), data);
    }
}

void PrintfLogger::appendInt(long data, uint8_t base)
{
    if (base == 2)
    {
        if (!data)
        {
            printf_P(PSTR("0")); // output a zero
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
        printf_P(PSTR("%o"), data);
    }
    else if (base == 16)
    {
        printf_P(PSTR("%X"), data);
    }
    else
    {
        printf_P(PSTR("%lu"), data);
    }
}

void PrintfLogger::appendUInt(unsigned long data, uint8_t base)
{
    if (base == 2)
    {
        if (!data)
        {
            printf_P(PSTR("0")); // output a zero
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
        printf_P(PSTR("%o"), data);
    }
    else if (base == 16)
    {
        printf_P(PSTR("%X"), data);
    }
    else
    {
        printf_P(PSTR("%l"), data);
    }
}

void PrintfLogger::appendDouble(double data, uint8_t precision)
{
    char fmt_buf[64];
    sprintf(fmt_buf, "%%.%dF", precision); // prepares a fmt str ("%.nF")
    printf_P(PSTR(fmt_buf), data);
}

void PrintfLogger::appendStr(const char* data)
{
    printf_P("%s", data);
}
