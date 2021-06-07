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

#include <string.h>
#include <Arduino.h>
#include <RF24Logging.h>
#include <RF24Loggers/ArduinoPrintLogger.h>
#include <handler_ext/RF24LogDualHandler.h>

// Create first hardware serial port log handler
ArduinoPrintLogger serialLogHandler1(&Serial);

// Create second hardware serial port log handler
ArduinoPrintLogger serialLogHandler2(&Serial);

RF24LogDualHandler dualHandler(&serialLogHandler1, &serialLogHandler2);

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";
const char PROGMEM DisableVendor[] = ""; // vendorId needs to be a flash string on AVR architecture

// we will use this variable to control the filtering of log messages for the second handler
uint8_t level = RF24LogLevel::ALL;

void setup()
{
  // configure serial port baudrate
  Serial.begin(115200);
  while (!Serial) {/* some boards need this */}

  // set maximal log level to ALL (for both handlers)
  dualHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port handler (to only 1 handler)
  rf24Logging.setHandler(&serialLogHandler1);

  RF24Log_info(vendorID, "RF24Log/examples/DualLogger%\n");
}

void loop()
{
  // set serial port handler (to both handlers)
  rf24Logging.setHandler(&dualHandler);
  bool is_2nd_handler_enabled_for_info;
  is_2nd_handler_enabled_for_info = level < RF24LogLevel::INFO;
  RF24Log_info(vendorID,
               "This info message should be logged %s because serialLogHandler2 verbosity is %o.",
               (is_2nd_handler_enabled_for_info ? "once" : "twice"),
               level);

  // set serial port handler (to only 1 handler)
  rf24Logging.setHandler(&serialLogHandler1);
  RF24Log_debug(vendorID, "This debug message should be logged once.");

  // NOTE: level 0 skips outputting the timestamp and level description
  RF24Log_log(0, DisableVendor, "\nEnter a log level (in octal form) to demonstrate filtering messages (for the second handler)\n");

  delay(5000);

  if (Serial.available()) {
    level = 0; // reset value for the following arithmatic
    char input = Serial.read();
    while (Serial.available() && input >= 48 && input < 56) {
      level <<= 3;
      level += input - 48;
      input = Serial.read();
    }
    RF24Log_log(0, DisableVendor, "Setting log level (in octal) to %o (for the second handler)", level);
    serialLogHandler2.setLogLevel(level);
  }
}
