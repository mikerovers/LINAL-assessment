cmake_minimum_required(VERSION 3.12)
project(LINAL-assessment)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER_INIT gcc)

enable_testing()
add_subdirectory(tests)

set(PROJECT_SOURCES main.cpp src/Vector.cpp src/Vector.h)

message( "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}" )
if ( "${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG" )
    add_definitions(-D_DEBUG)
endif()

add_subdirectory(external/SFML)

add_executable(LINAL-assessment ${PROJECT_SOURCES})
add_library(LINAL-library ${PROJECT_SOURCES})
target_link_libraries(LINAL-assessment sfml-graphics sfml-window)