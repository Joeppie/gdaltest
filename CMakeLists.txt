cmake_minimum_required(VERSION 3.8)
project(gdal_test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(gdal_test ${SOURCE_FILES})
find_package( GDAL )
target_link_libraries( gdal_test gdal )

SET(GDAL_INCLUDE_DIR "/usr/include/gdal")
include_directories( ${GDAL_INCLUDE_DIR} )