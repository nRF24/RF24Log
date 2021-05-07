/**
 * @file LevelDescriptions.h
 * @author Brendan Doherty (2bndy5)
 * @brief A collection of constants used to describe a particular logging level
 * @date Created 2021-05-06
 * @copyright Copyright (C)
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorpor ating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#ifndef SRC_RF24LOGPARTS_LEVELDESCRIPTION_H_
#define SRC_RF24LOGPARTS_LEVELDESCRIPTION_H_

/**
 * @defgroup lvlDesc Level Descriptions
 * @brief Level descriptions
 *
 * These can be modigied using RF24LOG_SHORT_DESC or RF24LOG_TERSE_DESC macros.
 * @{
 */
#if defined(RF24LOG_SHORT_DESC)
const char RF24LogDescError[] = " ERR";
const char RF24LogDescWarn[]  = "WARN";
const char RF24LogDescInfo[]  = "INFO";
const char RF24LogDescDebug[] = " DBG";
const char RF24LogDescLevel[] = "L ";

#elif defined(RF24LOG_TERSE_DESC)
const char RF24LogDescError[] = " E";
const char RF24LogDescWarn[]  = " W";
const char RF24LogDescInfo[]  = " I";
const char RF24LogDescDebug[] = "DB";
const char RF24LogDescLevel[] = "";

#else // !defined(RF24LOG_*_DESC)
/** @brief description of the @ref ERROR base level */
const char RF24LogDescError[] = "ERROR";
/** @brief description of the @ref WARN base level */
const char RF24LogDescWarn[] = " WARN";
/** @brief description of the @ref INFO base level */
const char RF24LogDescInfo[] = " INFO";
/** @brief description of the @ref DEBUG base level */
const char RF24LogDescDebug[] = "DEBUG";
/** @brief description of the @ref DEBUG base level */
const char RF24LogDescLevel[] = "Lvl ";
#endif // !defined(RF24LOG_*_DESC)

/** @brief collection of the base level descriptions */
const char * const RF24LogDescLevels[] =
{
    RF24LogDescError,
    RF24LogDescWarn,
    RF24LogDescInfo,
    RF24LogDescDebug
};

/**@} */

#endif /* SRC_RF24LOGPARTS_LEVELDESCRIPTION_H_ */
