/*
 * RF24LogLevel.h
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */

#ifndef LIBRARIES_RF24LOG_SRC_RF24LOGLEVEL_H_
#define LIBRARIES_RF24LOG_SRC_RF24LOGLEVEL_H_

#include <avr/pgmspace.h>

enum RF24LogLevel
{
   ERROR = 0, WARN = 1, INFO = 2, DEBUG = 3, TRACE = 4
};

#endif /* LIBRARIES_RF24LOG_SRC_RF24LOGLEVEL_H_ */
