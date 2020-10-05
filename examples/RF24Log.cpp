#include <Arduino.h>
#include <string.h>

#include "../src/RF24Logger.h"
#include "../src/RF24HardwareSerialLogAppender.h"

// create hardware serial port log appender
RF24HardwareSerialLogAppender serialLogAppender(&Serial);

// define global vendor id (it is stored in flash memory)
const char vendorID[] PROGMEM = "RF24LogExample";
const char globalProgmemText[] PROGMEM
= "global PROGMEM message";

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
}

void logSimpleRamMessage();
void logSimpleGlobalProgmemMessage();
void logSimpleFMacroMessage();
void logRamMessageWithRamStringArgument();
void logRamMessageWithProgmemStringArgument();
void logRamMessageWithFMacroStringArgument();

void loop()
{
   logSimpleRamMessage();
   logSimpleGlobalProgmemMessage();
   logSimpleFMacroMessage();
   logRamMessageWithRamStringArgument();
   logRamMessageWithProgmemStringArgument();
   logRamMessageWithFMacroStringArgument();

   //__FlashStringHelper cannot be declared oustide a function
   const __FlashStringHelper *flashText = F("this is a flash text");
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         "info log with string flash global argument   : %S", vendorID);
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         "info log with string flash local argument   : %S", flashText);

   rf24Logger.info((const __FlashStringHelper*) vendorID,
         "info log with unknown format   : %p", flashText);

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

void logSimpleGlobalProgmemMessage()
{
   rf24Logger.error((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) globalProgmemText);
   rf24Logger.warn((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) globalProgmemText);
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) globalProgmemText);
   rf24Logger.debug((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) globalProgmemText);
   rf24Logger.trace((const __FlashStringHelper*) vendorID,
         (const __FlashStringHelper*) globalProgmemText);

   Serial.println();
}

void logSimpleFMacroMessage()
{
   rf24Logger.error((const __FlashStringHelper*) vendorID,
         F("text from F macro"));
   rf24Logger.warn((const __FlashStringHelper*) vendorID,
         F("text from F macro"));
   rf24Logger.info((const __FlashStringHelper*) vendorID,
         F("text from F macro"));
   rf24Logger.debug((const __FlashStringHelper*) vendorID,
         F("text from F macro"));
   rf24Logger.trace((const __FlashStringHelper*) vendorID,
         F("text from F macro"));

   Serial.println();
}

void logRamMessageWithRamStringArgument()
{
   rf24Logger.error((const __FlashStringHelper*) vendorID,
         "RAM message with %s", "RAM string 1");
   rf24Logger.warn((const __FlashStringHelper*) vendorID, "RAM message with %s",
         "RAM string 2");
   rf24Logger.info((const __FlashStringHelper*) vendorID, "RAM message with %s",
         "RAM string 3");
   rf24Logger.debug((const __FlashStringHelper*) vendorID,
         "RAM message with %s", "RAM string 4");
   rf24Logger.trace((const __FlashStringHelper*) vendorID,
         "RAM message with %s", "RAM string 5");

   Serial.println();
}

void logRamMessageWithProgmemStringArgument()
{
   rf24Logger.error((const __FlashStringHelper*) vendorID,
         "RAM message with %S", (const __FlashStringHelper*) globalProgmemText);
   rf24Logger.warn((const __FlashStringHelper*) vendorID, "RAM message with %S",
         (const __FlashStringHelper*) globalProgmemText);
   rf24Logger.info((const __FlashStringHelper*) vendorID, "RAM message with %S",
         (const __FlashStringHelper*) globalProgmemText);
   rf24Logger.debug((const __FlashStringHelper*) vendorID,
         "RAM message with %S", (const __FlashStringHelper*) globalProgmemText);
   rf24Logger.trace((const __FlashStringHelper*) vendorID,
         "RAM message with %S", (const __FlashStringHelper*) globalProgmemText);

   Serial.println();
}

void logRamMessageWithFMacroStringArgument()
{
   rf24Logger.error((const __FlashStringHelper*) vendorID,
         "RAM message with %S", F("F macro string 1"));
   rf24Logger.warn((const __FlashStringHelper*) vendorID, "RAM message with %S",
         F("F macro string 2"));
   rf24Logger.info((const __FlashStringHelper*) vendorID, "RAM message with %S",
         F("F macro string 3"));
   rf24Logger.debug((const __FlashStringHelper*) vendorID,
         "RAM message with %S", F("F macro string 4"));
   rf24Logger.trace((const __FlashStringHelper*) vendorID,
         "RAM message with %S", F("F macro string 5"));

   Serial.println();
}
