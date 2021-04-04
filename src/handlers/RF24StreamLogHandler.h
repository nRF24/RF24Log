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

#include <handlers/RF24AbstractLogHandler.h>
#include <Print.h>

/**
 * A log handler implementation which outputs log messages to a stream.
 */
class RF24StreamLogHandler : public RF24AbstractLogHandler
{
protected:
    Print *stream;

public:
    RF24StreamLogHandler(Print *stream);

protected:
    void write(uint8_t logLevel,
               const __FlashStringHelper *vendorId,
               const char *message,
               va_list *args);

    void write(uint8_t logLevel,
               const __FlashStringHelper *vendorId,
               const __FlashStringHelper *message,
               va_list *args);

    void appendTimestamp();
    void appendLogLevel(uint8_t logLevel);
    void appendVendorId(const __FlashStringHelper *vendorId);
    void appendFormattedMessage(const char *format, va_list *args);
    void appendFormattedMessage(const __FlashStringHelper *format, va_list *args);
    void appendFormat(const char format, va_list *args);
};

#endif /* SRC_HANDLERS_RF24STREAMLOGHANDLER_H_ */
