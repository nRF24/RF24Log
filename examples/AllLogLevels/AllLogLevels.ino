/**
 * Created on: 31 Mar 2021
 *     Author: Witold Markowski (wmarkow)
 *
 * Copyright (C)
 *    2020        Witold Markowski (wmarkow)
 *    2021        Brendan Doherty (2bndy5) <br>
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#include <string.h>
#include <RF24Logging.h>

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
OStreamLogger serialLogHandler((std::ostream*)&std::cout);
#endif

// Define global vendor id (it is stored in FLASH memory)
const char PROGMEM vendorID[] = "RF24LogExample";
const char PROGMEM uiPrompt[] = "user input";

void setup()
{
#ifdef ARDUINO
  // configure serial port baudrate
  Serial.begin(115200);
  while (!Serial) {/* some boards need this */ ; }
#elif defined (PICO_BUILD)
  // wait here until the CDC ACM (serial port emulation) is connected
  while (!tud_cdc_connected()) {
    sleep_ms(10);
  }
#endif

  // set maximal log level to ALL
  serialLogHandler.setLogLevel(RF24LogLevel::ALL);
  // set serial port handler
  rf24Logging.setHandler(&serialLogHandler);

  RF24Log_info(vendorID, "RF24Log/examples/AllLogLevelsLogger");
}

void loop()
{
  uint8_t level = 0;
  char input;

#ifdef ARDUINO
  if (Serial.available()) {
    input = Serial.read();
    while (Serial.available() && input >= 48 && input < 56) {
      level <<= 3;
      level += input - 48;
      input = Serial.read();
    }
  }
#elif defined (PICO_BUILD)
  input = getchar_timeout_us(5000); // get char from buffer for user input after 5 sec
  while (input != PICO_ERROR_TIMEOUT && input >= 48 && input < 56) {
    level <<= 3;
    level += input - 48;
    input = getchar_timeout_us(1000); // get char from buffer for user input after 1 sec
  }
#endif // platform specific user input

  if (level) {
    RF24Log_log(1, uiPrompt, "Set log level (in octal) to %o\n", level);
    serialLogHandler.setLogLevel(level);
  }

  level = 0;
  do {
    RF24Log_log(level, vendorID, "A log message from %s on level %3d", "loop()", level);
    level++;
  } while (level);

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
#ifdef PICO_BUILD
  stdio_init_all(); // init necessary IO for the RP2040
#endif
  setup();
  while (1) {
    loop();
  }
  return 0;
}
#endif
