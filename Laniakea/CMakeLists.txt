cmake_minimum_required(VERSION 3.23)
project( LaniakeaEngine )


set(CMAKE_CXX_STANDARD 20)

set(LANIAKEA_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(LANIAKEA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)


# -------- Compiler flags setup --------
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
    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LANIAKEA_RELEASE_OUTPUT_DIRECTORY} )
endif()
if ( CMAKE_BUILD_TYPE MATCHES Release )
    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${LANIAKEA_RELEASE_OUTPUT_DIRECTORY} )
endif()


# -------- Include third party libraries -------
find_package (OpenGL REQUIRED)
include_directories ( ${LANIAKEA_INCLUDE_DIR})
link_directories(ThirdParty/glfw/lib)
# ------- Include Laniakea dirs --------
include_directories ( ${LANIAKEA_SOURCE_DIR} )


# -------- Platform definitions --------

IF ( WIN32 )
    add_compile_definitions( LANIAKEA_PLATFORM_WINDOWS )
ENDIF ()
add_compile_definitions( LANIAKEA_BUILD_DLL )

# -------- Add executables  --------
set (LANIAKEA_SOURCE_APPLICATION ${LANIAKEA_SOURCE_DIR}/Application/Application.cpp ${LANIAKEA_SOURCE_DIR}/Application/Logger.cpp ${LANIAKEA_SOURCE_DIR}/Application/Logger.h ${LANIAKEA_SOURCE_DIR}/Application/ApplicationConfig.cpp ${LANIAKEA_SOURCE_DIR}/Application/ApplicationConfig.h ${LANIAKEA_SOURCE_DIR}/Application/Input.cpp ${LANIAKEA_SOURCE_DIR}/Application/Input.h ${LANIAKEA_SOURCE_DIR}/Application/Core.h src/Laniakea/Laniakea.h src/Application/EntryPoint.h)
add_library(LaniakeaEngine SHARED ${LANIAKEA_SOURCE_APPLICATION})

# -------- Link target --------
target_link_libraries (LaniakeaEngine glfw3 opengl32)
