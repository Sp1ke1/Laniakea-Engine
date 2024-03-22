file ( GLOB_RECURSE LANIAKEA_RENDER_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Include/*.hpp")
file ( GLOB_RECURSE LANIAKEA_RENDER_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Source/*.cpp")

# laniakea-render library
set (LANIAKEA_RENDER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include/" )
add_library (Laniakea-Render SHARED ${CMAKE_CURRENT_SOURCE_DIR}/Source/Shader.cpp)
target_include_directories( Laniakea-Render PUBLIC ${LANIAKEA_RENDER_INCLUDE_DIR} )
target_link_libraries ( Laniakea-Render Laniakea-Core glad )

# tests
add_executable( Test-Render ${CMAKE_CURRENT_SOURCE_DIR}/Test/Test_Render.cpp)
target_compile_definitions ( Test-Render PRIVATE ${LANIAKEA_DEFINITIONS} )
target_compile_options( Test-Render PRIVATE ${LANIAKEA_CXX_FLAGS} )
target_link_libraries (Test-Render PRIVATE gtest Laniakea-Render )

enable_testing()
add_test ( "Renderer test" Test-Render )