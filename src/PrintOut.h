/**
 * @file ardout.h
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

#define Stream_t Print

enum _LineFeed { endl };

// To use `Serial.println();` as `Serial << endl;`
inline Print &operator <<(Print &obj, _LineFeed arg)
{
    if (!arg) { obj.println(); }
    return obj;
}

// To use `Serial.print(data);` as `Serial << data;`
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
 * inherit from the `Print` class (like the popular `Serial`objects).
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

    /** get the reference to the output stream */
    Print& get() { return *out_stream; }

    template <class T>
    friend inline Print &operator <<(Print &obj, T arg);

    friend inline Print &operator <<(Print &obj, _LineFeed arg);

    // the following methods are overiden virtual functions that default to their parents' behavior
    // I'm not documenting these
    virtual size_t write(uint8_t chr) { return out_stream ? out_stream->write(chr) : 0; }
    virtual size_t write(const uint8_t* buf, size_t len) { return out_stream ? out_stream->write(buf, len) : 0; }
};
#endif // ARDOUT_H
