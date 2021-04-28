/**
 * Created on: 30 Mar 2021
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *    2021        Witold Markowski (wmarkow)
 *
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

void setup()
{
  // configure serial port baudrate
  Serial.begin(115200);

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
  if (Serial.available()) {
    char input = Serial.read();
    uint8_t count = 0;
    while (Serial.available() && input >= 48 && input < 56) {
      count <<= 3;
      count += input - 48;
      input = Serial.read();
    }
    if (count) {
      Serial.print("Set log level (in octal) to ");
      Serial.print(count, OCT);
      Serial.println(" for Handler2");
      rf24SerialLogHandler2.setLogLevel(count); // set log level only for handler2
    }
  }

  RF24Log_info(vendorID, "This message should be logged %s.", "twice");
  RF24Log_warn(vendorID, "This warn message should be logged %s.", "twice");
  RF24Log_info(vendorID, "This info message should be logged %s.", "twice");
  RF24Log_debug(vendorID, "This debug message should NOT be logged %s.");

  Serial.println("");

  delay(5000);
}
