set ( STB_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/stb/src/stb_image.cpp )
set ( STB_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/stb/include/ )


add_library ( stb SHARED ${STB_SOURCE} )
target_include_directories( stb PUBLIC ${STB_INCLUDE} )

# Create a custom target for copying the DLL
add_custom_target(copy_stb_dll ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:stb>
        ${LANIAKEA_OUTPUT_DIRECTORY}
        )

# Ensure the custom target is built after the gtest target
add_dependencies(copy_stb_dll stb)