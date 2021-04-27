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

  RF24LOGGER_info(vendorID, "RF24Log/examples/AllLogLevelsLogger");
}

void loop()
{
  for (uint16_t logLevel = 0 ; logLevel <= 255 ; logLevel ++)
  {
    RF24LOGGER_log((uint8_t)logLevel, vendorID, "This is a log message with level %d", logLevel);
  }
#ifdef ARDUINO
  Serial.println("");

  delay(5000);
#elif !defined(PICO_BUILD)
  // for non-Arduino & not Pico SDK
  std::cout << std::endl;
  // time.sleep(1); // TODO
#endif
}

#ifndef ARDUINO
int main()
{
  setup();
  while (1) { loop(); }
  return 0;
}
#endif
