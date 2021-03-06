/**
 * @file FormatSpecifier.cpp
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

#include "FormatSpecifier.h"

/****************************************************************************/

bool FormatSpecifier::isFlagged(char c)
{
    if (c == '0')
    {
        fill = '0';
    }
    return (bool)(c == '-' || c == '+' || c == ' ' || c == '0');
}

/****************************************************************************/

bool FormatSpecifier::isPaddPrec(char c)
{
    if (c == '.' || (c > 47 && c < 58))
    {
        if (c == '.')
        {
            precis = 0; // 0.0 value will not be output
        }
        else
        {
            if (precis >=0)
            {
                precis = (precis * 10) + (c - 48);
            }
            else
            {
                width = (width * 10) + (c - 48);
            }
        }
        return true;
    }
    return false;

}

/****************************************************************************/

bool FormatSpecifier::isFmtOption(char c)
{

    if (c == 's' ||
    #ifdef ARDUINO_ARCH_AVR
            c == 'S' ||
    #endif
            c == 'c' ||
            c == 'D' ||
            c == 'f' ||
            c == 'F' ||
            c == 'x' ||
            c == 'X' ||
            c == 'o' ||
            c == 'u' ||
            c == 'd' ||
            c == 'i' ||
            c == 'b')
    {
        if (c == 'u' || c == 'x' || c == 'X' || c == 'o' || c == 'b')
        {
            length |= 0x80;
        }
        specifier = c;
        return false; // no second option supported
    }
    else if (c == 'l' || c == 'h')
    {
        if (length & 0x30) // second encountered length modifier
        {
            length = (length & 0x80) | (c == 'l' ? (length & 0x30) << 1 : (length & 0x30) >> 1);

        }
        else // first encountered length modifier
        {
            length = (length & 0x80) | (c == 'l' ? 32 : 16);
        }
        return true; // can also support a second option (like 'u')
    }
    return false;
}
