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

############################
# for non-RPi-Pico platforms
############################
cmake_minimum_required(VERSION 3.15)

# optionally build a debian install-able package (.deb file) instead of installing library
option(BUILD_DEB_PKG "set to on to build a debian package" OFF)

# Set the project name to your project name
project(RF24Log_lib C CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
add_compile_options(-Ofast -Wall)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# enable cache system
include(cmake/Cache.cmake)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# get library info from Arduino IDE's required library.properties file
include(cmake/GetLibInfo.cmake) # sets the variable LibTargetName

###########################
# create target for bulding the RF24Log lib
###########################
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

target_link_libraries(${LibTargetName} INTERFACE
    project_options
    project_warnings
    )

###########################
# target install rules for the RF24Log lib
###########################
install(TARGETS ${LibTargetName}
    DESTINATION lib
    )

install(FILES
        RF24Logging.h
        RF24LogBaseHandler.h
        RF24LogLevel.h
    DESTINATION include/RF24Log
    )

install(FILES
        RF24LogParts/Common.h
        RF24LogParts/LevelDescriptions.h
        RF24LogParts/AbstractHandler.h
        RF24LogParts/FormatSpecifier.h
        RF24LogParts/AbstractStream.h
        RF24LogParts/PrintfParser.h
    DESTINATION include/RF24Log/RF24LogParts
    )

install(FILES
        RF24Loggers/NativePrintLogger.h
        RF24Loggers/OStreamLogger.h
    DESTINATION include/RF24Log/RF24Loggers
    )

# CMAKE_CROSSCOMPILING is only TRUE when CMAKE_TOOLCHAIN_FILE is specified via CLI
if(CMAKE_HOST_UNIX AND "${CMAKE_CROSSCOMPILING}" STREQUAL "FALSE" AND NOT BUILD_DEB_PKG)
    install(CODE "message(STATUS \"Updating ldconfig\")")
    install(CODE "execute_process(COMMAND ldconfig)")
endif()

# prepare to build a debian package
if(BUILD_DEB_PKG)
    include(cmake/createDebianPkg.cmake)
endif()
