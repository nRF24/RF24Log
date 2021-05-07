/**
 * @file SpecifierFormat.h
 * @brief generic struct that allows customization of a printf-like parser
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

#ifndef SRC_RF24LOGPARTS_SPECIFIERFORMAT_H_
#define SRC_RF24LOGPARTS_SPECIFIERFORMAT_H_

#include <stdint.h>

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

#endif /* SRC_RF24LOGPARTS_SPECIFIERFORMAT_H_ */