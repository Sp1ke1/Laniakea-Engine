cmake_minimum_required(VERSION 3.23)
project ( glad )
set (CMAKE_CXX_STANDARD 20)

add_library ( glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c )

target_include_directories( glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries ( glad )