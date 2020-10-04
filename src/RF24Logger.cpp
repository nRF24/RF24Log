/*
 * RF24Logger.cpp
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */
#include "RF24Logger.h"
#include "RF24LogLevel.h"
#include "RF24TrashLogAppender.h"

RF24Logger::RF24Logger(RF24LogAppender *appender)
{
   this->appender = appender;
}

//void RF24Logger::error(const __FlashStringHelper *vendorId, char *message)
//{
//   appender->append(ERROR, vendorId, message);
//}

//void RF24Logger::warn(const __FlashStringHelper *vendorId, char *message)
//{
//   appender->append(WARN, vendorId, message);
//}

//void RF24Logger::info(const char *vendorId, char *message)
//{
//   appender->append(INFO, vendorId, message);
//}

//void RF24Logger::debug(const __FlashStringHelper *vendorId, char *message)
//{
//   appender->append(DEBUG, vendorId, message);
//}

//void RF24Logger::trace(const __FlashStringHelper *vendorId, char *message)
//{
//   appender->append(TRACE, vendorId, message);
//}

void RF24Logger::setAppender(RF24LogAppender *appender)
{
   this->appender = appender;
}

RF24TrashLogAppender rf24TrashLogAppender;
RF24Logger rf24Logger(&rf24TrashLogAppender);
