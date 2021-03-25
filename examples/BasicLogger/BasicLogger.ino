/**
 * Documentation is hosted at https://2bndy5.github.io/Rf24Log
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A basic logging example using RF24Log library
 */
#include "RF24Log.h"

void setup() {

    Serial.begin(115200);
    while (!Serial) {} // wait for native usb supported devices

    Ardout ardout(&Serial);
    // set output stream to Serial object
    logging.setHandler(&ardout);

    // print an origin agnostic message
    logging.getLogger() << "Starting BasicLogger Example" << 1 << endl;

    // set a default origin name for all messages
    logging.setName("RF24Log");

    // by default, messages for all logging levels are output
    logging.setLevel(DEBUG); // set to debug level

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
    delay(2000); // slow down loop for readability
}