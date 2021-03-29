/**
 * @file RF24StreamLogAppender.h
 *
 * Created on: 2 paź 2020
 *     Author: wmarkowski
 *
 * Copyright (C) 2020 Witold Markowski (wmarkow)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24STREAMLOGAPPENDER_H_
#define SRC_RF24STREAMLOGAPPENDER_H_

#include <Stream.h>
#include "RF24LogAppender.h"

class RF24StreamLogAppender : public RF24LogAppender
{
private:
   Stream *stream;
   void appendTimestamp();
   void appendLogLevel(RF24LogLevel logLevel);
   void appendVendorId(const __FlashStringHelper *vendorId);

public:
   RF24StreamLogAppender(Stream *stream);
   void append(RF24LogLevel logLevel, const __FlashStringHelper *vendorId,
         const char *message, ...);

   void append(RF24LogLevel logLevel, const __FlashStringHelper *vendorId,
         const __FlashStringHelper *message, ...);

protected:
   void appendFormattedMessage(const char *format, va_list args);
   void appendFormattedMessage(const __FlashStringHelper *format, va_list args);
   void appendFormat(const char format, va_list *args);
};

#endif /* SRC_RF24STREAMLOGAPPENDER_H_ */
