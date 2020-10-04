/*
 * RF24SerialPortLogAppender.cpp
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */
#include <Arduino.h>
#include "RF24HardwareSerialLogAppender.h"

const char rf24logLevelError[] PROGMEM = "ERROR";
const char rf24logLevelWarn[] PROGMEM = " WARN";
const char rf24logLevelInfo[] PROGMEM = " INFO";
const char rf24logLevelDebug[] PROGMEM = "DEBUG";
const char rf24logLevelTrace[] PROGMEM = "TRACE";

//const char rf24LogLevels[] PROGMEM = {"ERROR", " WARN", " INFO", "DEBUG", "TRACE"};
const char *const rf24LogLevels[] PROGMEM =
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
   //Serial.println(logLevel);
   //this->serial->print((const __FlashStringHelper*) rf24LogLevels[logLevel]);
   char c[12];
   sprintf(c, "%10lu ", millis());
   this->serial->print(c);
   this->serial->print(" ");

   switch (logLevel)
   {
      case ERROR:
         this->serial->print((const __FlashStringHelper*) rf24logLevelError);
         break;
      case WARN:
         this->serial->print((const __FlashStringHelper*) rf24logLevelWarn);
         break;
      case INFO:
         this->serial->print((const __FlashStringHelper*) rf24logLevelInfo);
         break;
      case DEBUG:
         this->serial->print((const __FlashStringHelper*) rf24logLevelDebug);
         break;
      case TRACE:
         this->serial->print((const __FlashStringHelper*) rf24logLevelTrace);
         break;
   }
   this->serial->print(" ");
   this->serial->print(vendorId);
   this->serial->print(" ");
   this->serial->println(message);
}

void RF24HardwareSerialLogAppender::append(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const __FlashStringHelper *message)
{
   char c[12];
   sprintf(c, "%10lu ", millis());
   this->serial->print(c);
   this->serial->print(" ");

   switch (logLevel)
   {
      case ERROR:
         this->serial->print((const __FlashStringHelper*) rf24logLevelError);
         break;
      case WARN:
         this->serial->print((const __FlashStringHelper*) rf24logLevelWarn);
         break;
      case INFO:
         this->serial->print((const __FlashStringHelper*) rf24logLevelInfo);
         break;
      case DEBUG:
         this->serial->print((const __FlashStringHelper*) rf24logLevelDebug);
         break;
      case TRACE:
         this->serial->print((const __FlashStringHelper*) rf24logLevelTrace);
         break;
   }
   this->serial->print(" ");
   this->serial->print(vendorId);
   this->serial->print(" ");
   this->serial->println(message);
}

