cmake_minimum_required(VERSION 3.23)
project(laniakea)

set(CMAKE_CXX_STANDARD 17)

find_package (OpenGL REQUIRED)

include_directories (${PROJECT_SOURCE_DIR}/ThirdParty/glfw/include/) # glfw include ( opengl, windows, inputs )
include_directories( ${PROJECT_SOURCE_DIR}/ThirdParty/glm/include/) # glm include ( math )

link_directories(${PROJECT_SOURCE_DIR}/ThirdParty/glfw/lib/)

add_executable(laniakea src/main.cpp)

target_link_libraries (laniakea glfw3 opengl32)
