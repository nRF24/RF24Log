/**
 * @file RF24Logger.h
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

#ifndef SRC_RF24LOGGER_H_
#define SRC_RF24LOGGER_H_

#include <WString.h>
#include "RF24LogLevel.h"
#include "RF24LogHandler.h"

/**
 * This is the end-user's access point into the world of logging messages.
 */
class RF24Logger
{
private:
    RF24LogHandler *handler;

public:
    /** @brief Initializes the appender to nullptr */
    RF24Logger();

    /**
     * @brief set the instance's handler
     * @param handler The log handler where the messages will be redirected.
     */
    void setHandler(RF24LogHandler *handler);

    /**
     * @brief ouput an ERROR message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message to output
     * @param args consumable arguments
     */
    template <class T>
    void error(const __FlashStringHelper *vendorId, T message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(RF24LogLevel::ERROR, vendorId, message, &args);
    }

    /**
     * @brief output a message to WARN the reader
     * @param vendorId A scoping identity of the message's origin
     * @param message The message to output
     * @param args consumable arguments
     */
    template <class T>
    void warn(const __FlashStringHelper *vendorId, T message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(RF24LogLevel::WARN, vendorId, message, &args);
    }

    /**
     * @brief output an INFO message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message to output
     * @param args consumable arguments
     */
    template <class T>
    void info(const __FlashStringHelper *vendorId, T message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(RF24LogLevel::INFO, vendorId, message, &args);
    }

    /**
     * @brief output a message to help developers DEBUG their source code
     * @param vendorId A scoping identity of the message's origin
     * @param message The message to output
     * @param args consumable arguments
     */
    template <class T>
    void debug(const __FlashStringHelper *vendorId, T message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(RF24LogLevel::DEBUG, vendorId, message, &args);
    }

    /**
     * @brief output a log message of any level
     * @param vendorId A scoping identity of the message's origin
     * @param message The message to output
     * @param args consumable arguments
     */
    template <class T>
    void log(uint8_t logLevel, const __FlashStringHelper *vendorId, T message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(logLevel, vendorId, message, &args);
    }
};

/**
 * the singleton used for all your program's logging purposes
 */
extern RF24Logger rf24Logger;

#endif /* SRC_RF24LOGGER_H_ */

/**
 * @example{lineno} BasicSerialLogger.ino
 *
 * A Basic usage of RF24Logger on the Arduino IDE's Serial Monitor.
 */

/**
 * @example{lineno} EmptyLogger.ino
 *
 * In contrast to the BasicSerialLogger example this demonstrates
 * how to dissable logging entirely.
 */
