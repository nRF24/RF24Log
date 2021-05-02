/**
 * @file ArduinoPrintLogger.h
 * @brief handler for Print::print() based function calls
 * @date Created 2 Oct 2020
 * @author Witold Markowski (wmarkow)
 * @copyright Copyright (C)
 *     2020    Witold Markowski (wmarkow) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24LOGGERS_ARDUINOPRINTLOGGER_H_
#define SRC_RF24LOGGERS_ARDUINOPRINTLOGGER_H_

#include <RF24LogAbstracts.h>
#include <Print.h>

/** @brief A log handler implementation which outputs log messages to a stream. */
class ArduinoPrintLogger : public RF24LogPrintfParser
{
protected:

    /** @brief The output stream */
    Print *stream;

public:

    /**
     * @brief instance constructor
     * @param stream The output stream to which logging messages are directed.
     */
    ArduinoPrintLogger(Print *stream);

protected:

    // declare the rest to raise from pure virtual
    /************************************************/
    void appendTimestamp();
    void appendChar(char data, uint16_t depth = 1);
    void appendInt(long data, uint8_t base = 10);
    void appendUInt(unsigned long data, uint8_t base = 10);
    void appendDouble(double data, uint8_t precision = 2);
    void appendStr(const char* data);
#ifdef ARDUINO_ARCH_AVR
    void appendStr(const __FlashStringHelper* data);
#endif
};

#endif /* SRC_RF24LOGGERS_ARDUINOPRINTLOGGER_H_ */
