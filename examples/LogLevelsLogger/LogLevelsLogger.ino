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


void logSimpleMessage();

void setup()
{
    // configure serial port baudrate
    Serial.begin(115200);

    // set maximal log level to ALL
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::ALL);
    // set serial port appender
    rf24Logger.setHandler(&rf24SerialLogHandler);

    RF24LOGGER_info(vendorID, "RF24Log/examples/LogLevelsLogger");
}

void loop()
{
    Serial.println("Set log level to OFF");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::OFF);
    logSimpleMessage();

    Serial.println("Set log level to ERROR");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::ERROR);
    logSimpleMessage();

    Serial.println("Set log level to ERROR + 1");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::ERROR + 1);
    logSimpleMessage();

    Serial.println("Set log level to ERROR + 7");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::ERROR + 7);
    logSimpleMessage();

    Serial.println("Set log level to WARN");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::WARN);
    logSimpleMessage();

    Serial.println("Set log level to INFO");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::INFO);
    logSimpleMessage();

    Serial.println("Set log level to DEBUG");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::DEBUG);
    logSimpleMessage();

    Serial.println("Set log level to DEBUG + 1");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::DEBUG + 1);
    logSimpleMessage();

    Serial.println("Set log level to DEBUG + 7");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::DEBUG + 7);
    logSimpleMessage();

    Serial.println("Set log level to ALL");
    rf24SerialLogHandler.setLogLevel(RF24LogLevel::ALL);
    logSimpleMessage();

    Serial.println("");
    delay(5000);
}

void logSimpleMessage()
{
    RF24LOGGER_error(vendorID, "Error message");
    RF24LOGGER_log(RF24LogLevel::ERROR + 1, vendorID, "Error message sub-level 1");
    RF24LOGGER_log(RF24LogLevel::ERROR + 7, vendorID, "Error message sub-level 7");

    RF24LOGGER_warn(vendorID, "Warning message");
    RF24LOGGER_log(RF24LogLevel::WARN + 1, vendorID, "Warning message sub-level 1");
    RF24LOGGER_log(RF24LogLevel::WARN + 7, vendorID, "Warning message sub-level 7");

    RF24LOGGER_info(vendorID, "Info message");
    RF24LOGGER_log(RF24LogLevel::INFO + 1, vendorID, "Info message sub-level 1");
    RF24LOGGER_log(RF24LogLevel::INFO + 7, vendorID, "Info message sub-level 7");

    RF24LOGGER_debug(vendorID, "Debug message");
    RF24LOGGER_log(RF24LogLevel::DEBUG + 1, vendorID, "Debug message sub-level 1");
    RF24LOGGER_log(RF24LogLevel::DEBUG + 7, vendorID, "Debug message sub-level 7");

    Serial.println();
}
