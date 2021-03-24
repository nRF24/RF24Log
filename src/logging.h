#ifndef LOGGING_H
#define LOGGING_H

/* macros for testing
#define ARDUINO // tricking Intellisense
 */

#ifndef ARDUINO

#include <cstdint> // uint8_t
#include <string>  // std::string
#include <ostream> // std::ostream, std::endl
#include <ctime>   // time_t, time(), ctime()

#define Stream_t std::ostream
#define str_t std::string
#define endl std::endl

#else // defined(ARDUINO)

#ifndef ARDUINO_API_VERSION
#include "Arduino.h"       // PROGMEM
#include "WString.h"       // for String datatype

#else // defined(ARDUINO_API_VERSION)
#include "api/AruinoAPI.h"
#include "String.h"        // for String datatype
#endif // defined(ARDUINO_API_VERSION)

#include "Print.h" // doesn't use pgmspace.h if defined(ARDUINO_API_VERSION)

#define Stream_t Print
#define str_t String

// To use `Serial.print(data);` as `Serial << data;`
template <class T>
inline Print &operator <<(Print &obj, T arg)
{
    obj.print(arg);
    return obj;
}

enum _EndLineCode { endl };

// To use `Serial.println();` as `Serial << endl;`
inline Print &operator <<(Print &obj, _EndLineCode arg)
{
    obj.println();
    return obj;
}

#endif // defined(ARDUINO)

#ifndef PROGMEM
#define PROGMEM
#endif

#define rf24_min(a, b) (a < b ? a : b)

/**
 * @defgroup logLevels Logging Levels
 * These values are used in magnitudes of 10
 * @{
 */
/** This level is the default and will output messages of any level */
#define NOT_SET 0
/** This level is for debugging outputs and will output messages of DEBUG, INFO, WARN, & ERROR levels */
#define DEBUG   1
/** This level is for informative outputs and will output messages of INFO, WARN, & ERROR levels */
#define INFO    2
/** This level is for warning outputs and will output messages of WARN & ERROR levels */
#define WARN    3
/** This level is for error outputs and will output messages of only ERROR levels */
#define ERROR   4

#ifdef DOXYGEN_FORCED
/**@}
 * @defgroup streamTypeDoc StreamType
 * This is just a placeholder for documenting the datatype of the output stream that will be
 * used by the instance of a RF24Logger.
 * @{
 */
#define StreamType
#endif // defined(DOXYGEN_FORCED)

/**@}
 * A templated class for implementing a single logging object.
 * Copied logging (using RF24Logger(RF24Logger*)) objects will re-use the original handler and level.
 */
template <typename StreamType>
class RF24Logger
{
private:
    StreamType* handler; /** the output stream */
    uint8_t level; /** the logging level used to filter logging messages */
    str_t _name; /** the logger instance's name */

    const PROGMEM char levelDesc0[] = "NOT_SET";
    const PROGMEM char levelDesc1[] = "DEBUG";
    const PROGMEM char levelDesc2[] = "INFO";
    const PROGMEM char levelDesc3[] = "WARN";
    const PROGMEM char levelDesc4[] = "ERROR";
    const PROGMEM char *levelDesc[] = {levelDesc0,
                                       levelDesc1,
                                       levelDesc2,
                                       levelDesc3,
                                       levelDesc4};

public:

    /** Empty constructor. level defaults to NOT_SET, and instance has no handler.  */
    RF24Logger() : level(NOT_SET), handler(nullptr) { _name = str_t(""); }

    /**
     * Instance constructor. level defaults to NOT_SET, and instance's handler is initialized.
     * @param stream The handler to which all logging output will be directed.
     * @param name The origin's name of the logger's messages.
     */
    RF24Logger(StreamType* stream, str_t name) : level(NOT_SET), handler(stream) { _name = str_t(name); }

