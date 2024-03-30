set ( CGLTF_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/cgltf.cpp )
set ( CGLTF_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include )


add_library ( cgltf SHARED ${CGLTF_SOURCE} )
target_include_directories( cgltf PUBLIC ${CGLTF_INCLUDE} )

# Create a custom target for copying the DLL
add_custom_target(copy_cgltf_dll ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:cgltf>
        ${LANIAKEA_OUTPUT_DIRECTORY}
        )

# Ensure the custom target is built after the gtest target
add_dependencies(copy_cgltf_dll cgltf)