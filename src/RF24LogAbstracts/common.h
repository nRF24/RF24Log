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