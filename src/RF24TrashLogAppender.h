/*
 * RF24TrashAppender.h
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */

#ifndef LIBRARIES_RF24LOG_SRC_RF24TRASHLOGAPPENDER_H_
#define LIBRARIES_RF24LOG_SRC_RF24TRASHLOGAPPENDER_H_

#include "RF24LogAppender.h"

class RF24TrashLogAppender : public RF24LogAppender
{
public:
   RF24TrashLogAppender();
   void append(uint8_t logLevel, const __FlashStringHelper *vendorId,
         const char *message);

   void append(uint8_t logLevel, const __FlashStringHelper *vendorId,
         const __FlashStringHelper *message);
};

#endif /* LIBRARIES_RF24LOG_SRC_RF24TRASHLOGAPPENDER_H_ */
