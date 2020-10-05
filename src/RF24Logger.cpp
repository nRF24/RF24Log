/*
 * RF24Logger.cpp
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */
#include "RF24Logger.h"
#include "RF24TrashLogAppender.h"

RF24Logger::RF24Logger(RF24LogAppender *appender)
{
   this->appender = appender;
}

void RF24Logger::setAppender(RF24LogAppender *appender)
{
   this->appender = appender;
}

// default global appender instance: it is trash log appender
RF24TrashLogAppender rf24TrashLogAppender;
// default logger instance
RF24Logger rf24Logger(&rf24TrashLogAppender);
