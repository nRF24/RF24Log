# RaspberryPi Pico SDK (for the RP2040)
Just to be very clear and concise: The following instructions are
**not required to use the Arduino IDE** with any RP2040-based boards.
These instructions pertain to using only the
[Raspberry Pi foundation's Pico SDK](https://github.com/raspberrypi/pico-sdk)
for RP2040 based boards.

## Prerequisite
Follow the Raspberry Pi Foundation's
["Getting Started with Pico" document](https://rptl.io/pico-get-started) to
setup a proper development environment on your host PC (the machine that
will build your project). Notice that the setup instructions are a little
different for building on a Windows PC.

Either set an environment variable named `PICO_SDK_PATH` that points to your
local clone of the pico-sdk or put the pico-sdk next to the RF24Log folder or
next to the folder containing your project using the RF24Log library:

    path/to/github/repos/
        pico-sdk/
        RF24Log/
        my_rf24_project/

Alternatively, the RF24Log repository can be included into your project's "lib"
folder as copies or git submodules. For more detail, see the below
instructions to incorporate RF24* libs into your project.

## Building the RF24Log examples for the Pico SDK

1. Create a "build" directory in the RF24Log repository's root directory and
   navigate to it:
   ```shell
   cd RF24Log
   mkdir build
   cd build
   ```
2. Configure CMake for your desired build type and specific RP2040-based board
   ```shell
   cmake ../examples -DUSE_PICO_SDK=ON -DCMAKE_BUILD_TYPE=Release -DPICO_BOARD=pico
   ```
   Or if building on a Windows PC:
   ```shell
   cmake -G "NMake Makefiles" ../examples -DUSE_PICO_SDK=ON -DCMAKE_BUILD_TYPE=Release -DPICO_BOARD=pico
   ```
   @warning The  `-DUSE_PICO_SDK=ON` option is required! Otherwise, the examples will be built for
   Linux/Windows platforms because the examples' code is cross-compatible.<br>

   The supported RP2040-based boards are listed in header files in the Pico SDK
   repository's [pico-sdk/src/boards/include/boards/\<board_name>.h files](https://github.com/raspberrypi/pico-sdk/tree/master/src/boards/include/boards).
   If the `-DPICO_BOARD` option is not specified, then the Pico SDK will default to
   building for the Raspberry Pi Pico board.
3. Build the examples using the CMakeLists.txt file located in the
   RF24Log/examples directory.
   ```shell
   cmake --build . --config Release
   ```
   Notice we specified the build type again using the `--config` option.

## Incorporating RF24* libs into your project
In order to use the RF24 libraries in your RP2040 based project:

1. Make a copy of the RF24Log library (and optionally RF24Network and RF24Mesh
   libraries) in a "lib" directory located in your project's root directory.

        path/to/my/project/
            lib/
                RF24/
                RF24Log/
                RF24Network/
                RF24Mesh/
            src/
                CMakeLists.txt
                ...

   Alternatively you can add the RF24* repositories as [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules).
2. Include their CMakeLists.txt files from the RF24 libraries in your project's top-level
   CMakeLists.txt file (usually located in the "src" directory). The following snippet
   assumes that your project's "src" directory is on the same level as the previously
   mentioned "lib" directory.
   ```txt
   include(../lib/RF24Log/CMakeLists.txt)
   include(../lib/RF24/CMakeLists.txt)
   include(../lib/RF24Network/CMakeLists.txt)
   include(../lib/RF24Mesh/CMakeLists.txt)
   ```
3. In the same CMakeLists.txt file from step 2, add the RF24 libraries into the
   `target_link_libraries` configuration:
   ```txt
   target_link_libraries(${CMAKE_PROJECT_NAME}
       # ... Your project's other libraries ...
       RF24Log
       RF24
       RF24Network
       RF24Mesh
       )
   ```
   If you are using tinyUSB, this line (or similar) should already exist:
   ```txt
   target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
   ```
4. Finally, remember to include the necessary RF24* libraries' header files in your
   project's source code where applicable.
   ```cpp
   #include <RF24Log.h>
   #include <RF24.h>
   #include <RF24Network.h>
   #include <RF24Mesh.h>
   ```
