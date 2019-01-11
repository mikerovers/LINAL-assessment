cmake_minimum_required(VERSION 3.12)
project(LINAL-assessment)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER_INIT gcc)

enable_testing()
add_subdirectory(tests)

set(PROJECT_SOURCES main.cpp src/Vector2D.cpp src/Vector2D.h src/Matrix.cpp src/Matrix.h src/MyMesh.cpp src/MyMesh.h src/obj/objload.h src/Vector3D.cpp src/Vector3D.h src/CustomView.cpp src/CustomView.h)

message( "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}" )
if ( "${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG" )
    add_definitions(-D_DEBUG)
endif()

add_subdirectory(external/SFML)

add_executable(LINAL-assessment ${PROJECT_SOURCES} src/PulseController.cpp src/PulseController.h)
add_library(LINAL-library ${PROJECT_SOURCES})
target_link_libraries(LINAL-assessment sfml-graphics sfml-window)
target_link_libraries(LINAL-library sfml-graphics sfml-window)