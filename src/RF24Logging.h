/**
 * @file RF24Logging.h
 * @brief Provides `rf24Logging` singleton for accessing the RF24Log API.
 * @date Created 2 Oct 2020
 * @author Witold Markowski (wmarkow)
 * @copyright Copyright (C)
 *    2020        Witold Markowski (wmarkow)
 *    2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24LOGGER_H_
#define SRC_RF24LOGGER_H_

#if defined(ARDUINO_ARCH_AVR)
#include <WString.h>
#endif

/**
 * @defgroup LoggingAPI Logging API
 *
 * @brief simple helper macros for user access to logging output via the @ref rf24Logging object.
 * @{
 */

#include "RF24LogLevel.h"
#include "RF24LogHandler.h"

#if defined (ARDUINO_ARCH_AVR)
    #define RF24LOG_FLASHIFY(A) F(A)
    #define RF24Log_error(vendorId, message, ...) (rf24Logging.log(RF24LogLevel::ERROR, (const __FlashStringHelper*)(vendorId), RF24LOG_FLASHIFY(message), ##__VA_ARGS__))
    #define RF24Log_warn(vendorId, message, ...) (rf24Logging.log(RF24LogLevel::WARN, (const __FlashStringHelper*)(vendorId), RF24LOG_FLASHIFY(message), ##__VA_ARGS__))
    #define RF24Log_info(vendorId, message, ...) (rf24Logging.log(RF24LogLevel::INFO, (const __FlashStringHelper*)(vendorId), RF24LOG_FLASHIFY(message), ##__VA_ARGS__))
    #define RF24Log_debug(vendorId, message, ...) (rf24Logging.log(RF24LogLevel::DEBUG, (const __FlashStringHelper*)(vendorId), RF24LOG_FLASHIFY(message), ##__VA_ARGS__))
    #define RF24Log_log(logLevel, vendorId, message, ...) (rf24Logging.log(logLevel, (const __FlashStringHelper*)(vendorId), RF24LOG_FLASHIFY(message), ##__VA_ARGS__))
#else

    /**
     * @brief ouput an @ref ERROR message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf specifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    #define RF24Log_error(vendorId, message, ...) (rf24Logging.log(RF24LogLevel::ERROR, vendorId, message, ##__VA_ARGS__))

    /**
     * @brief output a message to WARN the reader
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf specifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    #define RF24Log_warn(vendorId, message, ...) (rf24Logging.log(RF24LogLevel::WARN, vendorId, message, ##__VA_ARGS__))

    /**
     * @brief output an @ref INFO message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf specifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    #define RF24Log_info(vendorId, message, ...) (rf24Logging.log(RF24LogLevel::INFO, vendorId, message, ##__VA_ARGS__))

    /**
     * @brief output a message to help developers @ref DEBUG their source code
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf specifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    #define RF24Log_debug(vendorId, message, ...) (rf24Logging.log(RF24LogLevel::DEBUG, vendorId, message, ##__VA_ARGS__))

    /**
     * @brief output a log message of any level
     * @sa RF24Logging::log()
     * @param logLevel the level of the logging message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf specifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    #define RF24Log_log(logLevel, vendorId, message, ...) (rf24Logging.log(logLevel, vendorId, message, ##__VA_ARGS__))
#endif

/** @brief This is the end-user's access point into the world of logging messages. */
class RF24Logging
{
private:
    /** @brief The output stream handler configured by sethandler() */
    RF24LogHandler *handler;

public:
    /** @brief Initializes the handler to nullptr */
    RF24Logging();

    /**
     * @brief set the instance's handler
     * @param handler The log handler where the messages will be redirected.
     */
    void setHandler(RF24LogHandler *handler);

    /**
     * @brief output a log message of any level
     * @param logLevel the level of the logging message
     * @param vendorId A scoping identity of the message's origin
     * @param message The message format string. Review [the printf specifiers](),
     * but note that not all are supported on certain MCU architectures (eg `%%F` for floats).
     * @param ... the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    void log(uint8_t logLevel, const char *vendorId, const char *message, ...);

#if defined (ARDUINO_ARCH_AVR)
    void log(uint8_t logLevel, const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...);
#endif
};

#ifdef DOXYGEN_FORCED
/** @brief macro (when defined) disables line feeds at the end of all log messages. */
#define RF24LOG_NO_EOL

/** @brief macro (when defined) disables timestamp at the start of all log messages. */
#define RF24LOG_NO_TIMESTAMP
#endif

/** @brief the singleton used for all your program's logging purposes. */
extern RF24Logging rf24Logging;

/** @} */

#endif /* SRC_RF24LOGGER_H_ */

/**
 * @example{lineno} gettingStarted.ino
 *
 * A Basic usage of RF24Logging on the Arduino IDE's Serial Monitor.
 * This example accepts user input to change the log level used as a filter.
 */

/**
 * @example{lineno} DualStream.ino
 *
 * This example uses a handler extension to forward log messages to 2
 * simultaneous out put streams.
 * This example accepts user input to change the log level used as a filter.
 */

/**
 * @example{lineno} AllLogLevels.ino
 *
 * This example just prints a messaged for each supported log level.
 * This example accepts user input to change the log level used as a filter.
 */
