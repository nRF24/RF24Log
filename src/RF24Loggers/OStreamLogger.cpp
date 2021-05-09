/**
 * @file OStreamLogger.cpp
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
#include <ctime> // for time_t, struct tm*, time(), localtime(), strftime()
#include "OStreamLogger.h"


OStreamLogger::OStreamLogger(std::ostream *stream)
{
    _stream = stream;
}

void OStreamLogger::appendTimestamp()
{
    char buffer[21];
    time_t rawtime;
    time(&rawtime);

    strftime(buffer, 20, "%F:%H:%M:%S", localtime(&rawtime));
    buffer[19] = RF24LOG_DELIMITER;
    buffer[20] = 0;
    *_stream << buffer;
}

void OStreamLogger::appendChar(char data, uint16_t depth)
{
    while (depth)
    {
        --depth;
        *_stream << data;
    }
}

void OStreamLogger::appendInt(long data, uint8_t base)
{
    if (base == 2)
    {
        bool is_signed = data < 0;
        if (!data)
        {
            *_stream << '0'; // output a zero
            return;
        }
        else if (is_signed)
        {
            *_stream << '-'; // output a negative sign
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
            *_stream << buffer[index]; // dump reversed string 1 char at a time
        }
    }
    else if (base == 8)
    {
        *_stream << std::oct << data;
    }
    else if (base == 16)
    {
        *_stream << std::hex << data;
    }
    else
    {
        *_stream << std::dec << data;
    }
}

void OStreamLogger::appendUInt(unsigned long data, uint8_t base)
{
    if (base == 2)
    {
        if (!data)
        {
            *_stream << '0'; // output a zero
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
            *_stream << buffer[index]; // dump reversed string 1 char at a time
        }
    }
    else if (base == 8)
    {
        *_stream << std::oct << data;
    }
    else if (base == 16)
    {
        *_stream << std::hex << std::uppercase << data;
    }
    else
    {
        *_stream << std::dec << data;
    }
}

void OStreamLogger::appendDouble(double data, uint8_t precision)
{
    std::streamsize prev_precision = _stream->precision(precision);
    _stream->setf(std::ios::fixed, std::ios::floatfield);
    *_stream << data;
    _stream->precision(prev_precision);
    _stream->unsetf(std::ios::floatfield);
    _stream->unsetf(std::ios::fixed);
}

void OStreamLogger::appendStr(const char* data)
{
    *_stream << data;
}

#endif // !defined(ARDUINO)