/**
 * @file AllLogLevelsLogger.ino
 *
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

// Define global vendor id (it is stored in flash memory)
const char vendorID[] PROGMEM = "RF24LogLevelExample";


// Need to remember that backslash must be escaped in the string text
// Banner generated with https://devops.datenkollektiv.de/banner.txt/index.html
const PROGMEM char banner[5][46]  = { "   ___    ____   ___   ____   __             ",
                                    "  / _ \\  / __/  |_  | / / /  / /  ___   ___ _",
                                    " / , _/ / _/   / __/ /_  _/ / /__/ _ \\ / _ `/",
                                    "/_/|_| /_/    /____/  /_/  /____/\\___/ \\_, / ",
                                    "                                      /___/  "};

void setup()
{
   // configure serial port baudrate
   Serial.begin(115200);

   // set maximal log level to ALL
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::ALL);
   // set serial port appender
   rf24Logger.setHandler(&rf24SerialLogHandler);

   // display banner
   for (uint8_t i = 0; i < 5; ++i)
   {
      rf24Logger.info((const __FlashStringHelper*) vendorID, (const __FlashStringHelper*) banner[i]);
   }
}

void loop()
{
   for(uint16_t logLevel = 0 ; logLevel <= 255 ; logLevel ++)
   {
      rf24Logger.log((uint8_t)logLevel, (const __FlashStringHelper*)vendorID, F("This is a log message with level %d"), logLevel);
   }

   Serial.println("");
   delay(5000);
}


