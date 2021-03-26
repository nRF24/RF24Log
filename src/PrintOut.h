/**
 * @file PrintOut.h
 *
 * Copyright (C)
 *  2021        Brendan Doherty (2bndy5)
 *
 * This General Public License does not permit incorporating your program into
 * proprietary programs.  If your program is a subroutine library, you may
 * consider it more useful to permit linking proprietary applications with the
 * library.  If this is what you want to do, use the GNU Lesser General
 * Public License instead of this License.
 */

#ifndef ARDOUT_H
#define ARDOUT_H
#pragma once
#include "Arduino.h" // PROGMEM
// #include "stdlib.h"  // size_t
// #include "stdint.h"  // uint8_t
#include "Print.h"   // doesn't use pgmspace.h if defined(ARDUINO_API_VERSION)


/**
 * @ingroup streamTypeDoc
 * This macro will represent the `Print` class for Arduino-based API.
 */
#define Stream_t Print

/**
 * @defgroup endl endl
 * An enum used as a placeholder to give `Print::println()` a specific datatype.
 * @{
 */
/** @brief a privately used global enum */
enum _LineFeed { endl /** A zero value variable */ };
/** @} */

/**
 * Operator overload to implement using `Serial.println()` as `Serial << endl`
 * @param obj The reference to instantiated output stream obj
 * @param arg Due to the use of @ref _LineFeed, this parameter can only be 0.
 * @returns the @p obj referenced paramater
 */
inline Print &operator <<(Print &obj, _LineFeed arg)
{
    if (!arg) { obj.println(); }
    return obj;
}

/**
 * Operator overload to implement using `Serial.print(data)` as `Serial << data`
 * @param obj The reference to instantiated output stream obj
 * @param arg A templated parameter that can be anything that the output stream object can accept.
 * @returns the @p obj referenced paramater
 */
template <class T>
inline Print &operator <<(Print &obj, T arg)
{
    obj.print(arg);
    return obj;
}

/**
 * @brief A wrapper class that inherits from `Print` class.
 *
 * This class implements C++ `cout` output operator (`<<`) for any Arduino API that
 * inherit from the `Print` class (like the popular `Serial` objects).
 */
class PrintOut : public Print
{

private:
    /** a pointer to the specified output stream */
    Print* out_stream;

public:
    /** Empty contructor; output stream is uninitialized. */
    PrintOut() : out_stream(nullptr) {}

    /**
     * Instance constructor; initialize the output stream.
     * @note `Serial` objects still require `begin()` to be called prior to instantiation.
     * @param outStream The output stream to wrap
     */
    PrintOut(Print* outStream) : out_stream(outStream) {}

    /**
     * set or reconfigure the outputStream
     * @param outStream The output stream to wrap
     * @note `Serial` objects still require `begin()` to be called prior to instantiation.
     */
    void setStream(Print* outStream) { out_stream = outStream; }

    /**
     * Get the reference to the output stream
     * @returns The instantiated output stream passed to setStream()
     */
    Print& get() { return *out_stream; }

    template <class T>
    friend inline Print &operator <<(Print &obj, T arg);

    friend inline Print &operator <<(Print &obj, _LineFeed arg);

    /**
     * A virtual function overide that default to its parents' behavior
     * @param chr A byte to write to the outpput stream
     * @returns the amount of bytes written to the output stream
     */
    virtual size_t write(uint8_t chr) { return out_stream ? out_stream->write(chr) : 0; }

    /**
     * A virtual function overide that default to its parents' behavior
     * @param buf A byte array to write to the outpput stream
     * @param len The length of @p buf
     * @returns the amount of bytes written to the output stream
     */
    virtual size_t write(const uint8_t* buf, size_t len) { return out_stream ? out_stream->write(buf, len) : 0; }
};
#endif // ARDOUT_H
