file ( GLOB_RECURSE LANIAKEA_ECS_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "include/*.h")
file ( GLOB_RECURSE LANIAKEA_ECS_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "source/*.cpp")


set (LANIAKEA_ECS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
add_library (laniakea-ecs SHARED ${LANIAKEA_ECS_SOURCE} )
target_include_directories (laniakea-ecs PUBLIC ${LANIAKEA_ECS_INCLUDE_DIR} )

add_executable( test-ecs ${CMAKE_CURRENT_SOURCE_DIR}/test/test_ecs.cpp )
target_link_libraries (test-ecs gtest laniakea-ecs )
enable_testing()
add_test ( "Entity-Component-System test" test-ecs )