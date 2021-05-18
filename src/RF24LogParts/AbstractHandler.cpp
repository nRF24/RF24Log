/**
 * @file AbstractHandler.cpp
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

#include "AbstractHandler.h"

/****************************************************************************/

RF24LogAbstractHandler::RF24LogAbstractHandler()
{
    _logLevel = RF24LogLevel::INFO;
}

/****************************************************************************/

void RF24LogAbstractHandler::log(uint8_t logLevel,
                                 const char *vendorId,
                                 const char *message,
                                 va_list *args)
{
    if (isLevelEnabled(logLevel))
    {
        write(logLevel, vendorId, message, args);
    }
}

/****************************************************************************/

void RF24LogAbstractHandler::setLogLevel(uint8_t logLevel)
{
    _logLevel = logLevel;
}

/****************************************************************************/

bool RF24LogAbstractHandler::isLevelEnabled(uint8_t logLevel)
{
    return logLevel <= _logLevel;
}

/****************************************************************************/

#if defined (ARDUINO_ARCH_AVR)
void RF24LogAbstractHandler::log(uint8_t logLevel,
                                 const __FlashStringHelper *vendorId,
                                 const __FlashStringHelper *message,
                                 va_list *args)
{
    if (isLevelEnabled(logLevel))
    {
        write(logLevel, vendorId, message, args);
    }
}
#endif