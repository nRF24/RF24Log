/**
 * @file AbstractHandler.h
 * @brief abstract class that allows custom handlers agnostic to any output stream APIs
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

#ifndef SRC_RF24LOGPARTS_HANDLER_H_
#define SRC_RF24LOGPARTS_HANDLER_H_
#if defined (ARDUINO)
#include <WString.h> // __FlashStringHelper
#endif
#include <stdint.h>
#include <stdarg.h>

#include "../RF24LogBaseHandler.h"
#include "../RF24LogLevel.h"


/** @brief An abstract base class for handling log messages. */
class RF24LogAbstractHandler : public RF24LogBaseHandler
{

private:

    /**
     * @brief is logging enabled for a certain level?
     * @param logLevel The Log level to test if enabled.
     * @return true if the log messages are enabled for the specified @p logLevel; false otherwise.
     */
    bool isLevelEnabled(uint8_t logLevel);

public:

    /** @brief Sets log level to @ref INFO upon instantiation. */
    RF24LogAbstractHandler();

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

protected:

    /** The configured log level used to filter which messages are output. */
    uint8_t _logLevel;

    /**
     * write log message to its destination
     * @param logLevel The level of the logging message
     * @param vendorId The prefixed origin of the message
     * @param message The message
     * @param args The sequence of variables used to replace the format specifiers in the
     * same order for which they appear in the @p message
     */
    virtual void write(uint8_t logLevel,
                       const char *vendorId,
                       const char *message,
                       va_list *args) = 0;

#if defined (ARDUINO_ARCH_AVR)
    virtual void write(uint8_t logLevel,
                       const __FlashStringHelper *vendorId,
                       const __FlashStringHelper *message,
                       va_list *args) = 0;
#endif
};


#endif /* SRC_RF24LOGPARTS_HANDLER_H_ */
