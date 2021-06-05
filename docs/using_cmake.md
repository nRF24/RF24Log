# Using CMake
A more modern approach instead of using hand-crafted _Makefiles_ & _configure_ scripts
to build & install software.

## Installing the library

### Using a package manager
The RF24Log library has pre-built packages (*.deb or *.rpm files) that can be installed on a
Raspberry Pi. These packages can be found on the library's
[GitHub release page](https://GitHub.com/nRF24/RF24Log/releases)

@warning If you have previously installed the library from source code, then you will need
to uninstall it manually to avoid runtime conflicts.
```shell
sudo rm /usr/local/lib/librf24log.*
sudo rm -r /usr/local/include/RF24Log
```

1. Download the appropriate package for your machine

   Go to the library's [GitHub release page](https://GitHub.com/nRF24/RF24Log/releases), and look for
   the latest release's assets.

   For all Raspberry Pi variants using the Raspberry Pi OS (aka Raspbian), you need the file marked
   for _armhf_ architecture.

   For Raspberry Pi 4 variants using a 64-bit OS (like Ubuntu), you need the file marked for
   _arm64_ architecture.

2. Install the downloaded pkg

   If you downloaded the file directly from your target machine using the desktop environment, then
   you only need to double-click the package (deb or rpm) file, and the OS should do the rest. <br>

   If you downloaded the file remotely and want to copy it over ssh, then use the `scp` command in a terminal.
   ```shell
   scp pkg_filename.deb pi@host_name:~/Downloads
   ```

   @note You do not need to do this from within an ssh session. Also, you can use the target machine's IP
   address instead of its host name.<br>

   The `scp` command will ask you for a password belonging to the user's name on the remote machine (we used
   `pi` in the above example).<br>
   Now you can open up a ssh session and install the copied package from the terminal.
   ```shell
   ssh pi@host_name
   cd Downloads
   dpkg -i pkg_filename.deb
   ```

### Building from source code
1. CMake may need to be installed
   ```shell
   sudo apt-get install cmake
   ```
2. Make a directory to contain the RF24Log lib and enter it
   ```shell
   mkdir ~/rf24libs
   cd ~/rf24libs
   ```
3. Clone the [RF24Log repo](https://github.com/nRF24/RF24Log) and navigate to it
   ```shell
   git clone https://github.com/nRF24/RF24Log.git RF24Log
   cd RF24Log
   ```
4. Create a build directory inside the RF24Log directory and navigate to it.
   ```shell
   mkdir build
   cd build
   ```
5. Configure build environment
   ```shell
   cmake ../src
   ```
6. Build and install the library
   ```shell
   make
   sudo make install
   ```
7. Build the examples

   Navigate to the _examples_ directory
   ```shell
   cd ../examples
   ```
   Create a build directory in the examples_linux directory and navigate to it.
   ```shell
   mkdir build
   cd build
   ```
   Now you are ready to build the examples.
   ```shell
   cmake ..
   make
   ```
8. Run an example file
   ```shell
   sudo ./Gettingstarted
   ```

## Cross-compiling the library
The RF24Log library comes with some pre-made toolchain files (located in the _RF24/cmake/toolchains_
directory) to use in CMake. To use these toolchain files, additional command line options are needed
when configuring CMake to build the library (step 5 in the above instructions to build from source).
```shell
cmake ../src -D CMAKE_TOOLCHAIN_FILE=cmake/toolchains/armhf.cmake
make
```
If you plan on using the cross-compiled library with your personal cross-compiled project, then
it is advised to specify the path that your project will look in when linking to the RF24Log library:
```shell
cmake ../src -D CMAKE_INSTALL_PREFIX=/usr/arm-linux-gnueabihf -D CMAKE_TOOLCHAIN_FILE=cmake/toolchains/armhf.cmake
make
sudo make install
```

### Installing the library remotely
To install remotely, you can create an installable package file using CMake's built-in program called CPack.
```shell
cmake ../src -D CMAKE_TOOLCHAIN_FILE=cmake/toolchains/armhf.cmake
make
cpack
```
This will create a deb file and a rpm file that you can use to install to your target machine (see the
above instructions about using a package manager).
