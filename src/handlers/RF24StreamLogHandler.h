/**
 * @file RF24StreamLogHandler.h
 *
 * Created on: 2 Oct 2020
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *    2020        Witold Markowski (wmarkow)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_HANDLERS_RF24STREAMLOGHANDLER_H_
#define SRC_HANDLERS_RF24STREAMLOGHANDLER_H_

#include <RF24LogHandler.h>
#include <Stream.h>

/**
 * A log handler implementation which outputs log messages to a stream.
 */
class RF24StreamLogHandler : public RF24LogHandler
{
private:
   Stream *stream;
   void appendTimestamp();
   void appendLogLevel(RF24LogLevel logLevel);
   void appendVendorId(const __FlashStringHelper *vendorId);

public:
   RF24StreamLogHandler(Stream *stream);
   void log(RF24LogLevel logLevel, const __FlashStringHelper *vendorId,
         const char *message, va_list args);

   void log(RF24LogLevel logLevel, const __FlashStringHelper *vendorId,
         const __FlashStringHelper *message, va_list args);

protected:
   void appendFormattedMessage(const char *format, va_list args);
   void appendFormattedMessage(const __FlashStringHelper *format, va_list args);
   void appendFormat(const char format, va_list *args);
};

#endif /* SRC_HANDLERS_RF24STREAMLOGHANDLER_H_ */
