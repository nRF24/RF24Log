/*
 * RF24Logger.cpp
 *
 *  Created on: 3 paź 2020
 *      Author: wmarkowski
 */
#include "RF24Logger.h"

RF24Logger::RF24Logger()
{
   this->appender = NULL;
}

void RF24Logger::setAppender(RF24LogAppender *appender)
{
   this->appender = appender;
}

// default logger instance
RF24Logger rf24Logger;
