/**
 * @file RF24LogParts/common.h
 * @brief global functions for RF24Log Abstract objects.
 * @date Created 4 May 2021
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#ifndef SRC_RF24ABSTRACT_COMMON_H_
#define SRC_RF24ABSTRACT_COMMON_H_

#include <stdint.h>

/**
 * @brief how wide (in characters) does it take to display a number
 * @param numb The number to represent
 * @param base The base counting scheme. Defaults to 10 for decimal counting system
 */
uint16_t numbCharsToPrint(int64_t numb, uint8_t base = 10);

#endif /* SRC_RF24ABSTRACT_COMMON_H_ */