/**
 * Documentation is hosted at https://nRF24.github.io/RF24Log
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A basic logging example using RF24Log library
 */
#include "RF24Log.h"

PrintOut ardout(&Serial);

void setup() {

  Serial.begin(115200);
  while (!Serial) {} // wait for native usb supported devices

  // set output stream to Serial object
  logging.setHandler(&ardout);

  // print an origin agnostic message
  logging.getLogger() << endl << "Starting BasicLogger Example" << endl;
  // which is usably equivalent to the following
  ardout << "A prompt without using the logging object" << endl << endl;

  // set a default origin name for all messages
  logging.setName("RF24Log");

  // by default, messages for all logging levels are disabled
  logging.setLevel(DEBUG); // set to debug level (0 will disable logging messages)
}

void loop() {
  logging.debug("This is a DEBUG message");
  logging.info("This is an INFO message");
  logging.warn("This is a WARN message");
  logging.error("This is an ERROR message");
  logging.log(11, "This is a message for a custom DEBUG sublevel");
  logging.logOrigin(12, "SimonSays", "This is a message from a specific code block");
  logging.log(20, "This is an INFO message");
  logging.logOrigin(21, "End:of:Loop", "This is a message for a custom INFO sublevel");
  delay(1000); // slow down loop for readability
}