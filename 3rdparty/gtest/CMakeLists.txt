set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(gtest)

set ( INSTALL_GTEST OFF CACHE BOOL "" FORCE )

# For some reason gtest doesn't want to copy using add_custom_target with custom command as others.
set_target_properties(gtest PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${LANIAKEA_OUTPUT_DIRECTORY}
        )

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
