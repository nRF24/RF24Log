/**
 * @file RF24Logging.cpp
 * @date Created 2 Oct 2020
 * @author Witold Markowski (wmarkow)
 * @copyright Copyright (C) <br>
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#include <RF24Logging.h>

RF24Logging::RF24Logging()
{
    this->handler = nullptr;
}

void RF24Logging::setHandler(RF24LogBaseHandler *handler)
{
    this->handler = handler;
}

void RF24Logging::log(uint8_t logLevel, const char *vendorId, const char *message, ...)
{
    if (handler != nullptr)
    {
        va_list args;
        va_start(args, message);
        handler->log(logLevel, vendorId, message, &args);
        va_end(args);
    }
}

#if defined (ARDUINO_ARCH_AVR)
void RF24Logging::log(uint8_t logLevel, const __FlashStringHelper *vendorId, const __FlashStringHelper *message, ...)
{
    if (handler != nullptr)
    {
        va_list args;
        va_start(args, message);
        handler->log(logLevel, vendorId, message, &args);
        va_end(args);
    }
}
#endif

// default logger instance
RF24Logging rf24Logging;
