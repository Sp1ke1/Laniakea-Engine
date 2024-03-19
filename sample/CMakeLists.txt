cmake_minimum_required(VERSION 3.23)
project( sample )

set ( SAMPLE_PROJECT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/sample.cpp)
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE} )
add_executable( sample ${SAMPLE_PROJECT_SOURCE} )


target_link_libraries ( sample laniakea-core laniakea-render )
