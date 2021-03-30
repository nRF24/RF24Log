/**
 * @file RF24LogLevel.h
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

#ifndef SRC_RF24LOGLEVEL_H_
#define SRC_RF24LOGLEVEL_H_

#include <avr/pgmspace.h>

/** the predefined logging levels */
enum RF24LogLevel : uint8_t
{
   /** the level to specify an error message */
   ERROR = 0,
   /** the level to specify an warning message */
   WARN,
   /** the level to specify an informational message */
   INFO,
   /** the level to specify an debugging message */
   DEBUG,
   /** the level to specify an traceback message */
   TRACE
};

#endif /* SRC_RF24LOGLEVEL_H_ */