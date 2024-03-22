file(GLOB LANIAKEA_LIB_DIRS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*")
list(REMOVE_ITEM LANIAKEA_LIB_DIRS "CMakeLists.txt")
set (LANIAKEA_LIBRARIES)

foreach(lib ${LANIAKEA_LIB_DIRS})
    add_subdirectory(${lib})
    target_compile_definitions(Laniakea-${lib} PRIVATE ${LANIAKEA_DEFINITIONS} -DLANIAKEA_BUILD_DLL=1 )
    target_compile_options(Laniakea-${lib} PRIVATE ${LANIAKEA_CXX_FLAGS})

    add_custom_target(copy-laniakea-${lib}-dll ALL
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Laniakea-${lib}>
            ${LANIAKEA_OUTPUT_DIRECTORY}
            )

    add_dependencies(copy-laniakea-${lib}-dll Laniakea-${lib})

    list(APPEND LANIAKEA_LIBRARIES Laniakea-${lib})
endforeach()