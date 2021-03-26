/**
 * @file RF24Log_config.h
 *
 * Copyright (C)
 *  2021        Brendan Doherty (2bndy5)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#define RF24Log_VERSION_MAJOR @RF24Log_VERSION_MAJOR@
#define RF24Log_VERSION_MINOR @RF24Log_VERSION_MINOR@
#define RF24Log_VERSION_PATCH @RF24Log_VERSION_PATCH@

#ifndef ARDUINO

#include <cstdint> // uint8_t
#include <string>  // std::string
#include <ostream> // std::ostream, std::endl
#include <ctime>   // time_t, time(), ctime()

#define Stream_t std::ostream
#define endl std::endl

#else // defined(ARDUINO)
#include "PrintOut.h"
#endif // defined(ARDUINO)

#ifndef PROGMEM
#define PROGMEM
#endif

#ifndef pgm_read_ptr
#define pgm_read_ptr(p) (*(p))
#endif

#define rf24_min(a, b) (a < b ? a : b)
