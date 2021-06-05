/**
 * @file PrintfParser.cpp
 * @date Created 4 May 2021
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C) <br>
 *      2020        Witold Markowski (wmarkow)
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include "PrintfParser.h"
#if defined(ARDUINO_ARCH_AVR)
#include <avr/pgmspace.h> // pgm_read_byte()
#endif

#include "FormatSpecifier.h" // FormatSpecifier struct

/****************************************************************************/

#if defined(ARDUINO_ARCH_AVR)
void RF24LogPrintfParser::write(uint8_t logLevel,
                                const __FlashStringHelper *vendorId,
                                const __FlashStringHelper *message,
                                va_list *args)
{
    PGM_P p = reinterpret_cast<PGM_P>(message);
    char c = pgm_read_byte(p++);
    do
    {
        // print header
    #if defined(RF24LOG_NO_EOL)
        appendChar(RF24LOG_DELIMITER);
    #endif
        descTimeLevel(logLevel);
        PGM_P id = reinterpret_cast<PGM_P>(vendorId);
        char v = pgm_read_byte(id++);
        if (v)
        {
            appendStr(vendorId);
            appendChar(RF24LOG_DELIMITER);
        }

        // print formatted message (or at least 1 line at a time)
        while (c
    #if !defined(RF24LOG_NO_EOL)
               && c != '\n'
    #endif
        )
        {
            if (c == '%')
            {
                FormatSpecifier fmt_parser;
                c = pgm_read_byte(p++); // get ready to feed the parser
                while (c && fmt_parser.isFlagged(c))   { c = pgm_read_byte(p++); }
                while (c && fmt_parser.isPaddPrec(c))  { c = pgm_read_byte(p++); }
                while (c && fmt_parser.isFmtOption(c)) { c = pgm_read_byte(p++); }
                if (fmt_parser.specifier)
                {
                    appendFormat(&fmt_parser, args);
                    // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char
                    // if the `while(isFmtOption())` loop above iterated more than once, then
                    // we have to prevent disposing of the left over char here
                    if (fmt_parser.specifier != c)
                    {
                        p--; // let the next iteration handle it
                    }
                }
                else
                {
                    appendChar(c);
                }
            }
    #if defined(RF24LOG_TAB_SIZE)
            else if (c == '\t') { appendChar(' ', RF24LOG_TAB_SIZE); }
    #endif
            else
    #if defined(RF24LOG_NO_EOL)
            if (c != '\n') // dispose char; we control new line feeds ourselves
    #endif
            {
                appendChar(c);
            }
            c = pgm_read_byte(p++);
        }
    #if !defined(RF24LOG_NO_EOL)
        if (c == '\n') { c = pgm_read_byte(p++); } // dispose char; we control new line feeds ourselves
        appendChar('\n');
    #endif
    } while (c);
}
#endif

/****************************************************************************/

void RF24LogPrintfParser::write(uint8_t logLevel,
                                const char *vendorId,
                                const char *message,
                                va_list *args)
{
    char *c = (char *)message;
    do
    {
        // print header
#if defined(RF24LOG_NO_EOL)
        appendChar(RF24LOG_DELIMITER);
#endif
        descTimeLevel(logLevel);
        if (*vendorId)
        {
            appendStr(vendorId);
            appendChar(RF24LOG_DELIMITER);
        }

        // print formatted message (or at least 1 line at a time)
        while (*c
#if !defined(RF24LOG_NO_EOL)
               && *c != '\n'
#endif
        )
        {
            if (*c == '%')
            {
                FormatSpecifier fmt_parser;
                ++c; // get ready to feed the parser
                while (*c && fmt_parser.isFlagged(*c))   { ++c; }
                while (*c && fmt_parser.isPaddPrec(*c))  { ++c; }
                while (*c && fmt_parser.isFmtOption(*c)) { ++c; }
                // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char
                if (fmt_parser.specifier)
                {
                    appendFormat(&fmt_parser, args);
                    // fmt_parser.isFmtOption() stops parsing on a non-fmt-specifying char
                    // if the `while(isFmtOption())` loop above iterated more than once, then
                    // we have to prevent disposing of the left over char here
                    if (fmt_parser.specifier != *c) { --c; } // let the next iteration handle it
                }
                else
                {
                    appendChar(*c);
                }
            }
#if defined(RF24LOG_TAB_SIZE)
            else if (*c == '\t') { appendChar(' ', RF24LOG_TAB_SIZE); }
#endif
            else
#if defined(RF24LOG_NO_EOL)
            if (*c != '\n') // dispose char; we control the new line feeds ourselves
#endif
            {
                appendChar(*c);
            }
            ++c;
        }
#if !defined(RF24LOG_NO_EOL)
        if (*c == '\n') { ++c; } // dispose char; we control the new line feeds ourselves
        appendChar('\n');
#endif
    } while (*c);
}
