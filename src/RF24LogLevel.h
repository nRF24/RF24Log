/*
 * RF24LogLevel.h
 *
 *  Created on: 5 paź 2020
 *      Author: wmarkowski
 */

#ifndef SRC_RF24LOGLEVEL_H_
#define SRC_RF24LOGLEVEL_H_

#include <avr/pgmspace.h>

enum RF24LogLevel : uint8_t
{
   ERROR = 0, WARN, INFO, DEBUG, TRACE
};

#endif /* SRC_RF24LOGLEVEL_H_ */
