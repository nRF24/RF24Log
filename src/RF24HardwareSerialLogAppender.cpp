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
      const __FlashStringHelper *vendorId, const char *message, ...)
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

   // print formatted message
   va_list args;
   va_start(args, message);
   appendFormattedMessage(message, args);
   this->serial->println("");
}

void RF24HardwareSerialLogAppender::append(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const __FlashStringHelper *message,
      ...)
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

   // print formatted message
   va_list args;
   va_start(args, message);
   appendFormattedMessage(message, args);
   this->serial->println("");
}

void RF24HardwareSerialLogAppender::appendFormattedMessage(const char *format,
      va_list args)
{
   for (; *format != 0; ++format)
   {
      if (*format == '%')
      {
         ++format;
         appendFormat(*format, &args);
      }
      else
      {
         serial->print(*format);
      }
   }
}

void RF24HardwareSerialLogAppender::appendFormattedMessage(
      const __FlashStringHelper *format, va_list args)
{
   PGM_P p = reinterpret_cast<PGM_P>(format);
   char c = pgm_read_byte(p++);
   for (; c != 0; c = pgm_read_byte(p++))
   {
      if (c == '%')
      {
         c = pgm_read_byte(p++);
         appendFormat(c, &args);
      }
      else
      {
         serial->print(c);
      }
   }
}

void RF24HardwareSerialLogAppender::appendFormat(const char format,
      va_list *args)
{
   if (format == 's')
   {
      // print text from RAM
      register char *s = (char*) va_arg(*args, int);
      serial->print(s);

      return;
   }

   if (format == 'S')
   {
      // print text from FLASH
      register __FlashStringHelper *s = (__FlashStringHelper*) va_arg(*args,
            int);
      serial->print(s);

      return;
   }

   serial->print(format);
}
