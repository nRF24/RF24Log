/**
 * @file Stream.h
 * @brief abstract class that allows using different output stream APIs
 * @date Created 4 May 2021
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C)
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24LOGPARTS_STREAM_H_
#define SRC_RF24LOGPARTS_STREAM_H_

#if defined (ARDUINO)
#include <WString.h> // __FlashStringHelper
#endif
#include <stdint.h>
#include "SpecifierFormat.h" // SpecifierParsing struct
#include "common.h" // numbCharsToPrint()

/** @brief A `protected` collection of methods that output formatted data to a stream. */
class RF24LogAbstractStream
{

protected:

    /** @brief output a timestamp */
    virtual void appendTimestamp() = 0;

    /**
     * @brief output a description of the log level
     * @param logLevel The level to describe.
     */
    void appendLogLevel(uint8_t logLevel);

    /**
     * @brief Automate the output of the header' timestamp and level description
     * @param logLevel The Log level to describe.
     */
    void descTimeLevel(uint8_t logLevel);

    /**
     * @brief output a data according to the format specifier
     * @param fmt_parser The object of prefixed specifier options/flags
     * @param args The sequence of args
     */
    void appendFormat(SpecifierParsing* fmt_parser, va_list *args);

    /**
     * @brief append a character a number of times
     * @param data The char to use
     * @param depth The number of times that the @p data is sequentially output.
     */
    virtual void appendChar(char data, uint16_t depth = 1) = 0;

    /**
     * @brief append a signed (+/-) number
     * @param data The numeric data
     * @param base The base counting scheme. Defaults to 10 for decimal counting system
     */
    virtual void appendInt(long data, uint8_t base = 10) = 0;

    /**
     * @brief append an `unsigned' (only +) number
     * @param data The numeric data
     * @param base The base counting scheme. Defaults to 10 for decimal counting system
     */
    virtual void appendUInt(unsigned long data, uint8_t base = 10) = 0;

    /**
     * @brief append a floating point number
     * @param data The numeric data
     * @param precision The number of decimals places to output
     */
    virtual void appendDouble(double data, uint8_t precision = 2) = 0;

    /**
     * @brief append a c-string
     * @param data The c-string data
     */
    virtual void appendStr(const char* data) = 0;
#ifdef ARDUINO_ARCH_AVR
    virtual void appendStr(const __FlashStringHelper* data) = 0;
#endif
};

#endif /* SRC_RF24LOGPARTS_STREAM_H_ */