    /**
     * Copy constructor. Instance's log level and handler are set to @p obj instance's corresponding values.
     * @param obj An instantiated RF24Logger object from which values are copied from.
     */
    RF24Logger(RF24Logger* obj) : handler(obj->handler), level(obj->level) { _name = str_t(""); }

    /**
     * Set the handler to which all logging messages are directed.
     * @param stream The output stream to be used as the handler.
     */
    void sethandler(StreamType &stream) { handler = stream; }

    /**
     * Set the logging level that's to filter logging messages passed to log()
     * @param lvl The logging level must be in range [0, 60).
     */
    void setLevel(uint8_t lvl) { level = rf24_min(lvl, ERROR * 10 + 9); }

    /**
     * @brief Set a default @p name for the instance
     *
     * This will be used in calls to log(uint8_t lvl, Ts msg...)
     */
    void setName(str_t name) { _name = name; }

    /**
     * Returns the logging handler that was configured with RF24Logger(S*) or setHandler()
     *
     * Example usage:
     * @code
     * logging.getLogger() << "a string of text " << 0 << ':' << 1.0 << endl;
     * @endcode
     * would ouput "a string of text 0:1.0" with a trailing line feed.
     */
    StreamType* getLogger() { return handler; }

    /**
     * Log a message
     * @param lvl The logging level used for the specified message.
     * @param msg The specified message.
     */
    template <typename... Ts>
    void log(uint8_t lvl, Ts... msg) { log(lvl, name, msg...); }

    /**
     * @brief Log a message
     * @param lvl The logging level used for the specified message.
     * @param vendorId The orgin of the message.
     * @param msg The specified message.
     */
    template <typename... Ts>
    void log(uint8_t lvl, str_t vendorId, Ts... msg)
    {
        if (lvl < level || handler == nullptr)
            return;

        outputTimestamp() << ':' << outputLoglevel() << ':' <<  outputData(vendorId) << '=' << outputData(msg) << endl;
    }

    /**
     * @brief output a @ref INFO level message
     * @param msg The message to output.
     */
    template <typename... Ts>
    void info(TS... msg) { log(INFO * 10, name, msg...); }

    /**
     * @brief output a @ref DEBUG level message
     * @param msg The message to output.
     */
    template <typename... Ts>
    void debug(TS... msg) { log(DEBUG * 10, name, msg...); }

    /**
     * @brief output a @ref WARN level message
     * @param msg The message to output.
     */
    template <typename... Ts>
    void warn(TS... msg) { log(WARN * 10, name, msg...); }

    /**
     * @brief output a @ref ERROR level message
     * @param msg The message to output.
     */
    template <typename... Ts>
    void error(TS... msg) { log(ERROR * 10, name, msg...); }

protected:

    /**
     * @brief output a timestamp for the proceeding message
     */
    StreamType* outputTimestamp()
    {
        time_t now;
        time(&now);
        return outputData(ctime(now));
    }

    /**
     * @brief output an appropriate log level for the proceeding message
     */
    StreamType* outputLoglevel()
    {
        if (level % 10 == 0) {
            handler << levelDesc[level / 10];
        }
        else if (level < ERROR * 10 + 9) {
            handler << "Level " << level;
        }
        return handler;
    }

    /**
     * @brief output an arbitrary type of data
     *
     * This is our base case for parameter unpacking
     * @param data The data to output
     */
    template <typename Tdata>
    StreamType* outputData(Tdata data)
    {
        handler << data;
        return handler;
    }

    /**
     * @brief output an arbitrary type of data
     *
     * This is our recursive scenario for parameter unpacking
     * @param data The data to output
     * @param rest the pack of sequential parameters
     */
    template <typename Tdata, typename... Rest>
    StreamType* outputData(Tdata data, Rest... rest)
    {
        handler << data;
        return outputData(rest...);
    }

};

/** @brief A convenient singleton to get started quickly */
extern RF24Logger<Stream_t> logging;

#endif // LOGGING_H

/**
 * @example BasicLogger.ino
 * A basic logging example using RF24Log library
 */