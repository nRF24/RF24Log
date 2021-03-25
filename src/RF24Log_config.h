#define RF24Log_VERSION_MAJOR @RF24Log_VERSION_MAJOR@
#define RF24Log_VERSION_MINOR @RF24Log_VERSION_MINOR@
#define RF24Log_VERSION_PATCH @RF24Log_VERSION_PATCH@

#ifndef ARDUINO

#include <cstdint> // uint8_t
#include <string>  // std::string
#include <ostream> // std::ostream, std::endl
#include <ctime>   // time_t, time(), ctime()

#define Stream_t std::ostream
#define str_t std::string
#define endl std::endl

#else // defined(ARDUINO)
#include "ardout.h"
#endif // defined(ARDUINO)

#ifndef PROGMEM
#define PROGMEM
#endif

#ifndef pgm_read_ptr
#define pgm_read_ptr(p) (*(p))
#endif

#define rf24_min(a, b) (a < b ? a : b)
