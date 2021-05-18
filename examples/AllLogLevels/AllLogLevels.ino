/**
 * Created on: 31 Mar 2021
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

// Create hardware serial port log handler
ArduinoPrintLogger serialLogHandler(&Serial);

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";
const char PROGMEM DisableVendor[] = ""; // vendorId needs to be a flash string on AVR architecture

void setup()
{
  // configure serial port baudrate
  Serial.begin(115200);
  while (!Serial) {/* some boards need this */}

  // set maximal log level to ALL
  serialLogHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port handler
  rf24Logging.setHandler(&serialLogHandler);

  RF24Log_info(vendorID, "RF24Log/examples/AllLogLevelsLogger%\n");
}

void loop()
{
  uint8_t lvl = 0;
  do {
    RF24Log_log(lvl, vendorID, "A log message from %s on level %3d", "loop()", lvl);
    lvl++;
  } while (lvl);

  // NOTE: level 0 skips outputting the timestamp and level description
  RF24Log_log(0, DisableVendor, "\nEnter a log level (in octal form) to demonstrate filtering messages\n");

  delay(5000);

  uint8_t level = 0;
  if (Serial.available()) {
    char input = Serial.read();
    while (Serial.available() && input >= 48 && input < 56) {
      level <<= 3;
      level += input - 48;
      input = Serial.read();
    }
    RF24Log_log(0, DisableVendor, "Setting log level (in octal) to %o", level);
    serialLogHandler.setLogLevel(level);
  }
}
