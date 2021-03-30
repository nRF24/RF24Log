/**
 * @file RF24DualLogHandler.cpp
 *
 * Created on: 30 Mar 2021
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *    2021        Witold Markowski (wmarkow)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include <Arduino.h>

#include <handlers/RF24DualLogHandler.h>

RF24DualLogHandler::RF24DualLogHandler(RF24LogHandler *handler1,
      RF24LogHandler *handler2)
{
   this->handler1 = handler1;
   this->handler2 = handler2;
}

void RF24DualLogHandler::log(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const char *message, va_list args)
{

   handler1->log(logLevel, vendorId, message, args);
   handler2->log(logLevel, vendorId, message, args);
}

void RF24DualLogHandler::log(RF24LogLevel logLevel,
      const __FlashStringHelper *vendorId, const __FlashStringHelper *message,
      va_list args)
{
   handler1->log(logLevel, vendorId, message, args);
   handler2->log(logLevel, vendorId, message, args);
}
