cmake_minimum_required(VERSION 3.23)
project( LaniakeaEngine )


set(CMAKE_CXX_STANDARD 20)

set(LANIAKEA_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(LANIAKEA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/ThirdParty ${LANIAKEA_SOURCE_DIR})


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
    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LANIAKEA_DEBUG_OUTPUT_DIRECTORY} )
endif()
if ( CMAKE_BUILD_TYPE MATCHES Release )
    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${LANIAKEA_RELEASE_OUTPUT_DIRECTORY} )
endif()




# -------- Set up includes -------
include_directories ( ${LANIAKEA_INCLUDE_DIR} )

# -------- Set up third party libraries -------
find_package (OpenGL REQUIRED)
link_directories(ThirdParty/glfw/lib)



# -------- Preprocessor directives --------
if ( CMAKE_BUILD_TYPE MATCHES Debug )
    add_compile_definitions( LANIAKEA_BUILD_DEBUG )
endif()
if ( CMAKE_BUILD_TYPE MATCHES Release )
    add_compile_definitions( LANIAKEA_BUILD_RELEASE )
endif()

IF ( WIN32 )
    add_compile_definitions( LANIAKEA_PLATFORM_WINDOWS )
ENDIF ()
add_compile_definitions( LANIAKEA_BUILD_DLL )

# -------- Add executables  --------
set (LANIAKEA_SOURCE_APPLICATION ${LANIAKEA_SOURCE_DIR}/Application/Application.h ${LANIAKEA_SOURCE_DIR}/Application/Application.cpp
                                 ${LANIAKEA_SOURCE_DIR}/Application/KeyCodes.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/Logger.cpp ${LANIAKEA_SOURCE_DIR}/Application/Logger.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/ApplicationConfig.cpp ${LANIAKEA_SOURCE_DIR}/Application/ApplicationConfig.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/Input.cpp ${LANIAKEA_SOURCE_DIR}/Application/Input.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/Core.h
                                 ${LANIAKEA_SOURCE_DIR}/Laniakea/Laniakea.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/EntryPoint.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/Events/Event.cpp ${LANIAKEA_SOURCE_DIR}/Application/Events/Event.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/Events/EventDispatcher.cpp src/Application/Events/EventDispatcher.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/Events/ApplicationEvent.h ${LANIAKEA_SOURCE_DIR}/Application/Events/KeyEvent.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/Events/MouseEvent.h ${LANIAKEA_SOURCE_DIR}/Application/MouseCodes.h
                                 ${LANIAKEA_SOURCE_DIR}/Application/Window.h ${LANIAKEA_SOURCE_DIR}/Application/Window.cpp)
add_library(LaniakeaEngine SHARED ${LANIAKEA_SOURCE_APPLICATION})

# -------- Link target --------
target_link_libraries (LaniakeaEngine glfw3 opengl32)
