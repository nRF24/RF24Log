/**
 * Created on: 2 Oct 2020
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *    2020        Witold Markowski (wmarkow)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include <Arduino.h>
#include <string.h>

#include <RF24Logger.h>
#include <RF24Loggers/ArduinoPrintLogger.h>

// Create hardware serial port log handler
ArduinoPrintLogger rf24SerialLogHandler(&Serial);

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";

void setup()
{
  // configure serial port baudrate
  Serial.begin(115200);

  // set maximal log level to ALL
  rf24SerialLogHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port handler
  rf24Logger.setHandler(&rf24SerialLogHandler);

  RF24LOGGER_info(vendorID, "RF24Log/examples/BasicSerialLogger");
}

void loop()
{
  if (Serial.available()) {
    char input = Serial.parseInt();
    Serial.print("Set log level (in octal) to ");
    Serial.println(input, OCT);
    rf24SerialLogHandler.setLogLevel(input);
  }

  RF24LOGGER_error(vendorID, "Error message");
  RF24LOGGER_warn(vendorID, "Warning message");
  RF24LOGGER_info(vendorID, "Info message");
  RF24LOGGER_debug(vendorID, "Debug message");

  RF24LOGGER_error(vendorID, "Error message with %s", "RAM string 1");
  RF24LOGGER_warn(vendorID, "Warning message with %s", "RAM string 2");

  RF24LOGGER_info(vendorID, " info log with double value %D", 3.14);
  RF24LOGGER_debug(vendorID, " warn log with double value %D", 2.71);

  RF24LOGGER_log(RF24LogLevel::INFO + 1, vendorID, "INFO + 1 message");
  RF24LOGGER_log(RF24LogLevel::WARN + 1, vendorID, "WARN + 1 message");

  Serial.println("");

  delay(5000);
}
