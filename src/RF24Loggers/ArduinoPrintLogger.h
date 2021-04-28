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
class ArduinoPrintLogger : public RF24LogAbstractHandler, RF24LogAbstractStream
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

    /**
     * @brief output a data according to the format specifier
     * @param count The number of prefixed padding characters
     * @param format The format of the message
     * @param args The sequence of args
     */
    void appendFormat(SpecifierFlags* flags, char format, va_list *args);

    /**
     * @brief append a padding character a number of times
     * @param padding The char to use as padding
     * @param depth The number of padding characters desired sequentially.
     */
    void appendPadding(char padding, int16_t depth);


    // declare the rest to raise from pure virtual
    /************************************************/

    void appendTimestamp();
    void appendLogLevel(uint8_t logLevel);
    void appendFormattedMessage(const char *format, va_list *args);
    void write(uint8_t logLevel,
               const char *vendorId,
               const char *message,
               va_list *args);

#if defined (ARDUINO_ARCH_AVR)
    void write(uint8_t logLevel,
               const __FlashStringHelper *vendorId,
               const __FlashStringHelper *message,
               va_list *args);
    void appendFormattedMessage(const __FlashStringHelper *format, va_list *args);
#endif
};

#endif /* SRC_RF24LOGGERS_ARDUINOPRINTLOGGER_H_ */
