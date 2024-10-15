cmake_minimum_required(VERSION 3.26)
project(djinn CXX)
include(FetchContent)

find_package(SDL3 REQUIRED)
find_package(spdlog REQUIRED)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wall -g -O0")
set(INCLUDE_DIR include)
set(SRC_DIR src)

file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp)
add_executable(djinn ${SOURCE_FILES})
target_include_directories(djinn PRIVATE ${INCLUDE_DIR})
target_link_libraries(djinn PRIVATE SDL3::SDL3 spdlog::spdlog)

add_custom_target(distclean
    COMMAND ${CMAKE_COMMAND} -E rm -rf 
        ${CMAKE_BINARY_DIR}/djinn
        ${CMAKE_BINARY_DIR}/_deps
        ${CMAKE_BINARY_DIR}/CMakeCache.txt
        ${CMAKE_BINARY_DIR}/CMakeFiles
        ${CMAKE_BINARY_DIR}/Makefile
        ${CMAKE_BINARY_DIR}/cmake_install.cmake
        ${CMAKE_BINARY_DIR}/bin
        COMMENT "Performing a thorough cleanup of build and output files")
