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
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogHandler.h
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogAbstracts.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogAbstracts.h
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers/PrintfLogger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers/PrintfLogger.h
        # pico_stdlib
        )

    target_include_directories(RF24Log INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers
        ${CMAKE_CURRENT_LIST_DIR}/handler_ext
        )
    return()
endif()

cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name, my project isn't very descriptive
project(nRF24Log CXX)
