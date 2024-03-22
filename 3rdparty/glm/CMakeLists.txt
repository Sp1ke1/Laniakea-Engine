set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

add_subdirectory(glm)

# Create a custom target for copying the DLL
add_custom_target(copy_glm_dll ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glm>
        ${LANIAKEA_OUTPUT_DIRECTORY}
        )

# Ensure the custom target is built after the gtest target
add_dependencies(copy_glm_dll glm)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
