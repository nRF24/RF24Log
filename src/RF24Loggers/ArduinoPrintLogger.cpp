/**
 * @file ArduinoPrintLogger.cpp
 * @date Created 2 Oct 2020
 * @author Witold Markowski (wmarkow)
 * @copyright Copyright (C) <br>
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#include <Arduino.h> // millis()
#include "../RF24LogLevel.h"
#include "ArduinoPrintLogger.h"
#include <stdio.h> // size_t

/****************************************************************************/

ArduinoPrintLogger::ArduinoPrintLogger(Print *stream)
{
    _stream = stream;
}

/****************************************************************************/

void ArduinoPrintLogger::appendTimestamp()
{
    unsigned long now = millis();
    uint16_t w = numbCharsToPrint(now);
    appendChar(' ', (w < 10 ? 10 - w : 0));
    appendUInt(now, 10);
    appendChar(RF24LOG_DELIMITER);
}

/****************************************************************************/

void ArduinoPrintLogger::appendChar(char data, uint16_t depth)
{
    while (depth > 0)
    {
        --depth;
        _stream->print((char)data);
    }
}

/****************************************************************************/

void ArduinoPrintLogger::appendInt(long data)
{
    _stream->print((long)data);
}

/****************************************************************************/

void ArduinoPrintLogger::appendUInt(unsigned long data, uint8_t base)
{
    _stream->print((unsigned long)data, (int)base);
}

/****************************************************************************/

void ArduinoPrintLogger::appendDouble(double data, uint8_t precision)
{
    _stream->print(data, precision);
}

/****************************************************************************/

void ArduinoPrintLogger::appendStr(const char* data)
{
    _stream->print(data);
}

/****************************************************************************/

#ifdef ARDUINO_ARCH_AVR
void ArduinoPrintLogger::appendStr(const __FlashStringHelper* data)
{
    _stream->print(data);
}
#endif
