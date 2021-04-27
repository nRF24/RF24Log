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

#include <string.h>
#include <RF24Logger.h>

#ifdef ARDUINO
#include <Arduino.h>
#include <RF24Loggers/ArduinoPrintLogger.h>

// Create hardware serial port log handler
ArduinoPrintLogger serialLogHandler(&Serial);

#elif PICO_BUILD
#include "pico/stdlib.h"  // printf(), sleep_ms(), getchar_timeout_us(), to_us_since_boot(), get_absolute_time()
#include "pico/bootrom.h" // reset_usb_boot()
#include <tusb.h>         // tud_cdc_connected()
#include <RF24Loggers/PrintfLogger.h>

// Create hardware serial port log handler
PrintfLogger serialLogHandler(&printf);

#else
#include <iostream>
#include <RF24Loggers/OStreamLogger.h>

// Create hardware serial port log handler
OStreamLogger serialLogHandler(&std::cout);
#endif

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";

void setup()
{
#ifdef ARDUINO
  // configure serial port baudrate
  Serial.begin(115200);
#elif defined (PICO_BUILD)
  // wait here until the CDC ACM (serial port emulation) is connected
  while (!tud_cdc_connected()) {
    sleep_ms(10);
  }
#endif

  // set maximal log level to ALL
  serialLogHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port handler
  rf24Logger.setHandler(&serialLogHandler);

  RF24LOGGER_info(vendorID, "RF24Log/examples/BasicSerialLogger");
}

void loop()
{
#ifdef ARDUINO
  if (Serial.available()) {
    char input = Serial.read();
    uint8_t count = 0;
    while (Serial.available()) {
      if (input >= 48 && input < 56) {
        count <<= 3;
        count += input - 48;
      } else {
        break;
      }
    }
    Serial.print("Set log level (in octal) to ");
    Serial.println(count, OCT);
    serialLogHandler.setLogLevel(count);
  }
#elif defined (PICO_BUILD)
  char input;
  input = getchar_timeout_us(5000); // get char from buffer for user input after 5 sec
  uint8_t count = 0;
  if (input != PICO_ERROR_TIMEOUT) {
    printf("Set log level (in octal) to ");
  }
  while (input != PICO_ERROR_TIMEOUT) {
    if (input >= 48 && input < 56) {
      count <<= 3;
      count += input - 48;
    } else {
      break;
    }
    input = getchar_timeout_us(0); // get char from buffer for user input;
  }
  if (count) {
    printf("%o", count);
    serialLogHandler.setLogLevel(count);
  }

#endif

  RF24LOGGER_error(vendorID, "Error message");
  RF24LOGGER_warn(vendorID, "Warning message");
  RF24LOGGER_info(vendorID, "Info message");
  RF24LOGGER_debug(vendorID, "Debug message");

  RF24LOGGER_error(vendorID, "Error message with %s", "RAM string 1");
  RF24LOGGER_warn(vendorID, "Warning message with %s", "RAM string 2");

  RF24LOGGER_info(vendorID, " info log with double value %D", 3.14);
  RF24LOGGER_debug(vendorID, " warn log with double value %D", 2.71);

  RF24LOGGER_log(RF24LogLevel::INFO + 1, vendorID, "INFO + 1 message");
  RF24LOGGER_log(RF24LogLevel::WARN + 1, vendorID, "WARN + 1 message");
#ifdef ARDUINO
  Serial.println("");

  delay(5000);
#elif !defined(PICO_BUILD)
  // for non-Arduino & not Pico SDK
  // time.sleep(5); // TODO
#endif
}

#ifndef ARDUINO
int main()
{
  setup();
  while (1) {
    loop();
  }
  return 0;
}
#endif
