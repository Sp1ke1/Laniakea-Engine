set ( GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c )
set ( GLAD_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include )


add_library ( glad SHARED ${GLAD_SOURCE} )
target_include_directories( glad PUBLIC ${GLAD_INCLUDE} )

# Create a custom target for copying the DLL
add_custom_target(copy_glad_dll ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glad>
        ${LANIAKEA_OUTPUT_DIRECTORY}
        )

# Ensure the custom target is built after the gtest target
add_dependencies(copy_glad_dll glad)