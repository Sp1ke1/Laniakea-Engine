cmake_minimum_required(VERSION 3.23)
project( SampleProject )

set(CMAKE_CXX_STANDARD 20)

set(SAMPLE_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set (SAMPLE_PROJECT_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

set (LANIAKEA_INCLUDE_DIR ${PROJECT_ROOT_DIR}/Laniakea/ThirdParty ${PROJECT_ROOT_DIR}/Laniakea/src )

# -------- Release/Debug compiler flags --------
set(COMPILER_RELEASE_FLAGS -O2 -Wno-unknown-pragmas)
set(COMPILER_DEBUG_FLAGS -g -Wall -Wextra -pedantic -Wno-unknown-pragmas) # TODO: add sanitizer support ( Looks like they don't work under MinGW compiler )
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set (COMPILER_FLAGS ${COMPILER_DEBUG_FLAGS})
endif()
if ( CMAKE_BUILD_TYPE MATCHES Release)
    set (COMPILER_FLAGS ${COMPILER_RELEASE_FLAGS})
endif()
add_compile_options ( ${COMPILER_FLAGS} )


# -------- Release/Debug binary directory --------
if ( CMAKE_BUILD_TYPE MATCHES Debug )
    set ( SAMPLE_PROJECT_BUILD_DIR ${SAMPLE_PROJECT_BUILD_DIR}/Debug )
endif()
if ( CMAKE_BUILD_TYPE MATCHES Release )
    set ( SAMPLE_PROJECT_BUILD_DIR ${SAMPLE_PROJECT_BUILD_DIR}/Release )
endif()
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SAMPLE_PROJECT_BUILD_DIR})

# -------- Platform definitions --------
IF ( WIN32 )
    add_compile_definitions( LANIAKEA_PLATFORM_WINDOWS )
ENDIF ()



# -------- Code processing --------
include_directories( ${LANIAKEA_INCLUDE_DIR} )
set ( SAMPLE_PROJECT_SOURCE ${SAMPLE_PROJECT_SOURCE_DIR}/SampleProject.cpp )
add_executable( SampleProject ${SAMPLE_PROJECT_SOURCE} )
target_link_libraries ( SampleProject ${SAMPLE_PROJECT_BUILD_DIR}/libLaniakeaEngine.dll )
