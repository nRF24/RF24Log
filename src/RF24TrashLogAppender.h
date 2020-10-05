/*
 * RF24TrashAppender.h
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */

#ifndef SRC_RF24TRASHLOGAPPENDER_H_
#define SRC_RF24TRASHLOGAPPENDER_H_

#include "RF24LogAppender.h"

class RF24TrashLogAppender : public RF24LogAppender
{
public:
   RF24TrashLogAppender();
   void append(RF24LogLevel logLevel, const __FlashStringHelper *vendorId,
         const char *message, ...);

   void append(RF24LogLevel logLevel, const __FlashStringHelper *vendorId,
         const __FlashStringHelper *message, ...);
};

#endif /* SRC_RF24TRASHLOGAPPENDER_H_ */
