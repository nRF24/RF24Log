/**
 * @file NativePrintLogger.cpp
 * @date Created 2021-04-24
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C) <br>
 *     2021    Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#ifndef ARDUINO
#include <cstdio> // sprintf()

#if defined (PICO_BUILD)
#include <pico/stdlib.h> // to_ms_since_boot(), get_absolute_time()
#else
#include <ctime> // time_t, struct tm*, time(), localtime(), strftime()
#endif

#include "NativePrintLogger.h"

/****************************************************************************/

NativePrintLogger::NativePrintLogger()
{
}

/****************************************************************************/

void NativePrintLogger::appendTimestamp()
{
    #if defined(PICO_BUILD)
    printf_P("%10lu", to_ms_since_boot(get_absolute_time()));
    printf_P("%c", RF24LOG_DELIMITER);
    #else // !defined (PICO_BUILD) && !defined (ARDUINO)
    char buffer[21];
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 20, "%F:%H:%M:%S", timeinfo);
    buffer[20] = RF24LOG_DELIMITER;
    printf_P("%s", buffer);
    #endif // defined (PICO_BUILD) && !defined (ARDUINO)
}

/****************************************************************************/

void NativePrintLogger::appendChar(char data, uint16_t depth)
{
    while (depth > 0)
    {
        --depth;
        printf_P("%c", data);
    }
}

/****************************************************************************/

void NativePrintLogger::appendInt(long data)
{

    printf_P("%li", (long)data);
}

/****************************************************************************/

void NativePrintLogger::appendUInt(unsigned long data, uint8_t base)
{
    if (base == 2)
    {
        if (!data)
        {
            printf_P("0"); // output a zero
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
        while (index)
        {
            appendChar(buffer[--index]); // dump reversed string 1 char at a time
        }
    }
    else if (base == 8)
    {
        printf_P("%o", (unsigned int)data);
    }
    else if (base == 16)
    {
        printf_P("%X", (unsigned int)data);
    }
    else
    {
        printf_P("%lu", (unsigned long)data);
    }
}

/****************************************************************************/

void NativePrintLogger::appendDouble(double data, uint8_t precision)
{
    char fmt_buf[64];
    sprintf(fmt_buf, "%%.%dF", precision); // prepares a fmt str ("%.nF")
    printf_P(fmt_buf, data);
}

/****************************************************************************/

void NativePrintLogger::appendStr(const char* data)
{
    printf_P("%s", data);
}

#endif /* ARDUINO */
