/**
 * @file LogLevelsLogger.ino
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
const char vendorID[] PROGMEM = "RF24LogExample";


void logSimpleRamMessage();

void setup()
{
   // configure serial port baudrate
   Serial.begin(115200);

   // set maximal log level to ALL
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::ALL);
   // set serial port appender
   rf24Logger.setHandler(&rf24SerialLogHandler);

   rf24Logger.info((const __FlashStringHelper*) vendorID, F("RF24Log/examples/LogLevelsLogger"));
}

void loop()
{
   Serial.println("Set log level to OFF");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::OFF);
   logSimpleRamMessage();

   Serial.println("Set log level to ERROR");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::ERROR);
   logSimpleRamMessage();

   Serial.println("Set log level to ERROR + 1");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::ERROR + 1);
   logSimpleRamMessage();

   Serial.println("Set log level to ERROR + 7");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::ERROR + 7);
   logSimpleRamMessage();

   Serial.println("Set log level to WARN");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::WARN);
   logSimpleRamMessage();

   Serial.println("Set log level to INFO");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::INFO);
   logSimpleRamMessage();

   Serial.println("Set log level to DEBUG");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::DEBUG);
   logSimpleRamMessage();

   Serial.println("Set log level to DEBUG + 1");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::DEBUG + 1);
   logSimpleRamMessage();

   Serial.println("Set log level to DEBUG + 7");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::DEBUG + 7);
   logSimpleRamMessage();

   Serial.println("Set log level to ALL");
   rf24SerialLogHandler.setLogLevel(RF24LogLevel::ALL);
   logSimpleRamMessage();

   Serial.println("");
   delay(5000);
}

void logSimpleRamMessage()
{
   rf24Logger.error((const __FlashStringHelper*) vendorID,
         "Error message");
   rf24Logger.log(RF24LogLevel::ERROR + 1, (const __FlashStringHelper*) vendorID,
            "Error message sub-level 1");
   rf24Logger.log(RF24LogLevel::ERROR + 7, (const __FlashStringHelper*) vendorID,
               "Error message sub-level 7");

   rf24Logger.warn((const __FlashStringHelper*) vendorID,
         "Warning message");
   rf24Logger.log(RF24LogLevel::WARN + 1, (const __FlashStringHelper*) vendorID,
               "Warning message sub-level 1");
   rf24Logger.log(RF24LogLevel::WARN + 7, (const __FlashStringHelper*) vendorID,
                  "Warning message sub-level 7");

   rf24Logger.info((const __FlashStringHelper*) vendorID,
         "Info message");
   rf24Logger.log(RF24LogLevel::INFO + 1, (const __FlashStringHelper*) vendorID,
               "Info message sub-level 1");
   rf24Logger.log(RF24LogLevel::INFO + 7, (const __FlashStringHelper*) vendorID,
                  "Info message sub-level 7");

   rf24Logger.debug((const __FlashStringHelper*) vendorID,
         "Debug message");
   rf24Logger.log(RF24LogLevel::DEBUG + 1, (const __FlashStringHelper*) vendorID,
                  "Debug message sub-level 1");
   rf24Logger.log(RF24LogLevel::DEBUG + 7, (const __FlashStringHelper*) vendorID,
                     "Debug message sub-level 7");

   rf24Logger.trace((const __FlashStringHelper*) vendorID,
         "Trace message");
   rf24Logger.log(RF24LogLevel::TRACE + 1, (const __FlashStringHelper*) vendorID,
                     "Trace message sub-level 1");
   rf24Logger.log(RF24LogLevel::TRACE + 7, (const __FlashStringHelper*) vendorID,
                        "Trace message sub-level 7");

   Serial.println();
}
