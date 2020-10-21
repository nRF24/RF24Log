#include <Arduino.h>
#include <string.h>

#include <RF24Logger.h>
#include <RF24StreamLogAppender.h>

// Define global vendor id (it is stored in flash memory)
const char vendorID[] PROGMEM = "RF24LogExample";

// DO NOT create hardware serial port log appender
// RF24StreamLogAppender rf24SerialLogAppender(&Serial);

// Need to remember that backslash must be escaped in the string text
// Banner generated with https://devops.datenkollektiv.de/banner.txt/index.html
const char banner0[] PROGMEM = " ___   ___   ___   _ _    _                 ";
const char banner1[] PROGMEM = "| _ \\ | __| |_  ) | | |  | |     ___   __ _ ";
const char banner2[] PROGMEM = "|   / | _|   / /  |_  _| | |__  / _ \\ / _` |";
const char banner3[] PROGMEM = "|_|_\\ |_|   /___|   |_|  |____| \\___/ \\__, |";
const char banner4[] PROGMEM = "                                      |___/ ";

void setup()
{
   // configure serial port baudrate
   Serial.begin(57600);
   // DO NOT set serial port appender
   // rf24Logger.setAppender(&rf24SerialLogAppender);

   Serial.println("There is no appender defined. Nothing should be logged.");

   // display banner
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) banner0);
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) banner1);
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) banner2);
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) banner3);
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) banner4);
}

void logSimpleRamMessage();
void logFloatNumber();

void loop()
{
   logSimpleRamMessage();

   delay(5000);
}

void logSimpleRamMessage()
{
   rf24Logger.error((const __FlashStringHelper*) vendorID,
         "Error message defined in RAM");
   rf24Logger.warn((const __FlashStringHelper*) vendorID,
         "Warning message defined in RAM");
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         "Info message defined in RAM");
   rf24Logger.debug((const __FlashStringHelper*) vendorID,
         "Debug message defined in RAM");
   rf24Logger.trace((const __FlashStringHelper*) vendorID,
         "Trace message defined in RAM");

   Serial.println();
}
