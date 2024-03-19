file ( GLOB_RECURSE LANIAKEA_CORE_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "include/*.h")
file ( GLOB_RECURSE LANIAKEA_CORE_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "source/*.cpp")

set (LANIAKEA_CORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
add_library (laniakea-core SHARED ${LANIAKEA_CORE_SOURCE})
target_include_directories (laniakea-core PUBLIC ${LANIAKEA_CORE_INCLUDE_DIR} )
target_link_directories( laniakea-core PUBLIC ${LANIAKEA_3RDPARTY_GLFW_LIB_DIR} )
target_link_libraries( laniakea-core glfw3 )