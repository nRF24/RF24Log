#ifndef LOGGING_H
#define LOGGING_H

/* macros for testing
#define ARDUINO
 */

#ifndef ARDUINO

#include <cstdint> // datatypes (uint8_t)
#include <string>  // datatype (std::string) and other useful coversion functions
#include <ostream> // for building an output stream (includes cout)
#include <ctime>   // for creating timestamps

#ifndef PROGMEM
#define PROGMEM
#endif

#else // defined(ARDUINO)

#ifndef ARDUINO_API_VERSION
#include "Arduino.h"
#else // defined(ARDUINO_API_VERSION)
#include "api/AruinoAPI.h"
#endif // defined(ARDUINO_API_VERSION)

#include "String.h"
#include "Print.h"

// To use `Serial.print(data);` as `Serial << data;`
template <class T>
inline Print &operator <<(Print &obj, T arg)
{
    obj.print(arg);
    return obj;
}

enum _EndLineCode { endl };

inline Print &operator <<(Print &obj, _EndLineCode arg)
{
    obj.println();
    return obj;
}

#endif // defined(ARDUINO)


#define rf24_max(a, b) (a > b ? a : b)
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
    uint8_t level; /** the leevel that all messages are filtered with */

#ifdef ARDUINO
    String name;
#else
    std::string name;
#endif

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
    RF24Logger() : level(NOT_SET) { handler = nullptr; }

    /**
     * Instance constructor. level defaults to NOT_SET, and instance's handler is initialized.
     * @param stream The handler to which all logging output will be directed.
     */
    RF24Logger(StreamType* stream) : level(NOT_SET) { handler = stream; }

    /**
     * Copy constructor. Instance's log level and handler are set to @p obj instance's corresponding values.
     * @param obj An instantiated RF24Logger object from which values are copied from.
     */
    RF24Logger(RF24Logger* obj) { handler = obj->handler; level = obj->level; }

    /**
     * Set the handler to which all logging messages are directed.
     * @param stream The output stream to be used as the handler.
     */
    void sethandler(StreamType &stream) { handler = stream; }

    /**
     * Set the logging level that's to filter logging messages passed to log()
     * @param lvl The logging level must be in range [0, 60).
     */
    void setLevel(uint8_t lvl) { level = rf24_max(lvl, ERROR * 10 + 9); }

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
    void log(uint8_t lvl, Ts msg...) { log(lvl, name, msg); }

    /**
     * @brief Log a message
     * @param lvl The logging level used for the specified message.
     * @param vendorId The orgin of the message.
     * @param msg The specified message.
     */
    template <typename... Ts>
    void log(uint8_t lvl, std:string vendorId, Ts msg...)
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
    void info(TS msg...) { log(INFO * 10, msg); }

    /**
     * @brief output a @ref DEBUG level message
     * @param msg The message to output.
     */
    template <typename... Ts>
    void degub(TS msg...) { log(DEBUG * 10, msg); }

    /**
     * @brief output a @ref WARN level message
     * @param msg The message to output.
     */
    template <typename... Ts>
    void warn(TS msg...) { log(WARN * 10, msg); }

    /**
     * @brief output a @ref ERROR level message
     * @param msg The message to output.
     */
    template <typename... Ts>
    void error(TS msg...) { log(ERROR * 10, msg); }

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
    template <typename Tdata, typename... Rest>
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

#ifdef ARDUINO
extern RF24Logger<Print> logging;

#else // !defined(ARDUINO)
/** @brief A convenient singleton to get started quickly */
extern RF24Logger<std::ostream> logging;
#endif // !defined(ARDUINO)


#endif // LOGGING_H

/**
 * @example BasicLogger.ino
 * A basic logging example using RF24Log library
 */