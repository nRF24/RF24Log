/**
 * Created on: 21 Oct 2020
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

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";

// DO NOT create hardware serial port log appender
// RF24StreamLogHandler rf24SerialLogHandler(&Serial);

void setup()
{
    // configure serial port baudrate
    Serial.begin(115200);
    // DO NOT set serial port appender
    // rf24Logger.setAppender(&rf24SerialLogAppender);

    Serial.println("There is no appender defined. Nothing should be logged.");

    RF24LOGGER_info(vendorID, "RF24Log/examples/EmptyLogger");
}

void logSimpleMessage();

void loop()
{
    logSimpleMessage();

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
