/*
 * RF24LogAppender.h
 *
 *  Created on: 2 paź 2020
 *      Author: wmarkowski
 */

#ifndef SRC_RF24LOGAPPENDER_H_
#define SRC_RF24LOGAPPENDER_H_

#include <WString.h>
#include <stdint.h>
#include "RF24LogLevel.h"

class RF24LogAppender
{
public:
   virtual void append(RF24LogLevel logLevel,
         const __FlashStringHelper *vendorId, const char *message);

   virtual void append(RF24LogLevel logLevel,
         const __FlashStringHelper *vendorId,
         const __FlashStringHelper *message);
};

#endif /* SRC_RF24LOGAPPENDER_H_ */
