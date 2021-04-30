/**
 * @file RF24LogLevel.h
 * @brief Order of log levels and filtering
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

#ifndef SRC_RF24LOGLEVEL_H_
#define SRC_RF24LOGLEVEL_H_

#include <stdint.h>
/**
 * @defgroup logLevels Log Levels
 * @brief Order of logging levels
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

/**
 * @defgroup lvlDesc Level Descriptions
 * @brief Level descriptions
 * @{
 */
#ifdef RF24LOG_SHORT_DESC
const char RF24LogDescError[] = " ERR";
const char RF24LogDescWarn[]  = "WARN";
const char RF24LogDescInfo[]  = "INFO";
const char RF24LogDescDebug[] = "DEBG";
const char RF24LogDescLevel[] = "Lv";

#elif defined (RF24LOG_TERSE_DESC)
const char RF24LogDescError[] = " E";
const char RF24LogDescWarn[]  = " W";
const char RF24LogDescInfo[]  = " I";
const char RF24LogDescDebug[] = "DB";
const char RF24LogDescLevel[] = "";

#else
/** description of the @ref ERROR base level */
const char RF24LogDescError[] = "ERROR";
/** description of the @ref WARN base level */
const char RF24LogDescWarn[] = " WARN";
/** description of the @ref INFO base level */
const char RF24LogDescInfo[] = " INFO";
/** description of the @ref DEBUG base level */
const char RF24LogDescDebug[] = "DEBUG";
/** description of the @ref DEBUG base level */
const char RF24LogDescLevel[] = "Lvl";
#endif

/** collection of the base level descriptions */
const char * const RF24LogDescLevels[] = {RF24LogDescError,
                                          RF24LogDescWarn,
                                          RF24LogDescInfo,
                                          RF24LogDescDebug};

/**@} */
#endif /* SRC_RF24LOGLEVEL_H_ */
