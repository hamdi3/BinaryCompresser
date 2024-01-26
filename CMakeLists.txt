cmake_minimum_required(VERSION 3.10)
project(BinaryCompresser)

set(CMAKE_CXX_STANDARD 14)

# Find the zlib library
find_package(ZLIB REQUIRED)

add_executable(BinaryCompresser main.cpp utils/compresser.cpp)

# Link the zlib library to your executable
target_link_libraries(BinaryCompresser ${ZLIB_LIBRARIES})
