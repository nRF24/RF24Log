/**
 * @file RF24LogAbstracts.cpp
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

#include <RF24LogAbstracts.h>

RF24LogAbstractHandler::RF24LogAbstractHandler()
{
    this->logLevel = RF24LogLevel::INFO;
}

void RF24LogAbstractHandler::log(uint8_t logLevel,
                                 const char *vendorId,
                                 const char *message,
                                 va_list *args)
{
    if (logLevel > this->logLevel)
    {
        return;
    }

    write(logLevel, vendorId, message, args);
}

void RF24LogAbstractHandler::setLogLevel(uint8_t logLevel)
{
    this->logLevel = logLevel;
}

#if defined (ARDUINO_ARCH_AVR)
void RF24LogAbstractHandler::log(uint8_t logLevel,
                                 const __FlashStringHelper *vendorId,
                                 const __FlashStringHelper *message,
                                 va_list *args)
{
    if (logLevel > this->logLevel)
    {
        return;
    }

    write(logLevel, vendorId, message, args);
}
#endif

int16_t RF24LogAbstractStream::howWide(int numb, uint8_t base)
{
    int mask = numb;
    int16_t i = 0;
    while (mask)
    {
        if (base == 2)
        {
            mask >>= 1;
        }
        else if (base == 8)
        {
            mask >>= 3;
        }
        else if (base == 16)
        {
            mask >>= 4;
        }
        else // assume base is default value of 10
        {
            mask /= 10;
        }
        i++;
    }
    if (numb < 0)
    {
        i++; // compensate for the negative sign
    }
    return i;
}

bool SpecifierFlags::isFlagged(char c)
{
    if (c == '0')
    {
        fill = '0';
    }
    return (bool)(c == '-' || c == '+' || c == ' ' || c == '0');
}

bool SpecifierFlags::isPaddPrec(char c)
{
    if (c == '.' || (c > 47 && c < 58))
    {
        if (c == '.')
        {
            precis = 0;
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
