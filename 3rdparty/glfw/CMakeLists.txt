set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

add_subdirectory(glfw)

message(STATUS "Copying GLFW to: ${LANIAKEA_OUTPUT_DIRECTORY}")
# Create a custom target for copying the DLL
add_custom_target(copy_glfw_dll ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glfw>
        ${LANIAKEA_OUTPUT_DIRECTORY}
        )

# Ensure the custom target is built after the gtest target
add_dependencies(copy_glfw_dll glfw)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
