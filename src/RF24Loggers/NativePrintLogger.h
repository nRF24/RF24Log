/**
 * @file NativePrintLogger.h
 * @brief handler for printf-based function calls
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

#ifndef SRC_RF24LOGGERS_NATIVEPRINTLOGGER_H_
#define SRC_RF24LOGGERS_NATIVEPRINTLOGGER_H_

#include "../RF24LogParts/Parsing.h"
#include "../RF24LogParts/LevelDescriptions.h"

/** @brief macro pointing to the natively available `printf()` */
#ifndef printf_P
#define printf_P printf
#endif

/** @brief Class to manage logging messages to a printf function pointer. */
class NativePrintLogger : public RF24LogPrintfParser
{
public:
    /** @brief Construct a new NativePrintLogger object using stdout */
    NativePrintLogger();

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

#endif // SRC_RF24LOGGERS_NATIVEPRINTLOGGER_H_
