/**
 * @file RF24LogHandler.h
 *
 * Created on: 2 Oct 2020
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24LOGHANDLER_H_
#define SRC_RF24LOGHANDLER_H_

#include <WString.h>
#include <stdint.h>
#include <stdarg.h>
#include "RF24LogLevel.h"

/**
 * A base class for handling log messages.
 */
class RF24LogHandler
{
public:
    /**
     * @brief log a message.
     * @param logLevel the level of the logging message
     * @param vendorId The prefixed origin of the message
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%f` for floats).
     * @param args the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    virtual void log(uint8_t logLevel,
                     const __FlashStringHelper *vendorId,
                     const char *message,
                     va_list *args);

    /**
     * @brief log a message.
     * @param logLevel the level of the logging message
     * @param vendorId The prefixed origin of the message
     * @param message The message format string. Review [the printf spcifiers](https://www.cplusplus.com/reference/cstdio/printf/),
     * but note that not all are supported on certain MCU architectures (eg `%%f` for floats).
     * @param args the sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    virtual void log(uint8_t logLevel,
                     const __FlashStringHelper *vendorId,
                     const __FlashStringHelper *message,
                     va_list *args);

    /**
     * set the maximal level of the logged messages.
     * @param logLevel The verbosity level used to filter which of the logged messages
     * are output.
     * @see Review the descriptions in the @ref RF24LogLevel
     */
    virtual void setLogLevel(uint8_t logLevel);
};

#endif /* SRC_RF24LOGHANDLER_H_ */