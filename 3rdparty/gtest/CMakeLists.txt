set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(gtest)

message ( STATUS "Copying GTEST from: ${CMAKE_BINARY_DIR}/bin/libgtest.dll" )
message ( STATUS "Copying GTEST to: ${LANIAKEA_OUTPUT_DIRECTORY}")
# Attempt to copy the gtest DLL
add_custom_target(copy_gtest_dll ALL
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/bin/libgtest.dll
        ${LANIAKEA_OUTPUT_DIRECTORY}
        )


add_dependencies(copy_gtest_dll gtest)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
