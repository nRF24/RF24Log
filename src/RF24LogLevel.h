/**
 * @file RF24LogLevel.h
 * @brief Order of log levels and filtering
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

#ifndef SRC_RF24LOGLEVEL_H_
#define SRC_RF24LOGLEVEL_H_

#include <stdint.h>
/**
 * @defgroup logLevels Log Levels
 * @brief Order of logging levels
 * @{
 */

// #define RF24LOG_REVERSE_LVL_ORDER

/**
 * @brief the predefined logging levels
 *
 * These named levels are the base or parent levels. They increment in in octal counts of `010`.
 * Each base level can have up to 7 additional sublevels. <br>For example:
 * - a level of 031 is the first sublevel of @ref INFO verbosity
 * - a level of 037 is the last sublevel of @ref INFO verbosity
 *
 * If the log level is configured (using RF24LogBaseHandler::setLogLevel()) for a verbosty of `020` prevents outputting all messages designated for
 * any log level greater than `020`.
 */
enum RF24LogLevel : uint8_t
{
    /** (`0`) the level to disable all log messages */
    OFF   = 0,
#if defined (RF24LOG_REVERSE_LVL_ORDER)
    ERROR = 040,
    WARN  = 030,
    INFO  = 020,
    DEBUG = 010,
    ALL   = 1
#else
    /** (`010`) the level to specify an error message */
    ERROR = 010,
    /** (`020`) the level to specify an warning message */
    WARN  = 020,
    /** (`030`) the level to specify an informational message */
    INFO  = 030,
    /** (`040`) the level to specify an debugging message */
    DEBUG = 040,
    /** (`0377` or `0xFF`) the level to enable all log messages (disables filtering of levels) */
    ALL   = 0xFF
#endif
};

#if defined (DOXYGEN_FORCED)
/**
 * @brief a macro that (if defined) will reverse the order of the log levels
 *
 * This macro simply changes the values assigned to the enumeration values:
 * - ERROR = 040
 * - WARN  = 030
 * - INFO  = 020
 * - DEBUG = 010
 * - ALL   = 1
 */
#define RF24LOG_REVERSE_LVL_ORDER
#endif

/**@} */

#endif /* SRC_RF24LOGLEVEL_H_ */
