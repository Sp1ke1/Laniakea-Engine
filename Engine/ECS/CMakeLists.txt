file ( GLOB_RECURSE LANIAKEA_ECS_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Include/*.h")
file ( GLOB_RECURSE LANIAKEA_ECS_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Source/*.cpp")


set (LANIAKEA_ECS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include/")
add_library (Laniakea-ECS SHARED ${LANIAKEA_ECS_SOURCE} )
target_include_directories (Laniakea-ECS PUBLIC ${LANIAKEA_ECS_INCLUDE_DIR} )

add_executable( Test-ECS ${CMAKE_CURRENT_SOURCE_DIR}/Test/test_ecs.cpp)
target_link_libraries (Test-ECS PRIVATE gtest Laniakea-ECS )
target_compile_options ( Test-ECS PRIVATE ${LANIAKEA_CXX_FLAGS} )
target_compile_definitions( Test-ECS PRIVATE ${LANIAKEA_DEFINITIONS} )
enable_testing()
add_test ( "Entity-Component-System test" Test-ECS )