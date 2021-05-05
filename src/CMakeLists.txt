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
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogAbstracts/BaseHandler.h
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogAbstracts/common.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogAbstracts/Handler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogAbstracts/SpecifierFormat.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogAbstracts/Stream.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24LogAbstracts/Parsing.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers/NativePrintLogger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers/OStreamLogger.cpp
        )

    target_include_directories(RF24Log INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers
        ${CMAKE_CURRENT_LIST_DIR}/RF24Abstracts
        ${CMAKE_CURRENT_LIST_DIR}/handler_ext
        )
    return()
endif()

cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name
project(RF24Log
    LANGUAGES CXX
    VERSION 0.1.0
    )

add_library(rf24Log SHARED
    RF24Logging.cpp
    RF24LogLevel.h
    RF24LogAbstracts/BaseHandler.h
    RF24LogAbstracts/common.cpp
    RF24LogAbstracts/Handler.cpp
    RF24LogAbstracts/SpecifierFormat.cpp
    RF24LogAbstracts/Stream.cpp
    RF24LogAbstracts/Parsing.cpp
    RF24Loggers/NativePrintLogger.cpp
    RF24Loggers/OStreamLogger.cpp
    )


target_include_directories(rf24Log PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/RF24Loggers
    ${CMAKE_CURRENT_LIST_DIR}/RF24Abstracts
    ${CMAKE_CURRENT_LIST_DIR}/handler_ext
    )

install(TARGETS rf24Log
    DESTINATION lib
    )

install(FILES
        RF24Logging.cpp
        RF24Logging.h
        RF24LogLevel.h
    DESTINATION include/RF24Log
    )

install(FILES
        RF24LogAbstracts/BaseHandler.h
        RF24LogAbstracts/common.cpp
        RF24LogAbstracts/common.h
        RF24LogAbstracts/Handler.cpp
        RF24LogAbstracts/Handler.h
        RF24LogAbstracts/SpecifierFormat.cpp
        RF24LogAbstracts/SpecifierFormat.h
        RF24LogAbstracts/Stream.cpp
        RF24LogAbstracts/Stream.h
        RF24LogAbstracts/Parsing.cpp
        RF24LogAbstracts/Parsing.h
    DESTINATION include/RF24Log/RF24LogAbstracts
    )

install(FILES
        RF24Loggers/NativePrintLogger.cpp
        RF24Loggers/NativePrintLogger.h
        RF24Loggers/OStreamLogger.cpp
        RF24Loggers/OStreamLogger.h
    DESTINATION include/RF24Log/RF24Loggers
    )
