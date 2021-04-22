/**
 * Created on: 31 Mar 2021
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

#include <RF24Logger.h>
#include <handlers/RF24StreamLogHandler.h>

// Create hardware serial port log appender
RF24StreamLogHandler rf24SerialLogHandler(&Serial);

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";

void setup()
{
  // configure serial port baudrate
  Serial.begin(115200);

  // set maximal log level to ALL
  rf24SerialLogHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port appender
  rf24Logger.setHandler(&rf24SerialLogHandler);

  RF24LOGGER_info(vendorID, "RF24Log/examples/AllLogLevelsLogger");
}

void loop()
{
  for (uint16_t logLevel = 0 ; logLevel <= 255 ; logLevel ++)
  {
    RF24LOGGER_log((uint8_t)logLevel, vendorID, "This is a log message with level %d", logLevel);
  }

  Serial.println("");
  delay(5000);
}
