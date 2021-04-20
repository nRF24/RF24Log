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
#include <handlers/RF24StreamLogHandler.h>

// Create hardware serial port log appender
RF24StreamLogHandler rf24SerialLogHandler(&Serial);

// Define global vendor id (it is stored in flash memory)
const char PROGMEM vendorIDFlash[] = "RF24LogExample";
const char vendorIDRam[] = "RF24LogExample";


// Define some test messages stored in EEPROM
const char PROGMEM globalProgmemText[] = "global PROGMEM message";
const char PROGMEM globalProgmemMessageWithRamString[] = "PROGMEM message with %s";

void setup()
{
  // configure serial port baudrate
  Serial.begin(115200);

  // set maximal log level to ALL
  rf24SerialLogHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port appender
  rf24Logger.setHandler(&rf24SerialLogHandler);

  rf24Logger.info((const __FlashStringHelper*) vendorIDFlash, F("RF24Log/examples/BasicSerialLogger"));

  RF24LOGGER_info(vendorIDFlash, "This comes from macro.");
}

void logSimpleRamMessage();
void logSimpleGlobalProgmemMessage();
void logSimpleFMacroMessage();
void logRamMessageWithRamStringArgument();
void logRamMessageWithProgmemStringArgument();
void logRamMessageWithFMacroStringArgument();
void logProgmemMessageWithRamStringArgument();
void logMessageWithAdditionalTagAtTheBeginning();
void logMessageWithUnknownFormat();
void logFloatNumber();
void logCustomLogLevels();

void loop()
{
  logSimpleRamMessage();
  logSimpleGlobalProgmemMessage();
  logSimpleFMacroMessage();
  logRamMessageWithRamStringArgument();
  logRamMessageWithProgmemStringArgument();
  logRamMessageWithFMacroStringArgument();
  logProgmemMessageWithRamStringArgument();
  logMessageWithAdditionalTagAtTheBeginning();
  logMessageWithUnknownFormat();
  logFloatNumber();
  logCustomLogLevels();

  Serial.println();
  Serial.println("--------------------------------------------------");
  Serial.println();

  delay(5000);
}

void logSimpleRamMessage()
{
  rf24Logger.error(vendorIDRam, "Error message defined in RAM");
  rf24Logger.warn(vendorIDRam, "Warning message defined in RAM");
  rf24Logger.info(vendorIDRam, "Info message defined in RAM");
  rf24Logger.debug(vendorIDRam, "Debug message defined in RAM");

  Serial.println();
}

void logSimpleGlobalProgmemMessage()
{
  rf24Logger.error((const __FlashStringHelper*) vendorIDFlash,
                   (const __FlashStringHelper*) globalProgmemText);
  rf24Logger.warn((const __FlashStringHelper*) vendorIDFlash,
                  (const __FlashStringHelper*) globalProgmemText);
  rf24Logger.info((const __FlashStringHelper*) vendorIDFlash,
                  (const __FlashStringHelper*) globalProgmemText);
  rf24Logger.debug((const __FlashStringHelper*) vendorIDFlash,
                   (const __FlashStringHelper*) globalProgmemText);

  Serial.println();
}

void logSimpleFMacroMessage()
{
  rf24Logger.error((const __FlashStringHelper*) vendorIDFlash,
                   F("text from F macro"));
  rf24Logger.warn((const __FlashStringHelper*) vendorIDFlash,
                  F("text from F macro"));
  rf24Logger.info((const __FlashStringHelper*) vendorIDFlash,
                  F("text from F macro"));
  rf24Logger.debug((const __FlashStringHelper*) vendorIDFlash,
                   F("text from F macro"));

  Serial.println();
}

void logRamMessageWithRamStringArgument()
{
  rf24Logger.error(vendorIDRam, "RAM message with %s", "RAM string 1");
  rf24Logger.warn(vendorIDRam, "RAM message with %s", "RAM string 2");
  rf24Logger.info(vendorIDRam, "RAM message with %s", "RAM string 3");
  rf24Logger.debug(vendorIDRam, "RAM message with %s", "RAM string 4");

  Serial.println();
}

void logRamMessageWithProgmemStringArgument()
{
  rf24Logger.error(vendorIDRam,
                   "RAM message with %S", (const __FlashStringHelper*) globalProgmemText);
  rf24Logger.warn(vendorIDRam, "RAM message with %S",
                  (const __FlashStringHelper*) globalProgmemText);
  rf24Logger.info(vendorIDRam, "RAM message with %S",
                  (const __FlashStringHelper*) globalProgmemText);
  rf24Logger.debug(vendorIDRam,
                   "RAM message with %S", (const __FlashStringHelper*) globalProgmemText);

  Serial.println();
}

void logRamMessageWithFMacroStringArgument()
{
  rf24Logger.error(vendorIDRam, "RAM message with %S", F("F macro string 1"));
  rf24Logger.warn(vendorIDRam, "RAM message with %S", F("F macro string 2"));
  rf24Logger.info(vendorIDRam, "RAM message with %S", F("F macro string 3"));
  rf24Logger.debug(vendorIDRam, "RAM message with %S", F("F macro string 4"));

  Serial.println();
}

void logProgmemMessageWithRamStringArgument()
{
  rf24Logger.error((const __FlashStringHelper*) vendorIDFlash,
                   (const __FlashStringHelper*) globalProgmemMessageWithRamString,
                   "RAM string 1");
  rf24Logger.warn((const __FlashStringHelper*) vendorIDFlash,
                  (const __FlashStringHelper*) globalProgmemMessageWithRamString,
                  "RAM string 2");
  rf24Logger.info((const __FlashStringHelper*) vendorIDFlash,
                  (const __FlashStringHelper*) globalProgmemMessageWithRamString,
                  "RAM string 3");
  rf24Logger.debug((const __FlashStringHelper*) vendorIDFlash,
                   (const __FlashStringHelper*) globalProgmemMessageWithRamString,
                   "RAM string 4");

  Serial.println();
}

void logMessageWithAdditionalTagAtTheBeginning()
{
  rf24Logger.info(vendorIDRam,
                  "%S info log with additional tag at the beginning", F("RF24Log.cpp"));

  Serial.println();
}

void logMessageWithUnknownFormat()
{
  rf24Logger.info((const __FlashStringHelper*) vendorIDFlash,
                  F("info log with unknown format   : %p"), F("flash text"));

  Serial.println();
}

void logFloatNumber()
{
  rf24Logger.info(vendorIDRam, " info log with double value %D", 3.14);

  rf24Logger.warn(vendorIDRam, " warn log with double value %D", 3.14);

  rf24Logger.error(vendorIDRam, "error log with double value %D", 3.14);

  rf24Logger.debug(vendorIDRam, "debug log with double value %F", 2.71);

  Serial.println();
}

void logCustomLogLevels()
{
  rf24Logger.log(RF24LogLevel::INFO + 1, vendorIDRam,
                 "INFO + 1 message defined in RAM");

  rf24Logger.log(RF24LogLevel::WARN + 1, (const __FlashStringHelper*) vendorIDFlash,
                 F("WARN + 1 message defined in FLASH"));

  Serial.println();
}
