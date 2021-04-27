/**
 * @file PrintfLogger.cpp
 * @date created 2021-04-24
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C)
 *     2021    Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#ifdef ARDUINO
#include <Arduino.h> // millis()
#elif defined (PICO_BUILD)
#include <pico-sdk/stdlib.h> // to_us_since_boot(), absolute_time()
#else
#include <ctime> // for time_t, struct tm*, time(), localtime(), strftime()
#endif
#include "PrintfLogger.h"

/** description of the @ref ERROR base level */
const char rf24logLevelError[] = "ERROR";
/** description of the @ref WARN base level */
const char rf24logLevelWarn[] = " WARN";
/** description of the @ref INFO base level */
const char rf24logLevelInfo[] = " INFO";
/** description of the @ref DEBUG base level */
const char rf24logLevelDebug[] = "DEBUG";
/** collection of the base level descriptions */
const char *const rf24LogLevels[] = {rf24logLevelError,
                                     rf24logLevelWarn,
                                     rf24logLevelInfo,
                                     rf24logLevelDebug};

PrintfLogger::PrintfLogger(int (*_stream)(const char *, ...))
{
    stream = _stream;
}

void PrintfLogger::write(uint8_t logLevel,
                         const char *vendorId,
                         const char *message,
                         va_list *args)
{
    appendTimestamp();
    appendLogLevel(logLevel);
    stream(vendorId);
    stream(";");

    // print formatted message
    appendFormattedMessage(message, args);
    #ifndef RF24LOG_NO_EOL
    stream("\n");
    #endif
}

void PrintfLogger::appendTimestamp()
{
    #if defined(PICO_BUILD)
    stream("%12lu;", to_us_since_boot(adbsolute_time()));
    #elif defined (ARDUINO)
    stream("%12lu;", millis());
    #else // !defined (PICO_BUILD) && !defined (ARDUINO)
    char buffer[21];
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 21, "%F:%H:%M:%S;", timeinfo);
    stream(buffer);
    #endif // defined (PICO_BUILD) && !defined (ARDUINO)
}

void PrintfLogger::appendLogLevel(uint8_t logLevel)
{
    uint8_t subLevel = logLevel & 0x07;

    if (logLevel >= RF24LogLevel::ERROR && logLevel <= RF24LogLevel::DEBUG + 7)
    {
        uint8_t logIndex = ((logLevel & 0x38) >> 3) - 1;
        stream(rf24LogLevels[logIndex]);

        if(subLevel)
        {
            stream(":%d;", subLevel);
        }
        else
        {
            stream("  ;");
        }

        return;
    }

    stream("Lvl%4i;", logLevel);
}

void PrintfLogger::appendFormattedMessage(const char *format, va_list *args)
{
    stream(format, args);
}
