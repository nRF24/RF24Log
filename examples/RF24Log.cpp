#include <Arduino.h>
#include <string.h>

#include "../src/RF24Logger.h"
#include "../src/RF24HardwareSerialLogAppender.h"

// create hardware serial port log appender
RF24HardwareSerialLogAppender serialLogAppender(&Serial);

// define global vendor id (it is stored in flash memory)
const char vendorID[] PROGMEM = "RF24LogExample";
const char textFromFlash[] PROGMEM
      = "******************************************";

void setup()
{
   // configure serial port baudrate
   Serial.begin(57600);
   // set serial port appender
   rf24Logger.setAppender(&serialLogAppender);

   // Info string in flash memory
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         F("******************************************"));
   // Info string in RAM memory
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         "***          Logging example           ***");
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) textFromFlash);
}

void loop()
{
   //__FlashStringHelper cannot be declared oustide a function
   const __FlashStringHelper *flashText = F("this is a flash text");

   rf24Logger.info((const __FlashStringHelper*) vendorID, flashText);

   rf24Logger.error((const __FlashStringHelper*) vendorID,
         "Log as info message");
   rf24Logger.warn((const __FlashStringHelper*) vendorID,
         "Log as warning message");
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         "Log as error message");
   rf24Logger.debug((const __FlashStringHelper*) vendorID,
         "Log as debug message");
   rf24Logger.trace((const __FlashStringHelper*) vendorID,
         "Log as trace message");

   delay(5000);
}
