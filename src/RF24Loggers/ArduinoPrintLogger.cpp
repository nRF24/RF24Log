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

void ArduinoPrintLogger::appendTimestamp()
{
    unsigned long now = millis();
    int16_t w = howWide(now);
    appendChar(' ', 10 - w);
    appendUInt(now, 10);
    appendChar(RF24LOG_DELIMITER);
}

void ArduinoPrintLogger::appendChar(char data, int16_t depth)
{
    while (depth > 0)
    {
        --depth;
        stream->print((char)data);
    }
}

void ArduinoPrintLogger::appendInt(long data, uint8_t base)
{
    stream->print((int)data, base == 2 ? BIN : (base == 8 ? OCT : (base == 16 ? HEX : DEC)));
}

void ArduinoPrintLogger::appendUInt(unsigned long data, uint8_t base)
{
    stream->print((unsigned long)data, base == 2 ? BIN : (base == 8 ? OCT : (base == 16 ? HEX : DEC)));
}

void ArduinoPrintLogger::appendDouble(double data, uint8_t precision)
{
    stream->print(data, precision);
}

void ArduinoPrintLogger::appendStr(const char* data)
{
    stream->print(data);
}

#ifdef ARDUINO_ARCH_AVR
void ArduinoPrintLogger::appendStr(const __FlashStringHelper* data)
{
    stream->print(data);
}
#endif

#ifdef ARDUINO_ARCH_AVR
void ArduinoPrintLogger::write(uint8_t logLevel,
                               const __FlashStringHelper *vendorId,
                               const __FlashStringHelper *message,
                               va_list *args)
{
    descTimeLevel(logLevel);
    appendStr(vendorId);
    appendChar(RF24LOG_DELIMITER, 1);

    // print formatted message
    appendFormattedMessage(message, args);
    #ifndef RF24LOG_NO_EOL
    appendChar('\n');
    #endif
}
#endif

void ArduinoPrintLogger::write(uint8_t logLevel,
                               const char *vendorId,
                               const char *message,
                               va_list *args)
{
    descTimeLevel(logLevel);
    appendStr(vendorId);
    appendChar(RF24LOG_DELIMITER);

    // print formatted message
    appendFormattedMessage(message, args);
    #ifndef RF24LOG_NO_EOL
    appendChar('\n');
    #endif
}
