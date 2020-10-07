/*
 * RF24Logger.h
 *
 *  Created on: 2 paź 2020
 *      Author: wmarkowski
 */

#ifndef SRC_RF24LOGGER_H_
#define SRC_RF24LOGGER_H_

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
   RF24Logger();
   void setAppender(RF24LogAppender *appender);
   template<class T, typename ... Args> void error(
         const __FlashStringHelper *vendorId, T message, Args ...args)
   {
      if (appender == NULL)
      {
         return;
      }
      appender->append(RF24LogLevel::ERROR, vendorId, message, args...);
   }

   template<class T, typename ... Args> void warn(
         const __FlashStringHelper *vendorId, T message, Args ...args)
   {
      if (appender == NULL)
      {
         return;
      }
      appender->append(RF24LogLevel::WARN, vendorId, message, args...);
   }

   template<class T, typename ... Args> void info(
         const __FlashStringHelper *vendorId, T message, Args ...args)
   {
      if (appender == NULL)
      {
         return;
      }
      appender->append(RF24LogLevel::INFO, vendorId, message, args...);
   }

   template<class T, typename ... Args> void debug(
         const __FlashStringHelper *vendorId, T message, Args ...args)
   {
      if (appender == NULL)
      {
         return;
      }
      appender->append(RF24LogLevel::DEBUG, vendorId, message, args...);
   }

   template<class T, typename ... Args> void trace(
         const __FlashStringHelper *vendorId, T message, Args ...args)
   {
      if (appender == NULL)
      {
         return;
      }
      appender->append(RF24LogLevel::TRACE, vendorId, message, args...);
   }
};

extern RF24Logger rf24Logger;
#endif /* SRC_RF24LOGGER_H_ */
