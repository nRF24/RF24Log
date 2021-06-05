/**
 * @file PrintfParser.h
 * @brief Mechanisms for parsing the log messages before they are output to a stream
 * @date Created 4 May 2021
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C) <br>
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24LOGPARTS_PARSING_H_
#define SRC_RF24LOGPARTS_PARSING_H_

#include <stdint.h>
#include "AbstractHandler.h"
#include "AbstractStream.h"

/** @brief class that holds the RF24Log's in-house printf-like parsing */
class RF24LogPrintfParser : public RF24LogAbstractHandler, public RF24LogAbstractStream
{
protected:
    void write(uint8_t logLevel,
               const char *vendorId,
               const char *message,
               va_list *args);

#if defined (ARDUINO_ARCH_AVR)
    void write(uint8_t logLevel,
               const __FlashStringHelper *vendorId,
               const __FlashStringHelper *message,
               va_list *args);
#endif
};

#endif /* SRC_RF24LOGPARTS_PARSING_H_ */
