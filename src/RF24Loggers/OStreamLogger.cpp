/**
 * @file OStreamLogger.cpp
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
#ifndef ARDUINO
#include <ctime> // for time_t, struct tm*, time(), localtime(), strftime()
#include "OStreamLogger.h"


OStreamLogger::OStreamLogger(std::ostream *stream)
{
    this->stream = stream;
}

void OStreamLogger::write(uint8_t logLevel,
                          const char *vendorId,
                          const char *message,
                          va_list *args)
{
    descTimeLevel(logLevel);
    *stream << vendorId << RF24LOG_DELIMITER;

    // print formatted message
    appendFormattedMessage(message, args);
    #ifndef RF24LOG_NO_EOL
    *stream << std::endl;
    #endif
}

void OStreamLogger::appendTimestamp()
{
    char buffer[21];
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 20, "%F:%H:%M:%S", timeinfo);
    buffer[20] = RF24LOG_DELIMITER;
    *stream << buffer;
}

void OStreamLogger::appendChar(char data, uint16_t depth)
{
    while (depth > 0)
    {
        --depth;
        *stream << (char)data;
    }
}

void OStreamLogger::appendInt(long data, uint8_t base)
{
    if (base == 2)
    {
        bool is_signed = data < 0;
        if (!data)
        {
            *stream << '0'; // output a zero
            return;
        }
        else if (is_signed)
        {
            *stream << '-'; // output a negative sign
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
            *stream << buffer[index]; // dump reversed string 1 char at a time
        }
    }
    else if (base == 8)
    {
        *stream << std::oct << data;
    }
    else if (base == 16)
    {
        *stream << std::hex << data;
    }
    else
    {
        *stream << std::dec << data;
    }
}

void OStreamLogger::appendUInt(unsigned long data, uint8_t base)
{
    if (base == 2)
    {
        if (!data)
        {
            *stream << '0'; // output a zero
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
            *stream << buffer[index]; // dump reversed string 1 char at a time
        }
    }
    else if (base == 8)
    {
        *stream << std::oct << data;
    }
    else if (base == 16)
    {
        *stream << std::hex << data;
    }
    else
    {
        *stream << std::dec << data;
    }
}

void OStreamLogger::appendDouble(double data, uint8_t precision)
{
    *stream << std::fixed << stream->precision(precision) << data;
}

void OStreamLogger::appendStr(const char* data)
{
    *stream << data;
}

#endif // !defined(ARDUINO)