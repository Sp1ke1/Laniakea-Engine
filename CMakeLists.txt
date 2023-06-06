cmake_minimum_required(VERSION 3.23)
project(laniakea)


set(CMAKE_CXX_STANDARD 20)

set(LANIAKEA_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# -------- Compiler flags setup --------
set(COMPILER_RELEASE_FLAGS -O2 -Wno-unknown-pragmas)
set(COMPILER_DEBUG_FLAGS -g -Wall -pedantic -Wno-unknown-pragmas) # TODO: add sanitizer support ( Looks like they don't work under MinGW compiler )

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set (COMPILER_FLAGS ${COMPILER_DEBUG_FLAGS})
endif()
if ( CMAKE_BUILD_TYPE MATCHES Release)
    set (COMPILER_FLAGS ${COMPILER_RELEASE_FLAGS})
endif()
add_compile_options ( ${COMPILER_FLAGS} )

# -------- Include third party libraries -------
find_package (OpenGL REQUIRED)
include_directories (${PROJECT_SOURCE_DIR}/ThirdParty/glfw/include) # glfw include ( opengl, windows, inputs )
include_directories( ${PROJECT_SOURCE_DIR}/ThirdParty/glm/include) # glm include ( math )
include_directories ( ${PROJECT_SOURCE_DIR}/ThirdParty/json/include)
link_directories(${PROJECT_SOURCE_DIR}/ThirdParty/glfw/lib)

# -------- Add executables  --------
set (LANIAKEA_SOURCE_APPLICATION ${LANIAKEA_SOURCE_DIR}/Application/Application.cpp src/Application/Logger.cpp src/Application/Logger.h src/Application/ApplicationConfig.cpp src/Application/ApplicationConfig.h src/Application/InputHandler.cpp src/Application/InputHandler.h)
add_executable(laniakea src/Application/main.cpp ${LANIAKEA_SOURCE_APPLICATION})

# -------- Link target --------
target_link_libraries (laniakea glfw3 opengl32)
