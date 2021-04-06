/**
 * @file RF24AbstractLogHandler.cpp
 *
 * Created on: 3 Apr 2021
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

#include "RF24AbstractLogHandler.h"

RF24AbstractLogHandler::RF24AbstractLogHandler()
{
    this->logLevel = RF24LogLevel::INFO;
}

void RF24AbstractLogHandler::setLogLevel(uint8_t logLevel)
{
    this->logLevel = logLevel;
}

void RF24AbstractLogHandler::log(uint8_t logLevel,
                                 const __FlashStringHelper *vendorId,
                                 const char *message,
                                 va_list *args)
{
    if (logLevel > this->logLevel)
    {
        return;
    }

    write(logLevel, vendorId, message, args);
}

void RF24AbstractLogHandler::log(uint8_t logLevel,
                                 const __FlashStringHelper *vendorId,
                                 const __FlashStringHelper *message,
                                 va_list *args)
{
    if (logLevel > this->logLevel)
    {
        return;
    }

    write(logLevel, vendorId, message, args);
}
