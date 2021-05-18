/**
 * @file RF24LogParts/common.cpp
 * @date Created 2 Oct 2020
 * @author Brendan Doherty (2bndy5)
 * @copyright Copyright (C) <br>
 *      2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include "Common.h"

/****************************************************************************/

uint16_t numbCharsToPrint(int64_t numb, uint8_t base)
{
    int64_t mask = (numb < 0 ? numb * -1 : numb);
    uint16_t i = 0;
    while (mask)
    {
        if      (base == 2)  { mask >>= 1; }
        else if (base == 8)  { mask >>= 3; }
        else if (base == 16) { mask >>= 4; }
        else /*base == 10*/  { mask /= 10; }
        i++;
    }
    if (numb <= 0)
    {
        i += 1 + (bool)numb; // compensate for the negative sign (and zero char)
    }
    return i;
}
