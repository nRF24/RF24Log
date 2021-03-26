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

/** for use with CMake */
#define RF24Log_VERSION_MAJOR @RF24Log_VERSION_MAJOR@
/** for use with CMake */
#define RF24Log_VERSION_MINOR @RF24Log_VERSION_MINOR@
/** for use with CMake */
#define RF24Log_VERSION_PATCH @RF24Log_VERSION_PATCH@

#ifndef ARDUINO

#include <cstdint> // uint8_t
#include <string>  // std::string
#include <ostream> // std::ostream, std::endl
#include <ctime>   // time_t, time(), ctime()

/**
 * @defgroup streamTypeDoc StreamType
 * This is just a placeholder for documenting the datatype of the output stream that will be
 * used by the instance of a RF24Logger.
 * @{
 */
/** This macro will represent the `ostream`class for non-Arduino-based API. */
#define Stream_t std::ostream
/** @} */

#else // defined(ARDUINO)
#include "PrintOut.h"
#endif // defined(ARDUINO)

#ifndef PROGMEM
/** A macro to bridge the gap between platforms that don't have it */
#define PROGMEM
#endif

#ifndef pgm_read_ptr
/** A macro to bridge the gap between platforms that don't have it */
#define pgm_read_ptr(p) (*(p))
#endif

/** A macro to compute the minimum value of 2 parameters */
#define rf24_min(a, b) (a < b ? a : b)
