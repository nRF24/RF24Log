cmake_minimum_required(VERSION 3.12)

# iterate over a list of examples by name
set(EXAMPLES_LIST
    GettingStarted
    AllLogLevels
    )

option(USE_PICO_SDK "Use the Pico SDK to build the RF24Log lib's examples" OFF)

if (USE_PICO_SDK)
    # Pull in SDK (must be before project)
    include(../src/cmake/pico_sdk_import.cmake)

    project(pico_examples C CXX ASM)

    # Initialize the Pico SDK
    pico_sdk_init()

    # In YOUR project, include RF24's CMakeLists.txt
    # giving the path depending on where the library
    # is cloned to in your project
    include(../src/CMakeLists.txt)

    foreach(example ${EXAMPLES_LIST})
        #make a target
        add_executable(${example} ${example}.cpp)

        # link the necessary libs to the target
        target_link_libraries(${example} PUBLIC
            RF24Log
            pico_stdlib
            )

        # enable serial output over USB instead of RX/TX GPIO pins
        pico_enable_stdio_usb(${example} 1)
        pico_enable_stdio_uart(${example} 0)

        # create map/bin/hex file etc.
        pico_add_extra_outputs(${example})
    endforeach()

else() # if NOT USE_PICO_SDK

    project(RF24LogExamples)

    find_library(RF24Log rf24log)
    message(STATUS "using RF24Log at: ${RF24Log}")

    foreach(example ${EXAMPLES_LIST})
        #make a target
        add_executable(${example} ${example}.cpp)

        # link the RF24Log lib to the target
        target_link_libraries(${example} PUBLIC ${RF24Log}) # this command looks for the installed librf24log.so
    endforeach()
endif()
