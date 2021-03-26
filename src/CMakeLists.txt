cmake_minimum_required (VERSION 3.8)

# set the project name and set version
project ("RF24Log"
         VERSION 0.1.0)

add_library(RF24Log RF24Log.h)

set_target_properties(RF24Log PROPERTIES LINKER_LANGUAGE CXX)

# add directory to binary tree for searching includes
target_include_directories(RF24Log PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# assemble the config file with variables from CMake
configure_file(RF24Log_config.h RF24Log_config.h)
