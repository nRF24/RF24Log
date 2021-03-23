/**
 * @file RF24LogLevel.h
 *
 * Created on: 2 paź 2020
 *     Author: wmarkowski
 *
 * Copyright (C) 2020 Witold Markowski (wmarkow)
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

enum RF24LogLevel : uint8_t
{
   ERROR = 0,
   WARN,
   INFO,
   DEBUG,
   TRACE
};

#endif /* SRC_RF24LOGLEVEL_H_ */
