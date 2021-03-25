#include <iostream>
#include "../src/RF24Log.h"

void setup()
{
    logging.setHandler(&std::cout);
    logging.getLogger() << "logger using cout" << endl;
}

int main()
{
    setup();

    return 0;
}
