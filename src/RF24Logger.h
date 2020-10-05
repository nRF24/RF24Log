/*
 * RF24Logger.h
 *
 *  Created on: 2 paź 2020
 *      Author: wmarkowski
 */

#ifndef LIBRARIES_RF24LOG_SRC_RF24LOGGER_H_
#define LIBRARIES_RF24LOG_SRC_RF24LOGGER_H_

#include <WString.h>
#include "RF24LogLevel.h"
#include "RF24LogAppender.h"

#define RF24_LOG_LEVEL_ERROR 0
#define RF24_LOG_LEVEL_WARN 1
#define RF24_LOG_LEVEL_INFO 2
#define RF24_LOG_LEVEL_DEBUG 3
#define RF24_LOG_LEVEL_TRACE 4

class RF24Logger
{
private:
   RF24LogAppender *appender;

public:
   RF24Logger(RF24LogAppender *appender);
   void setAppender(RF24LogAppender *appender);
//   void error(const __FlashStringHelper *vendorId, char *message);
   template<class T> void error(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(RF24LogLevel::ERROR, vendorId, message);
   }

//   void warn(const __FlashStringHelper *vendorId, char *message);
   template<class T> void warn(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(RF24LogLevel::WARN, vendorId, message);
   }

   template<class T> void info(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(RF24LogLevel::INFO, vendorId, message);
   }

//   void debug(const __FlashStringHelper *vendorId, char *message);
   template<class T> void debug(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(RF24LogLevel::DEBUG, vendorId, message);
   }

//   void trace(const __FlashStringHelper *vendorId, char *message);
   template<class T> void trace(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(RF24LogLevel::TRACE, vendorId, message);
   }
};

extern RF24Logger rf24Logger;
#endif /* LIBRARIES_RF24LOG_SRC_RF24LOGGER_H_ */
