/*
 * RF24LogLevel.h
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */

#ifndef LIBRARIES_RF24LOG_SRC_RF24LOGLEVEL_H_
#define LIBRARIES_RF24LOG_SRC_RF24LOGLEVEL_H_

#include <avr/pgmspace.h>

enum RF24LogLevel : uint8_t
{
   ERROR = 0, WARN, INFO, DEBUG, TRACE
};

#endif /* LIBRARIES_RF24LOG_SRC_RF24LOGLEVEL_H_ */
