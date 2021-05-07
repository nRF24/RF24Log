/**
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
#include <RF24Log/RF24Logging.h>

#ifdef PICO_BUILD
#include "pico/stdlib.h"  // printf(), sleep_ms(), getchar_timeout_us(), to_us_since_boot(), get_absolute_time()
#include "pico/bootrom.h" // reset_usb_boot()
#include <tusb.h>         // tud_cdc_connected()

#include <RF24Log/RF24Loggers/NativePrintLogger.h>

// Create hardware serial port log handler
NativePrintLogger serialLogHandler;

#else
#include <iostream>
#include <RF24Log/RF24Loggers/OStreamLogger.h>

// Create hardware serial port log handler
OStreamLogger serialLogHandler((std::ostream*)&std::cout);
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

    RF24Log_info(vendorID, "RF24Log/examples/gettingStarted");
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

    RF24Log_warn(vendorID, "Warn with error code = 0x%x%x%x%x", 222, 173, 190, 239);
    RF24Log_error(vendorID, "Error message with %s", "RAM string");
    RF24Log_info(vendorID, "Info about rounding a double value %.4D", 3.14159);
    RF24Log_debug(vendorID, "Debug precision of a double value %.4D", 2.71);

    RF24Log_log(RF24LogLevel::INFO + 1, vendorID, "message on sublevel INFO + 1");
    RF24Log_log(RF24LogLevel::WARN + 1, vendorID, "message on sublevel WARN + 1");
    RF24Log_log(RF24LogLevel::INFO + 7, vendorID, "message on sublevel INFO + 7");
    RF24Log_log(RF24LogLevel::ERROR - 1, vendorID, "message on sublevel ERROR - 1");
    RF24Log_log(RF24LogLevel::DEBUG + 8, vendorID, "message on sublevel DEBUG + 8");

    RF24Log_log(077, vendorID, "This\n\tis a multiline\n\t\tmessage that\n\tends with a\nblank line\n\n");
    RF24Log_log(75, vendorID, "%%%%This is level 0x%02x (0b%08b or%4dh)%2c", 75, 75, 75, '!');

    // note negative numbers will look strange in binary, hexadecimal, and octal output if they aren't first casted as unsigned numbers
    // RF24Log_log(-0xAA, vendorID, "0x%02x is 0b%08b is %d, but can also be %o", (uint8_t)(-0xAA), (uint8_t)(-0xAA), -0xAA, -0xAA);

    // print a blank line (no timestamp, level description, or vendorId)
    RF24Log_log(0, DisableVendor, "");

#if !defined(PICO_BUILD)
    // for non-Arduino & not Pico SDK
    // time.sleep(5); // TODO
#endif
}

int main()
{
#ifdef PICO_BUILD
    stdio_init_all(); // init necessary IO for the RP2040
#endif
    setup();
#ifdef PICO_BUILD
    while (1)
    {
#endif
        loop();
#ifdef PICO_BUILD
        sleep_ms(5000);
    }
#endif
    return 0;
}
