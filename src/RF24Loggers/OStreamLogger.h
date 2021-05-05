/**
 * @file OStreamLogger.h
 * @brief handler for ostream based objects
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
#ifndef SRC_RF24LOGGERS_OSTREAMLOGGER_H_
#define SRC_RF24LOGGERS_OSTREAMLOGGER_H_

#include <ostream>
#include <RF24LogAbstracts/Parsing.h>

/** @brief Class to manage logging messages to a `ostream` based object. */
class OStreamLogger : public RF24LogPrintfParser
{
public:
    /**
     * @brief Construct a new OStreamLogger object
     * @param stream The output stream that inherits from ostream class.
     */
    OStreamLogger(std::ostream* stream);

private:

    /** The internal reference to the configured output stream */
    std::ostream* _stream;

protected:

    // declare the rest to raise from pure virtual
    /************************************************/

    void appendTimestamp();
    void appendChar(char data, uint16_t depth = 1);
    void appendInt(long data, uint8_t base = 10);
    void appendUInt(unsigned long data, uint8_t base = 10);
    void appendDouble(double data, uint8_t precision = 2);
    void appendStr(const char* data);
};

#ifndef PROGMEM
#define PROGMEM
#endif

#endif // SRC_RF24LOGGERS_OSTREAMLOGGER_H_
#endif // !defined(ARDUINO)