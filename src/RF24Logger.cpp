/**
 * @file RF24Logger.cpp
 *
 * Created on: 2 paź 2020
 *     Author: wmarkowski
 *
 * Copyright (C) 2020 Witold Markowski (wmarkow)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#include "RF24Logger.h"

RF24Logger::RF24Logger()
{
   this->appender = nullptr;
}

void RF24Logger::setAppender(RF24LogAppender *appender)
{
   this->appender = appender;
}

// default logger instance
RF24Logger rf24Logger;
