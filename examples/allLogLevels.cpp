/**
 * @file allLogLevels.cpp
 * @author Brendan Doherty (2bndy5)
 * @date Created 2021-05-04
 * @copyright Copyright (C)
 *    2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include <string.h>
#include <RF24Logging.h>

#if defined (PICO_BUILD)
#include "pico/stdlib.h"  // printf(), sleep_ms(), getchar_timeout_us(), to_us_since_boot(), get_absolute_time()
#include "pico/bootrom.h" // reset_usb_boot()
#include <tusb.h>         // tud_cdc_connected()
#include <RF24Loggers/PrintfLogger.h>

// Create hardware serial port log handler
PrintfLogger serialLogHandler(&printf);

#else
#include <iostream>
#include <RF24Loggers/OStreamLogger.h>

// Create hardware serial port log handler
OStreamLogger serialLogHandler((std::ostream *)&std::cout);
#endif

// Define global vendor id (it is stored in FLASH memory)
const char vendorID[] = "RF24LogExample";
const char DisableVendor[] = ""; // vendorId needs to be a flash string on AVR architecture

void setup()
{
#if defined(PICO_BUILD)
    // wait here until the CDC ACM (serial port emulation) is connected
    while (!tud_cdc_connected())
    {
        sleep_ms(10);
    }
#endif

    // set maximal log level to ALL
    serialLogHandler.setLogLevel(RF24LogLevel::ALL);
    // set serial port handler
    rf24Logging.setHandler(&serialLogHandler);

    RF24Log_info(vendorID, "RF24Log/examples/AllLogLevelsLogger");
}

void loop()
{
    uint8_t level = 0;
    char input;

#if defined(PICO_BUILD)
    input = getchar_timeout_us(5000); // get char from buffer for user input after 5 sec
    while (input != PICO_ERROR_TIMEOUT && input >= 48 && input < 56)
    {
        level <<= 3;
        level += input - 48;
        input = getchar_timeout_us(1000); // get char from buffer for user input after 1 sec
    }
#endif // platform specific user input

    if (level)
    {
        RF24Log_log(0, DisableVendor, "Set log level (in octal) to %o\n", level);
        serialLogHandler.setLogLevel(level);
    }

    level = 0;
    do
    {
        RF24Log_log(level, vendorID, "A log message from %s on level %3d", "loop()", level);
        level++;
    } while (level);

    // print a blank line (no timestamp, level description, or vendorId)
    RF24Log_log(0, DisableVendor, "");

#if !defined(PICO_BUILD)
    // for non-Arduino & not Pico SDK
    // time.sleep(1); // TODO
#endif
}

int main()
{
#if defined (PICO_BUILD)
    stdio_init_all(); // init necessary IO for the RP2040
#endif
    setup();
    while (1)
    {
        loop();
    }
    return 0;
}
