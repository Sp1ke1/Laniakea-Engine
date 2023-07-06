cmake_minimum_required(VERSION 3.23)
project( Laniakea )



set ( PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

# Set up engine dll directory
set ( PROJECT_DIRECTORY ${PROJECT_ROOT_DIR}/SampleProject ) # Root dir of client project
set ( LANIAKEA_RELEASE_OUTPUT_DIRECTORY ${PROJECT_DIRECTORY}/build/Release )
set ( LANIAKEA_DEBUG_OUTPUT_DIRECTORY ${PROJECT_DIRECTORY}/build/Debug )

add_subdirectory( Laniakea )
add_subdirectory( SampleProject )




