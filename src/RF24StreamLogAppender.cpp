/*
 * RF24StreamLogAppender.cpp
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */
#include <Arduino.h>

#include "RF24StreamLogAppender.h"

const char rf24logLevelError[] = "ERROR";
const char rf24logLevelWarn[] = " WARN";
const char rf24logLevelInfo[] = " INFO";
const char rf24logLevelDebug[] = "DEBUG";
const char rf24logLevelTrace[] = "TRACE";

const char *const rf24LogLevels[] =
{ rf24logLevelError, rf24logLevelWarn, rf24logLevelInfo, rf24logLevelDebug,
      rf24logLevelTrace };

RF24StreamLogAppender::RF24StreamLogAppender(Stream *stream)
{
   this->stream = stream;
}

void RF24StreamLogAppender::append(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const char *message, ...)
{
   appendTimestamp();
   appendLogLevel(logLevel);
   appendVendorId(vendorId);

   // print formatted message
   va_list args;
   va_start(args, message);
   appendFormattedMessage(message, args);
   stream->println("");
}

void RF24StreamLogAppender::append(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const __FlashStringHelper *message,
      ...)
{
   appendTimestamp();
   appendLogLevel(logLevel);
   appendVendorId(vendorId);

   // print formatted message
   va_list args;
   va_start(args, message);
   appendFormattedMessage(message, args);
   stream->println("");
}

void RF24StreamLogAppender::appendFormattedMessage(const char *format,
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
         stream->print(*format);
      }
   }
}

void RF24StreamLogAppender::appendFormattedMessage(
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
         stream->print(c);
      }
   }
}

void RF24StreamLogAppender::appendFormat(const char format, va_list *args)
{
   if (format == 's')
   {
      // print text from RAM
      register char *s = (char*) va_arg(*args, int);
      stream->print(s);

      return;
   }

   if (format == 'S')
   {
      // print text from FLASH
      register __FlashStringHelper *s = (__FlashStringHelper*) va_arg(*args,
            int);
      stream->print(s);

      return;
   }

   stream->print(format);
}

void RF24StreamLogAppender::appendTimestamp()
{
   char c[12];
   sprintf(c, "%10lu ", millis());
   stream->print(c);
   stream->print(" ");
}

void RF24StreamLogAppender::appendLogLevel(RF24LogLevel logLevel)
{
   stream->print(rf24LogLevels[logLevel]);
   stream->print(" ");
}

void RF24StreamLogAppender::appendVendorId(const __FlashStringHelper *vendorId)
{
   stream->print(vendorId);
   stream->print(" ");
}
