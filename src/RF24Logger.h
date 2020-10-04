/*
 * RF24Logger.h
 *
 *  Created on: 2 paź 2020
 *      Author: wmarkowski
 */

#ifndef LIBRARIES_RF24LOG_SRC_RF24LOGGER_H_
#define LIBRARIES_RF24LOG_SRC_RF24LOGGER_H_

#include <WString.h>
#include "RF24LogAppender.h"

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
      appender->append(ERROR, vendorId, message);
   }

//   void warn(const __FlashStringHelper *vendorId, char *message);
   template<class T> void warn(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(WARN, vendorId, message);
   }

   template<class T> void info(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(INFO, vendorId, message);
   }

//   void debug(const __FlashStringHelper *vendorId, char *message);
   template<class T> void debug(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(DEBUG, vendorId, message);
   }

//   void trace(const __FlashStringHelper *vendorId, char *message);
   template<class T> void trace(const __FlashStringHelper *vendorId, T message)
   {
      appender->append(TRACE, vendorId, message);
   }
};

extern RF24Logger rf24Logger;
#endif /* LIBRARIES_RF24LOG_SRC_RF24LOGGER_H_ */
