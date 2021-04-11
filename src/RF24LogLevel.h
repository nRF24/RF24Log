/**
 * @file RF24LogLevel.h
 *
 * Created on: 2 Oct 2020
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5)
 *
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
 * @{
 */
/**
 * @brief the predefined logging levels
 *
 * These named levels are the base or parent levels. They increment in in octal counts of `010`.
 * Each base level can have up to 7 additional sublevels. <br>For example:
 * - a level of 031 is the first sublevel of @ref INFO verbosity
 * - a level of 037 is the last sublevel of @ref INFO verbosity
 *
 * If the log level is configured (using RF24LogHandler::setLogLevel()) for a verbosty of `020` prevents outputting all messages designated for
 * any log level greater than `020`.
 */
enum RF24LogLevel : uint8_t
{
    /** (`0`) the level to disable all log messages */
    OFF = 0,
    /** (`010`) the level to specify an error message */
    ERROR = 010,
    /** (`020`) the level to specify an warning message */
    WARN = 020,
    /** (`030`) the level to specify an informational message */
    INFO = 030,
    /** (`040`) the level to specify an debugging message */
    DEBUG = 040,
    /** (`0377` or `0xFF`) the level to enable all log messages (disables filtering of levels) */
    ALL = 0xFF
};
/**@} */
#endif /* SRC_RF24LOGLEVEL_H_ */
