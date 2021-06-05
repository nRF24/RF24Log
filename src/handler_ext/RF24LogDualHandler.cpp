/**
 * @file RF24LogDualHandler.cpp
 *
 * Created on: 30 Mar 2021
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

#include "RF24LogDualHandler.h"

RF24LogDualHandler::RF24LogDualHandler(RF24LogBaseHandler *handler1,
                                       RF24LogBaseHandler *handler2)
{
    this->handler1 = handler1;
    this->handler2 = handler2;
}

void RF24LogDualHandler::log(uint8_t logLevel,
                             const char *vendorId,
                             const char *message,
                             va_list *args)
{
    // va_list can be iterated only once.
    // Since we have here two handlers, we need to copy arguments.
    va_list args2;
    va_copy(args2, *args);

    // redirect logs to wrapped handlers
    handler1->log(logLevel, vendorId, message, args);
    handler2->log(logLevel, vendorId, message, &args2);
    va_end(args2);
}

void RF24LogDualHandler::setLogLevel(uint8_t logLevel)
{
    handler1->setLogLevel(logLevel);
    handler2->setLogLevel(logLevel);
}

#if defined (ARDUINO_ARCH_AVR)
void RF24LogDualHandler::log(uint8_t logLevel,
                             const __FlashStringHelper *vendorId,
                             const __FlashStringHelper *message,
                             va_list *args)
{
    // va_list can be iterated only once.
    // Since we have here two handlers, we need to copy arguments.
    va_list args2;
    va_copy(args2, *args);

    // redirect logs to wrapped handlers
    handler1->log(logLevel, vendorId, message, args);
    handler2->log(logLevel, vendorId, message, &args2);
    va_end(args2);
}
#endif
