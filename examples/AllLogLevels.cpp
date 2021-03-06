/**
 * @file allLogLevels.cpp
 * @author Brendan Doherty (2bndy5)
 * @date Created 2021-05-04
 * @copyright Copyright (C) <br>
 *    2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include <string.h>

#ifdef PICO_BUILD
#include "pico/stdlib.h"  // printf(), sleep_ms(), getchar_timeout_us(), to_us_since_boot(), get_absolute_time()
#include "pico/bootrom.h" // reset_usb_boot()
#include <tusb.h>         // tud_cdc_connected()

#include "RF24Logging.h"
#include "RF24Loggers/NativePrintLogger.h"

// Create hardware serial port log handler
NativePrintLogger serialLogHandler;

#else
#include <iostream> // std:: cout, std::cin, std::ostream
#include <stdint.h> // uint8_t
#include <RF24Log/RF24Logging.h>
#include <RF24Log/RF24Loggers/OStreamLogger.h>

// Create hardware serial port log handler
OStreamLogger serialLogHandler((std::ostream*)&std::cout);
#endif

// Define global vendor id
const char vendorID[] = "RF24LogExample";
const char DisableVendor[] = "";

void setup()
{
#if defined(PICO_BUILD)
    // wait here until the CDC ACM (serial port emulation) is connected
    while (!tud_cdc_connected()) {
        sleep_ms(10);
    }
#endif

    // set maximal log level to ALL
    serialLogHandler.setLogLevel(RF24LogLevel::ALL);
    // set serial port handler
    rf24Logging.setHandler(&serialLogHandler);

    RF24Log_info(vendorID, "RF24Log/examples/AllLogLevelsLogger%\n");
}

void loop()
{

    uint8_t lvl = 0;
    do
    {
        RF24Log_log(lvl, vendorID, "A log message from %s on level %3d", "loop()", lvl);
        lvl++;
    } while (lvl);

    // get input from user
    // NOTE: level 0 skips outputting the timestamp and level description
    RF24Log_log(0, DisableVendor, "\nEnter a log level (in octal form) to demonstrate filtering messages\n");
#if defined (PICO_BUILD)
    uint8_t level = 0;
#else
    int level = 0;
#endif

#if defined(PICO_BUILD)
    char input = getchar_timeout_us(5000); // get char from buffer for user input after 5 sec
    if (input != PICO_ERROR_TIMEOUT) {
        while (input >= 48 && input < 56) {
            level <<= 3;
            level += input - 48;
            input = getchar_timeout_us(1000); // get char from buffer for user input after 1 sec
        }
        RF24Log_log(0, DisableVendor, "Setting log level (in octal) to %o", level);
        serialLogHandler.setLogLevel(level);
    }
#else
    RF24Log_log(0, DisableVendor, "Press Ctrl+C to quit.");
    std::cin >> std::oct >> level;
    RF24Log_log(0, DisableVendor, "Setting log level (in octal) to %o", level);
    serialLogHandler.setLogLevel(level);
#endif // platform specific user input
} // end loop()


int main()
{
#ifdef PICO_BUILD
    stdio_init_all(); // init necessary IO for the RP2040
#endif
    setup();
    while (1) {
        loop();
#ifdef PICO_BUILD
        sleep_ms(5000);
#endif
    }
    return 0;
}
