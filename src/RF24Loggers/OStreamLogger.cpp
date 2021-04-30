/**
 * @file OStreamLogger.cpp
 * @date Created 2021-04-24
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C)
 *     2021    Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */
#ifndef ARDUINO
#include <ctime> // for time_t, struct tm*, time(), localtime(), strftime()
#include "OStreamLogger.h"


OStreamLogger::OStreamLogger(std::ostream *stream)
{
    this->stream = stream;
}

void OStreamLogger::write(uint8_t logLevel,
                          const char *vendorId,
                          const char *message,
                          va_list *args)
{
    descTimeLevel(logLevel);
    *stream << vendorId << RF24LOG_DELIMITER;

    // print formatted message
    appendFormattedMessage(message, args);
    #ifndef RF24LOG_NO_EOL
    *stream << std::endl;
    #endif
}

void OStreamLogger::appendTimestamp()
{
    char buffer[21];
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 20, "%F:%H:%M:%S", timeinfo);
    buffer[20] = RF24LOG_DELIMITER;
    *stream << buffer;
}

void OStreamLogger::appendLogLevel(uint8_t logLevel)
{
    uint8_t subLevel = logLevel & 0x07;

    if (logLevel >= RF24LogLevel::ERROR && logLevel <= RF24LogLevel::DEBUG + 7)
    {
        uint8_t logIndex = ((logLevel & 0x38) >> 3) - 1;
        *stream << RF24LogDescLevels[logIndex];

        if(subLevel)
        {
            *stream << "+" << (unsigned int)subLevel << RF24LOG_DELIMITER;
        }
        else
        {
            *stream << "  " << RF24LOG_DELIMITER;
        }

        return;
    }

    *stream << RF24LogDescLevel;
    stream->width(4);
    *stream << std::oct << logLevel << RF24LOG_DELIMITER;
}

void OStreamLogger::appendFormattedMessage(const char *format, va_list *args)
{
    char buffer[80];
    sprintf(buffer, format, args);
    *stream << buffer;
}
#endif // !ARDUINO