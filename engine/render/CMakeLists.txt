file ( GLOB_RECURSE LANIAKEA_RENDER_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "include/*.hpp")
file ( GLOB_RECURSE LANIAKEA_RENDER_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "source/*.cpp")


find_package ( OpenGL REQUIRED )

# laniakea-render library
set (LANIAKEA_RENDER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/" )
add_library (laniakea-render SHARED ${LANIAKEA_RENDER_SOURCE})
target_include_directories( laniakea-render PUBLIC ${LANIAKEA_RENDER_INCLUDE_DIR} )
target_link_libraries ( laniakea-render laniakea-core glad )

# tests
add_executable( test-render ${CMAKE_CURRENT_SOURCE_DIR}/test/test_render.cpp)
target_link_libraries (test-render gtest laniakea-render)
enable_testing()
add_test ( "Renderer test" test-render )