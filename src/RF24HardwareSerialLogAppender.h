/*
 * RF24SerialPortLogAppender.h
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */

#ifndef SRC_RF24HARDWARESERIALLOGAPPENDER_H_
#define SRC_RF24HARDWARESERIALLOGAPPENDER_H_

#include <HardwareSerial.h>
#include "RF24LogAppender.h"

class RF24HardwareSerialLogAppender : public RF24LogAppender
{
private:
   HardwareSerial *serial;
public:
   RF24HardwareSerialLogAppender(HardwareSerial *serial);
   void append(RF24LogLevel logLevel, const __FlashStringHelper *vendorId,
         const char *message, ...);

   void append(RF24LogLevel logLevel, const __FlashStringHelper *vendorId,
         const __FlashStringHelper *message, ...);

protected:
   void appendFormattedMessage(const char *format, va_list args);
   void appendFormattedMessage(const __FlashStringHelper *format, va_list args);
   void appendFormat(const char format, va_list *args);
};

#endif /* SRC_RF24HARDWARESERIALLOGAPPENDER_H_ */
