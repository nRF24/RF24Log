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

#if defined (ARDUINO_ARCH_AVR)
  #define RF24LOG_FLASHIFY(A) F(A)
  #define RF24LOGGER_info(vendorId, message, ...) (rf24Logger.log(RF24LogLevel::INFO, (const __FlashStringHelper*)(vendorId), RF24LOG_FLASHIFY(message), ##__VA_ARGS__))
#else
  #define RF24LOGGER_info(vendorId, message, ...) (rf24Logger.log(RF24LogLevel::INFO, vendorId, message, ##__VA_ARGS__))
#endif

/**
 * This is the end-user's access point into the world of logging messages.
 */
class RF24Logger
{
private:
    /** The output stream handler configured by sethandler() */
    RF24LogHandler *handler;

public:
    /** @brief Initializes the handler to nullptr */
    RF24Logger();

    /**
     * @brief set the instance's handler
     * @param handler The log handler where the messages will be redirected.
     */
    void setHandler(RF24LogHandler *handler);

    /**
     * @brief ouput an ERROR message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void error(const char *vendorId, const char *message, ...);

    /**
     * @brief output a message to WARN the reader
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void warn(const char *vendorId, const char *message, ...);

    /**
     * @brief output an INFO message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void info(const char *vendorId, const char *message, ...);

    /**
     * @brief output a message to help developers DEBUG their source code
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void debug(const char *vendorId, const char *message, ...);

    /**
     * @brief output a log message of any level
     * @param logLevel the level of the logging message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void log(uint8_t logLevel, const char *vendorId, const char *message, ...);

#if defined (ARDUINO_ARCH_AVR)
    /**
     * @brief ouput an ERROR message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void error(const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...);

    /**
     * @brief output a message to WARN the reader
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void warn(const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...);

    /**
     * @brief output an INFO message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void info(const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...);

    /**
     * @brief output a message to help developers DEBUG their source code
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void debug(const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...);

    /**
     * @brief output a log message of any level
     * @param logLevel the level of the logging message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void log(uint8_t logLevel, const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...);
#endif
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
