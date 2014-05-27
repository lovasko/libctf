cmake_minimum_required(VERSION 2.8)

project (test)
set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE LIBCTF_SOURCES "src/*.c")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_library(ctf SHARED ${LIBCTF_SOURCES})

