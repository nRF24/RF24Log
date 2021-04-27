/**
 * @file RF24LogAbstracts.h
 * @brief abstract classes that allow custom handlers and different output stream APIs
 *
 * Created on: 2 Oct 2020
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *    2020        Witold Markowski (wmarkow)
 *    2021        Brendan Doherty (2bndy5)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24LOGABSTRACTS_H_
#define SRC_RF24LOGABSTRACTS_H_
#if defined (ARDUINO_ARCH_AVR)
#include <WString.h>
#endif
#include <stdint.h>
#include <stdarg.h>

#include <RF24LogHandler.h>
#include "RF24LogLevel.h"

/**
 * A base class for handling log messages.
 */
class RF24LogAbstractHandler : public RF24LogHandler
{
public:
    void log(uint8_t logLevel,
             const char *vendorId,
             const char *message,
             va_list *args);

    void setLogLevel(uint8_t logLevel);

#if defined (ARDUINO_ARCH_AVR)
    void log(uint8_t logLevel,
             const __FlashStringHelper *vendorId,
             const __FlashStringHelper *message,
             va_list *args);
#endif

protected:

    /** The configured log level used to filter which messages are output. */
    uint8_t logLevel;

    RF24LogAbstractHandler();

    /**
     * write log message to its destination
     * @param logLevel The level of the logging message
     * @param vendorId The prefixed origin of the message
     * @param message The message
     * @param args The sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    virtual void write(uint8_t logLevel,
                       const char *vendorId,
                       const char *message,
                       va_list *args) = 0;

#if defined (ARDUINO_ARCH_AVR)
    virtual void write(uint8_t logLevel,
                       const __FlashStringHelper *vendorId,
                       const __FlashStringHelper *message,
                       va_list *args) = 0;
#endif
};

/**
 * @brief A `protected` collection of methods that output formatted data to a stream.
 */
class RF24LogAbstractStream
{
protected:
    /** @brief output a timestamp */
    virtual void appendTimestamp() = 0;

    /**
     * @brief output a description of the log level
     * @param logLevel The level to describe.
     */
    virtual void appendLogLevel(uint8_t logLevel) = 0;

    /**
     * @brief output a message with the specifiers replaced with values from the sequence of @p args
     * @param format The format of the message
     * @param args The sequence of args
     */
    virtual void appendFormattedMessage(const char *format, va_list *args) = 0;

#if defined (ARDUINO_ARCH_AVR)
    virtual void appendFormattedMessage(const __FlashStringHelper *format, va_list *args) = 0;
#endif

};

#endif /* SRC_RF24LOGABSTRACTS_H_ */
