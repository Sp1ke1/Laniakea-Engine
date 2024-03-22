cmake_minimum_required(VERSION 3.23)
project(laniakea)


set (CMAKE_CXX_STANDARD 20)

# Declare compiler options and definitions
set (LANIAKEA_DEFINITIONS)
set (LANIAKEA_CXX_FLAGS)

# 3RD party
set (LANIAKEA_3RDPARTY_INCLUDE)
set (LANIAKEA_3RDPARTY_LIBS)

# Setup build output directory. TODO: consider more sofisticated way
set ( LANIAKEA_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Sample/Build/${CMAKE_BUILD_TYPE} CACHE INTERNAL "")
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LANIAKEA_OUTPUT_DIRECTORY} )

# Compiler options setup
if (CMAKE_BUILD_TYPE MATCHES Debug)
    list (APPEND LANIAKEA_CXX_FLAGS -Wall -Werror -Wextra -pedantic -g -Wno-unknown-pragmas -Wno-volatile)
endif()

if (CMAKE_BUILD_TYPE MATCHES Release )
    list (APPEND LANIAKEA_CXX_FLAGS -O2 -Wno-unknown-pragmas -Wno-volatile )
endif()

# Prepocessor definitions setup

if ( CMAKE_BUILD_TYPE MATCHES Debug )
    list ( APPEND LANIAKEA_DEFINITIONS "-DLANIAKEA_BUILD_DEBUG=1" )
endif()
if ( CMAKE_BUILD_TYPE MATCHES Release )
    list ( APPEND LANIAKEA_DEFINITIONS "-DLANIAKEA_BUILD_RELEASE=1" )
endif()

IF ( WIN32 )
    list ( APPEND LANIAKEA_DEFINITIONS "-DLANIAKEA_PLATFORM_WINDOWS=1" )
ENDIF ()

add_subdirectory(3rdparty)
include_directories( ${LANIAKEA_3RDPARTY_INCLUDE} )

add_subdirectory(Engine)
add_subdirectory(Sample)







