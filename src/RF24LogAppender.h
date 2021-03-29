/**
 * @file RF24LogAppender.h
 *
 * Created on: 2 paź 2020
 *     Author: wmarkowski
 *
 * Copyright (C)
 *    2020        Witold Markowski (wmarkow)
 *    2021        Brendan Doherty (2bndy5)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24LOGAPPENDER_H_
#define SRC_RF24LOGAPPENDER_H_

#include <WString.h>
#include <stdint.h>
#include <stdarg.h>
#include "RF24LogLevel.h"

/**
 * A base class for delegating messages to a stream.
 */
class RF24LogAppender
{
public:
      /**
       * direct messages to a stream.
       * @param logLevel the level of the logging message
       * @param vendorId The prefixed origin of the message
       * @param message The message
       */
      virtual void append(RF24LogLevel logLevel,
                          const __FlashStringHelper *vendorId,
                          const char *message,
                          ...);

      /**
       * direct messages to a stream.
       * @param logLevel the level of the logging message
       * @param vendorId The prefixed origin of the message
       * @param message The message
       */
      virtual void append(RF24LogLevel logLevel,
                          const __FlashStringHelper *vendorId,
                          const __FlashStringHelper *message,
                          ...);
};

#endif /* SRC_RF24LOGAPPENDER_H_ */
