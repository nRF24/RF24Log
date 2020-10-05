/*
 * RF24SerialPortLogAppender.h
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */

#ifndef LIBRARIES_RF24LOG_SRC_RF24HARDWARESERIALLOGAPPENDER_H_
#define LIBRARIES_RF24LOG_SRC_RF24HARDWARESERIALLOGAPPENDER_H_

#include <HardwareSerial.h>
#include "RF24LogAppender.h"

class RF24HardwareSerialLogAppender : public RF24LogAppender
{
private:
   HardwareSerial *serial;
public:
   RF24HardwareSerialLogAppender(HardwareSerial *serial);
   void append(uint8_t logLevel, const __FlashStringHelper *vendorId,
         const char *message);

   void append(uint8_t logLevel, const __FlashStringHelper *vendorId,
         const __FlashStringHelper *message);
};

#endif /* LIBRARIES_RF24LOG_SRC_RF24HARDWARESERIALLOGAPPENDER_H_ */
