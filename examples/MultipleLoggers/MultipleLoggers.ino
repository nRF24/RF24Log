/**
 * Documentation is hosted at https://2bndy5.github.io/Rf24Log
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A example using RF24Log library to log multiple "libraries" (basic class structures
 * in this example). We expect that only 1 of the libraries will actually print
 * something during `loop()` because we filter out the logging from the MyLib2 object
 * using a different/higher logging level (specifically set by the MyLib2 class' c'tor).
 */
#include "RF24Log.h"

PrintOut ardout(&Serial);

class MyLib1
{
private:
    RF24Logger<Stream_t> logger;

public:
  MyLib1() {
    logger = RF24Logger<Stream_t>(&logging);
    logger.setName("MyLib1");
    logger.info("object instantiated successfully!");
  }

  void func(uint8_t arg) {
    logger.logOrigin(INFO, "MyLib1.func", "received ", arg, " as an argument");
  }
};

class MyLib2
{
private:
    RF24Logger<Stream_t> logger;

public:
  MyLib2() {
    logger = RF24Logger<Stream_t>(&logging);
    logger.setName("MyLib2");
    logger.info("object instantiated successfully!");
    logger.setLevel(WARN); // notice this is after we called logger.info()
  }

  void func(uint8_t arg) {
    logger.logOrigin(INFO, "MyLib2.func", "received ", arg, " as an argument");
  }
};

MyLib1* lib1 = nullptr;
MyLib2* lib2 = nullptr;

void setup() {

  // DO THIS BEFORE INSTANTIATING THE EXAMPLES' CLASSES (MyLib1 & MyLib2)
  Serial.begin(115200);
  while (!Serial) {} // wait for native usb supported devices

  // set output stream to Serial object
  logging.setHandler(&ardout);

  logging.setLevel(INFO);

  // print an origin agnostic message
  logging.getLogger() << "Starting MultipleLogger Example" << endl;

  lib1 = new MyLib1();
  lib2 = new MyLib2();
}

void loop() {
  lib1->func(1);
  lib2->func(2);
  delay(1000); // slow down loop for readability
}
