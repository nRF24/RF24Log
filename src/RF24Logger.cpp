/**
 * @file RF24Logger.cpp
 *
 * Created on: 2 Oct 2020
 *     Author: Witold Markowski (wmarkow)
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
#include <stdio.h>
#include "RF24Logger.h"

RF24Logger::RF24Logger()
{
    this->handler = nullptr;
}

void RF24Logger::setHandler(RF24LogHandler *handler)
{
    this->handler = handler;
}

void RF24Logger::error(const char *vendorId, const char *message, ...)
{
    if (handler == nullptr)
    {
        return;
    }
    va_list args;
    va_start(args, message);
    handler->log(RF24LogLevel::ERROR, vendorId, message, &args);
}

void RF24Logger::warn(const char *vendorId, const char *message, ...)
{
    if (handler == nullptr)
    {
        return;
    }
    va_list args;
    va_start(args, message);
    handler->log(RF24LogLevel::WARN, vendorId, message, &args);
}

void RF24Logger::info(const char *vendorId, const char *message, ...)
{
    if (handler == nullptr)
    {
        return;
    }
    va_list args;
    va_start(args, message);
    handler->log(RF24LogLevel::INFO, vendorId, message, &args);
}

void RF24Logger::debug(const char *vendorId, const char *message, ...)
{
    if (handler == nullptr)
    {
        return;
    }
    va_list args;
    va_start(args, message);
    handler->log(RF24LogLevel::DEBUG, vendorId, message, &args);
}

void RF24Logger::log(uint8_t logLevel, const char *vendorId, const char *message, ...)
{
    if (handler == nullptr)
    {
        return;
    }
    va_list args;
    va_start(args, message);
    handler->log(logLevel, vendorId, message, &args);
}

#if defined (ARDUINO_ARCH_AVR)
    void RF24Logger::error(const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(RF24LogLevel::ERROR, vendorId, message, &args);
    }

    void RF24Logger::warn(const __FlashStringHelper *vendorId, const __FlashStringHelper * message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(RF24LogLevel::WARN, vendorId, message, &args);
    }

    void RF24Logger::info(const __FlashStringHelper *vendorId, const __FlashStringHelper * message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(RF24LogLevel::INFO, vendorId, message, &args);
    }

    void RF24Logger::debug(const __FlashStringHelper *vendorId, const __FlashStringHelper * message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(RF24LogLevel::DEBUG, vendorId, message, &args);
    }

    void RF24Logger::log(uint8_t logLevel, const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...)
    {
        if (handler == nullptr)
        {
            return;
        }
        va_list args;
        va_start(args, message);
        handler->log(logLevel, vendorId, message, &args);
    }
#endif

// default logger instance
RF24Logger rf24Logger;
