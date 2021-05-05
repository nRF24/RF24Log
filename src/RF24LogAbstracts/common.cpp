
#include <RF24LogAbstracts/common.h>

/* *************************** Abstract global function defs **************************** */

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
