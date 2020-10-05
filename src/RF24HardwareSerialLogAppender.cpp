/*
 * RF24SerialPortLogAppender.cpp
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */
#include <Arduino.h>
#include "RF24HardwareSerialLogAppender.h"

const char rf24logLevelError[] = "ERROR";
const char rf24logLevelWarn[] = " WARN";
const char rf24logLevelInfo[] = " INFO";
const char rf24logLevelDebug[] = "DEBUG";
const char rf24logLevelTrace[] = "TRACE";

const char *const rf24LogLevels[] =
{ rf24logLevelError, rf24logLevelWarn, rf24logLevelInfo, rf24logLevelDebug,
      rf24logLevelTrace };

RF24HardwareSerialLogAppender::RF24HardwareSerialLogAppender(
      HardwareSerial *serial)
{
   this->serial = serial;
}

void RF24HardwareSerialLogAppender::append(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const char *message)
{
   // print timestamp
   char c[12];
   sprintf(c, "%10lu ", millis());
   this->serial->print(c);
   this->serial->print(" ");

   // print log level
   this->serial->print(rf24LogLevels[logLevel]);
   this->serial->print(" ");

   // print vendor id
   this->serial->print(vendorId);
   this->serial->print(" ");

   // print message
   this->serial->println(message);
}

void RF24HardwareSerialLogAppender::append(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const __FlashStringHelper *message)
{
   // print timestamp
   char c[12];
   sprintf(c, "%10lu ", millis());
   this->serial->print(c);
   this->serial->print(" ");

   // print log level
   this->serial->print(rf24LogLevels[logLevel]);
   this->serial->print(" ");

   // print vendor id
   this->serial->print(vendorId);
   this->serial->print(" ");

   // print message
   this->serial->println(message);
}

