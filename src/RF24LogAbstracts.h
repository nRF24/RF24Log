/**
 * @file RF24LogAbstracts.h
 * @brief abstract classes that allow custom handlers and different output stream APIs
 * @date Created 2 Oct 2020
 * @author Witold Markowski (wmarkow)
 * @copyright Copyright (C)
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef SRC_RF24LOGABSTRACTS_H_
#define SRC_RF24LOGABSTRACTS_H_
#if defined (ARDUINO)
#include <WString.h>
#endif
#include <stdint.h>
#include <stdarg.h>

#include "RF24LogHandler.h"
#include "RF24LogLevel.h"

/**
 * @brief how wide (in characters) does it take to display a number
 *
 * @param numb The number to represent
 * @param base The base counting scheme. Defaults to 10 for decimal counting system
 */
uint16_t howWide(int64_t numb, uint8_t base = 10);


/** @brief Some data about a format specifier */
struct SpecifierParsing
{
    /**
     * @brief Construct a new Specifier Flags object
     * @param pad The default char used when padding data
     */
    SpecifierParsing(char pad = ' ') : fill(pad), width(0), precis(-1), isUnsigned(false), specifier(0) {};

    /**
     * @brief is a character a valid specifier flag
     * @param c A character
     * @return true if the @p c param is a valid option; false otherwise
     */
    bool isFlagged(char c);

    /**
     * @brief is a character a valid specifier padding/precision quantity
     * @param c A character
     * @return true if the @p c param is a valid option; false otherwise
     */
    bool isPaddPrec(char c);

    /**
     * @brief is a character a valid/supported specifier format option
     * @param c A character
     * @return true if the @p c param could be followed by another option; false otherwise
     */
    bool isFmtOption(char c);

    /** @brief The default character used as padding. */
    char fill;
    /** @brief The width of the padding */
    uint16_t width;
    /** @brief The number of decimal places. If negative, then default of 2 places is used. */
    int8_t precis;
    /** @brief flag to explicitly represent the number as an unsigned integer */
    bool isUnsigned;
    /** @brief datatype specifier */
    char specifier;
};

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
     * @brief append a padding character a number of times
     * @param data The char to use as padding
     * @param depth The number of padding characters desired sequentially.
     */
    virtual void appendChar(char data, uint16_t depth = 1) = 0;

    /**
     * @brief append a number
     * @param data The numeric data
     * @param base The base counting scheme. Defaults to 10 for decimal counting system
     */
    virtual void appendInt(long data, uint8_t base = 10) = 0;

    /**
     * @brief append a positive number
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


/** @brief An abstract base class for handling log messages. */
class RF24LogAbstractHandler : public RF24LogHandler
{
public:
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

private:

    /**
     * @brief is logging enabled for a certain level?
     * @param logLevel The Log level to test if enabled.
     * @return true if the log messages are enabled for the specified @p logLevel; false otherwise.
     */
    bool isLevelEnabled(uint8_t logLevel);

protected:

    // this is needed so RF24LogAbstracthandler::write() can call RF24LogAbstractStream::append*()
    friend class RF24LogAbstractStream;

    /** The configured log level used to filter which messages are output. */
    uint8_t logLevel;

    RF24LogAbstractHandler();

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

class RF24LogPrintfParser : public RF24LogAbstractHandler, RF24LogAbstractStream
{
protected:
    void write(uint8_t logLevel,
                       const char *vendorId,
                       const char *message,
                       va_list *args);

#if defined (ARDUINO_ARCH_AVR)
    void write(uint8_t logLevel,
                       const __FlashStringHelper *vendorId,
                       const __FlashStringHelper *message,
                       va_list *args);
#endif
};

#endif /* SRC_RF24LOGABSTRACTS_H_ */
