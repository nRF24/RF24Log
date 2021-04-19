/**
 * @file RF24AbstractLogHandler.h
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

#ifndef SRC_HANDLERS_RF24ABSTRACTLOGHANDLER_H_
#define SRC_HANDLERS_RF24ABSTRACTLOGHANDLER_H_

#include <WString.h>
#include <stdint.h>
#include <stdarg.h>

#include <RF24LogHandler.h>
#include "RF24LogLevel.h"

/**
 * A base class for handling log messages.
 */
class RF24AbstractLogHandler : public RF24LogHandler
{
public:
    void log(uint8_t logLevel,
             const char *vendorId,
             const char *message,
             va_list *args);

    void setLogLevel(uint8_t logLevel);

#ifdef ARDUINO_ARCH_AVR
    void log(uint8_t logLevel,
             const __FlashStringHelper *vendorId,
             const __FlashStringHelper *message,
             va_list *args);
#endif

protected:

    /** The configured log level used to filter which messages are output. */
    uint8_t logLevel;

    RF24AbstractLogHandler();

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

#ifdef ARDUINO_ARCH_AVR
    /**
     * write log message to its destination
     * @param logLevel The level of the logging message
     * @param vendorId The prefixed origin of the message
     * @param message The message
     * @param args The sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    virtual void write(uint8_t logLevel,
                       const __FlashStringHelper *vendorId,
                       const __FlashStringHelper *message,
                       va_list *args) = 0;
#endif
};

#endif /* SRC_HANDLERS_RF24ABSTRACTLOGHANDLER_H_ */
