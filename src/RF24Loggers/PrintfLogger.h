/**
 * @file PrintfLogger.h
 * @brief handler for printf basedfunction calls
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

#ifndef SRC_RF24LOGGERS_PRINTFLOGGER_H_
#define SRC_RF24LOGGERS_PRINTFLOGGER_H_

#include <RF24LogAbstracts.h>

/** @brief Class to manage logging messages to a printf function pointer. */
class PrintfLogger : public RF24LogAbstractHandler, RF24LogAbstractStream
{
public:
    /**
     * @brief Construct a new PrintfLogger object
     * @param _stream The `printf()`-like function that ships with cstdio.
     */
    PrintfLogger(int (*_stream)(const char *, ...));

private:

    /** @brief The internal reference to the configured output stream */
    int (*stream)(const char *, ...);

protected:

    // declare the rest to raise from pure virtual
    /************************************************/

    void appendTimestamp();
    void appendChar(char data, int16_t depth = 1);
    void appendInt(long data, uint8_t base = 10);
    void appendUInt(unsigned long data, uint8_t base = 10);
    void appendDouble(double data, uint8_t precision = 2);
    void appendStr(const char* data);
    void write(uint8_t logLevel,
               const char *vendorId,
               const char *message,
               va_list *args);
};

#endif // SRC_RF24LOGGERS_PRINTFLOGGER_H_
