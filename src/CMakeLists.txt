# Check if we are building a pico-sdk based project
# (or more exactly: if we just got included in a pico-sdk based project)
if (PICO_SDK_PATH)
    # If so, load the relevant CMakeLists-file but don't do anything else

    project(nRF24Log C CXX ASM)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 17)

    # Define the RF24Log core library
    add_library(RF24Log INTERFACE)

    target_sources(RF24Log INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/RF24Logging.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogLevel.h
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogBaseHandler.h
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogParts/Common.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogParts/LevelDescriptions.h
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogParts/AbstractHandler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogParts/FormatSpecifier.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogParts/AbstractStream.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogParts/PrintfParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers/NativePrintLogger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers/OStreamLogger.cpp
        )

    target_include_directories(RF24Log INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers
        ${CMAKE_CURRENT_LIST_DIR}/RF24Parts
        ${CMAKE_CURRENT_LIST_DIR}/handler_ext
        )

    return()
endif()

#################################
# build for x86/x84 platforms

cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name
project(RF24Log_lib C CXX)

add_compile_options(-Ofast -Wall -pthread)

include(cmake/PreventInSourceBuilds.cmake)

# set a variable to reuse the target name
set(LibTargetName rf24log) # this var is used in the GetLibVersion.cmake module

# get library version number (major, minor, patch) from Arduino IDE's required library.properties file
include(cmake/GetLibVersion.cmake)
message("RF24 library version: ${${LibTargetName}_VERSION_STRING}")

add_library(${LibTargetName} SHARED
    RF24Logging.cpp
    RF24LogBaseHandler.h
    RF24LogLevel.h
    RF24LogParts/Common.cpp
    RF24LogParts/LevelDescriptions.h
    RF24LogParts/AbstractHandler.cpp
    RF24LogParts/FormatSpecifier.cpp
    RF24LogParts/AbstractStream.cpp
    RF24LogParts/PrintfParser.cpp
    RF24Loggers/NativePrintLogger.cpp
    RF24Loggers/OStreamLogger.cpp
    )


target_include_directories(${LibTargetName} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers
    ${CMAKE_CURRENT_LIST_DIR}/RF24Parts
    ${CMAKE_CURRENT_LIST_DIR}/handler_ext
    )

install(TARGETS ${LibTargetName}
    DESTINATION lib
    )

install(FILES
        RF24Logging.cpp
        RF24Logging.h
        RF24LogBaseHandler.h
        RF24LogLevel.h
    DESTINATION include/RF24Log
    )

install(FILES
        RF24LogParts/Common.cpp
        RF24LogParts/Common.h
        RF24LogParts/LevelDescriptions.h
        RF24LogParts/AbstractHandler.cpp
        RF24LogParts/AbstractHandler.h
        RF24LogParts/FormatSpecifier.cpp
        RF24LogParts/FormatSpecifier.h
        RF24LogParts/AbstractStream.cpp
        RF24LogParts/AbstractStream.h
        RF24LogParts/PrintfParser.cpp
        RF24LogParts/PrintfParser.h
    DESTINATION include/RF24Log/RF24LogParts
    )

install(FILES
        RF24Loggers/NativePrintLogger.cpp
        RF24Loggers/NativePrintLogger.h
        RF24Loggers/OStreamLogger.cpp
        RF24Loggers/OStreamLogger.h
    DESTINATION include/RF24Log/RF24Loggers
    )
