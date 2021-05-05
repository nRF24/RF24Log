/**
 * @file RF24LogAbstracts/BaseHandler.h
 * @brief inherent declarations for all handlers.
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

#ifndef SRC_RF24LOGABSTRACTS_BASEHANDLER_H_
#define SRC_RF24LOGABSTRACTS_BASEHANDLER_H_

#if defined(ARDUINO_ARCH_AVR)
#include <WString.h> // __FlashStringHelper
#else
#include <string.h>
#endif
#include <stdint.h>
#include <stdarg.h>

/** @brief Change The Delimiter character used in the header prefix of log messages. */
#if !defined(RF24LOG_DELIMITER)
#define RF24LOG_DELIMITER ';'
#endif

// for some reason, these need to be declared here and
// not on any higher level of the project
// #define RF24LOG_NO_TIMESTAMP
// #define RF24LOG_NO_EOL
// #define RF24LOG_SHORT_DESC
// #define RF24LOG_TERSE_DESC
// #define RF24LOG_TAB_SIZE 4

#ifdef DOXYGEN_FORCED
/** @brief macro (when defined) disables line feeds at the end of all log messages. */
#define RF24LOG_NO_EOL

/** @brief macro (when defined) disables timestamp at the start of all log messages. */
#define RF24LOG_NO_TIMESTAMP

/**
 * @brief macro (when defined) uses a short description of the log levels.
 *
 * Descriptions with this macro defined look like
 * @code
 * " ERR ", "INFO1"
 * "WARN ", "INFO7"
 * "INFO ", "L   7"
 * " DBG ", "L 113"
 * @endcode
 */
#define RF24LOG_SHORT_DESC

/**
 * @brief macro (when defined) uses a terse (very short) description of the log levels.
 *
 * Descriptions with this macro defined look like
 * @code
 * " E ", " I1"
 * " W ", " I7"
 * " I ", "  7"
 * "DB ", "113"
 * @endcode
 */
#define RF24LOG_TERSE_DESC

/**
 * @brief macro (when defined) relaces all `\t` characters with a specified quantity of spaces
 *
 * When this macro is not defined the `\t` characters may have in consistent number of spaces between platforms.
 */
#define RF24LOG_TAB_SIZE 8
#endif

/** @brief A base mechanism for handling log messages. */
class RF24LogBaseHandler
{
public:
    /**
     * @brief log a message.
     * @param logLevel The level of the logging message
     * @param vendorId The prefixed origin of the message
     * @param message The message format string. Review [the supported printf spcifiers](md_docs_supported_specifiers.html).
     * @param args The sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    virtual void log(uint8_t logLevel,
                     const char *vendorId,
                     const char *message,
                     va_list *args);

#if defined (ARDUINO_ARCH_AVR)
    virtual void log(uint8_t logLevel,
                     const __FlashStringHelper *vendorId,
                     const __FlashStringHelper *message,
                     va_list *args);
#endif

    /**
     * set the maximal level of the logged messages.
     * @param logLevel The verbosity level used to filter which of the logged messages
     * are output.
     * @see Review the descriptions in the @ref logLevels
     */
    virtual void setLogLevel(uint8_t logLevel);
};

#endif /* SRC_RF24LOGABSTRACTS_BASEHANDLER_H_ */
