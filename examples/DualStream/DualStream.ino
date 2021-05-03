/**
 * Created on: 30 Mar 2021
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *    2020        Witold Markowski (wmarkow)
 *    2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include <Arduino.h>
#include <string.h>

#include <RF24Logging.h>
#include <RF24Loggers/ArduinoPrintLogger.h>
#include <handler_ext/RF24DualLogHandler.h>

// Create first hardware serial port log handler
ArduinoPrintLogger rf24SerialLogHandler1(&Serial);

// Create second hardware serial port log handler
ArduinoPrintLogger rf24SerialLogHandler2(&Serial);

RF24DualLogHandler rf24DualLogHandler(&rf24SerialLogHandler1, &rf24SerialLogHandler2);

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";
const char PROGMEM DisableVendor[] = ""; // vendorId needs to be a flash string on AVR architecture

void setup()
{
  // configure serial port baudrate
  Serial.begin(115200);
  while (!Serial) {/* some boards need this */ ; }

  // set maximal log level to ALL
  rf24DualLogHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port handler
  rf24Logging.setHandler(&rf24DualLogHandler);

  RF24Log_info(vendorID, "RF24Log/examples/DualLogger");
}

void loop()
{
  // set log level for both Handlers
  rf24DualLogHandler.setLogLevel(RF24LogLevel::ALL);

  uint8_t level = 0;
  char input;

#ifdef ARDUINO
  if (Serial.available()) {
    input = Serial.read();
    while (Serial.available() && input >= 48 && input < 56) {
      level <<= 3;
      level += input - 48;
      input = Serial.read();
    }
  }
#elif defined (PICO_BUILD)
  input = getchar_timeout_us(5000); // get char from buffer for user input after 5 sec
  while (input != PICO_ERROR_TIMEOUT && input >= 48 && input < 56) {
    level <<= 3;
    level += input - 48;
    input = getchar_timeout_us(1000); // get char from buffer for user input after 1 sec
  }
#endif // platform specific user input

  if (level) {
    RF24Log_log(0, DisableVendor, "Set log level (in octal) to %o\n", level);
    rf24SerialLogHandler2.setLogLevel(level); // set log level only for handler2
  }

  RF24Log_info(vendorID, "This message should be logged %s.", "twice");
  RF24Log_warn(vendorID, "This warn message should be logged %s.", "twice");
  RF24Log_info(vendorID, "This info message should be logged %s.", "twice");
  RF24Log_debug(vendorID, "This debug message should NOT be logged %s.");

  // print a blank line (no timestamp, level description, or vendorId)
  RF24Log_log(0, DisableVendor, "");

#ifdef ARDUINO

  delay(5000);
#elif !defined(PICO_BUILD)
  // for non-Arduino & not Pico SDK
  // time.sleep(1); // TODO
#endif
}
