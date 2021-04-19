/**
 * @file RF24DualLogHandler.h
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

#ifndef SRC_HANDLERS_RF24DUALLOGHANDLER_H_
#define SRC_HANDLERS_RF24DUALLOGHANDLER_H_

#include <RF24LogHandler.h>

/**
 * A log handler implementation which redirects log messages to a two other log handlers.
 */
class RF24DualLogHandler : public RF24LogHandler
{
private:
    RF24LogHandler *handler1;
    RF24LogHandler *handler2;

public:

    /**
     * @brief Instance constructor
     * @param handler1 An output stream handler
     * @param handler2 An output stream handler
     */
    RF24DualLogHandler(RF24LogHandler *handler1, RF24LogHandler *handler2);

    void log(uint8_t logLevel,
             const char *vendorId,
             const char *message,
             va_list *args);

    void setLogLevel(uint8_t logLevel);

#ifdef ARDUINO_ARCH_AVR
    void log(uint8_t logLevel,
             const __FlashStringHelper *vendorId,
             const __FlashStringHelper *message,
             va_list *args);
#endif

};

#endif /* SRC_HANDLERS_RF24DUALLOGHANDLER_H_ */
