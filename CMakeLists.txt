cmake_minimum_required(VERSION 3.23)
project(laniakea)


set(CMAKE_CXX_STANDARD 17)

set(COMPILER_RELEASE_FLAGS -O2)
set(COMPILER_DEBUG_FLAGS -g -Wall -pedantic) # TODO: add sanitizer support ( Looks like they don't work under MinGW compiler ) 

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set (COMPILER_FLAGS ${COMPILER_DEBUG_FLAGS})
endif()
if ( CMAKE_BUILD_TYPE MATCHES Release)
    set (COMPILER_FLAGS ${COMPILER_RELEASE_FLAGS})
endif()

add_compile_options ( ${COMPILER_FLAGS} )

find_package (OpenGL REQUIRED)

include_directories (${PROJECT_SOURCE_DIR}/ThirdParty/glfw/include/) # glfw include ( opengl, windows, inputs )
include_directories( ${PROJECT_SOURCE_DIR}/ThirdParty/glm/include/) # glm include ( math )

link_directories(${PROJECT_SOURCE_DIR}/ThirdParty/glfw/lib/)

add_executable(laniakea src/main.cpp)

target_link_libraries (laniakea glfw3 opengl32)
