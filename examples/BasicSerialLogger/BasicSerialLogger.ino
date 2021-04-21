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

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";

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

    RF24LOGGER_info(vendorID, "RF24Log/examples/BasicSerialLogger");

    RF24LOGGER_info(vendorID, "This comes from macro.");
}

void logSimpleMessage();
void logMessageWithRamStringArgument();
void logFloatNumber();
void logCustomLogLevels();

void loop()
{
    logSimpleMessage();
    logMessageWithRamStringArgument();
    logFloatNumber();
    logCustomLogLevels();

    Serial.println();
    Serial.println("--------------------------------------------------");
    Serial.println();

        delay(5000);
}

void logSimpleMessage()
{
    RF24LOGGER_error(vendorID, "Error message");
    RF24LOGGER_warn(vendorID, "Warning message");
    RF24LOGGER_info(vendorID, "Info message");
    RF24LOGGER_debug(vendorID, "Debug message");

    Serial.println();
}


void logMessageWithRamStringArgument()
{
    RF24LOGGER_error(vendorID, "Error message with %s", "RAM string 1");
    RF24LOGGER_warn(vendorID, "Warning message with %s", "RAM string 2");
    RF24LOGGER_info(vendorID, "Info message with %s", "RAM string 3");
    RF24LOGGER_debug(vendorID, "Debug message with %s", "RAM string 4");

    Serial.println();
}

void logFloatNumber()
{
    RF24LOGGER_info(vendorID, " info log with double value %D", 3.14);
    RF24LOGGER_warn(vendorID, " warn log with double value %D", 3.14);
    RF24LOGGER_error(vendorID, "error log with double value %D", 3.14);
    RF24LOGGER_debug(vendorID, "debug log with double value %F", 2.71);

    Serial.println();
}

void logCustomLogLevels()
{
    RF24LOGGER_log(RF24LogLevel::INFO + 1, vendorID, "INFO + 1 message");
    RF24LOGGER_log(RF24LogLevel::WARN + 1, vendorID, "WARN + 1 message");

    Serial.println();
}
