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

#include <RF24Logger.h>
#include <handlers/RF24StreamLogHandler.h>
#include <handlers/RF24DualLogHandler.h>

// Create first hardware serial port log appender
RF24StreamLogHandler rf24SerialLogHandler1(&Serial);

// Create second hardware serial port log appender
RF24StreamLogHandler rf24SerialLogHandler2(&Serial);

RF24DualLogHandler rf24DualLogHandler(&rf24SerialLogHandler1, &rf24SerialLogHandler2);

// Define global vendor id (it is stored in flash memory)
const char PROGMEM vendorID[] = "RF24LogExample";


// Define some test messages stored in EEPROM
const char PROGMEM globalProgmemText[] = "global PROGMEM message";
const char PROGMEM globalProgmemMessageWithRamString[] = "PROGMEM message with %s";

void setup()
{
  // configure serial port baudrate
  Serial.begin(115200);

  // set maximal log level to ALL
  rf24DualLogHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port appender
  rf24Logger.setHandler(&rf24DualLogHandler);

  rf24Logger.info((const __FlashStringHelper*) vendorID, F("RF24Log/examples/DualLogger"));
}

void loop()
{
  rf24DualLogHandler.setLogLevel(RF24LogLevel::ALL);
  rf24Logger.info((const __FlashStringHelper*) vendorID, F("This message should be logged %s."), "twice");

  rf24DualLogHandler.setLogLevel(RF24LogLevel::INFO);
  rf24Logger.warn((const __FlashStringHelper*) vendorID, F("This warn message should be logged %s."), "twice");
  rf24Logger.info((const __FlashStringHelper*) vendorID, F("This info message should be logged %s."), "twice");
  rf24Logger.debug((const __FlashStringHelper*) vendorID, F("This debug message should NOT be logged %s."));

  delay(5000);
}
