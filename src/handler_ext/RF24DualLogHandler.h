/**
 * @file RF24DualLogHandler.h
 * @brief handler extention to manage 2 handlers
 * @date Created 30 Mar 2021
 * @author Witold Markowski (wmarkow)
 * @copyright Copyright (C) <br>
 *     2020    Witold Markowski (wmarkow) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_HANDLER_EXT_RF24DUALLOGHANDLER_H_
#define SRC_HANDLER_EXT_RF24DUALLOGHANDLER_H_

#include "../RF24LogBaseHandler.h"

/** @brief Module to extend the RF24LogBaseHandler mechanism for redirecting to 2 different RF24LogBaseHandler objects. */
class RF24DualLogHandler : public RF24LogBaseHandler
{
private:
    RF24LogBaseHandler *handler1;
    RF24LogBaseHandler *handler2;

public:

    /**
     * @brief Instance constructor
     * @param handler1 An output stream handler
     * @param handler2 An output stream handler
     */
    RF24DualLogHandler(RF24LogBaseHandler *handler1, RF24LogBaseHandler *handler2);

    void log(uint8_t logLevel,
             const char *vendorId,
             const char *message,
             va_list *args);

    void setLogLevel(uint8_t logLevel);

#if defined (ARDUINO_ARCH_AVR)
    void log(uint8_t logLevel,
             const __FlashStringHelper *vendorId,
             const __FlashStringHelper *message,
             va_list *args);
#endif

};

#endif /* SRC_HANDLER_EXT_RF24DUALLOGHANDLER_H_ */
