cmake_minimum_required(VERSION 3.0.0)

# add the source code subdiectory
add_subdirectory(src)

# set project name and version number
project(RF24Log VERSION 0.1.0)

# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
