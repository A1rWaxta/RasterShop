cmake_minimum_required(VERSION 3.13)
project(RasterShop)

set(CMAKE_CXX_STANDARD 17)

set(GOOGLE_TEST_INCLUDE_DIR "lib/googletest/googletest/include")
set(GOOGLE_MOCK_INCLUDE_DIR "lib/googletest/googlemock/include")

message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "Compiling for ${CMAKE_SYSTEM_NAME} system")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message(STATUS "Compiling using Clang (LLVM) compiler")
	set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DRELEASE")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fstandalone-debug -DDEBUG")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions(-DSYSTEM_LINUX)
endif()

#add_subdirectory(tests)

add_subdirectory(src)
add_subdirectory(tests)