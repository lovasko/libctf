cmake_minimum_required(VERSION 2.8)

project (ctf)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE LIBCTF_SOURCES "src/*.c")
add_library(ctf SHARED ${LIBCTF_SOURCES})

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
	include_directories(${ZLIB_INCLUDE_DIRS} )
	target_link_libraries(ctf ${ZLIB_LIBRARIES} )
endif(ZLIB_FOUND)

find_package(LIBELF REQUIRED)
if (LIBELF_FOUND)
	include_directories(${LIBELF_INCLUDE_DIRS} )
	target_link_libraries(ctf ${LIBELF_LIBRARIES} )
endif(LIBELF_FOUND)

