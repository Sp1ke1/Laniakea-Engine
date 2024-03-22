cmake_minimum_required(VERSION 3.23)
project( Sample )

set ( SAMPLE_PROJECT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/Source/Sample.cpp)


add_executable( Sample ${SAMPLE_PROJECT_SOURCE} )
target_compile_options ( Sample PRIVATE ${LANIAKEA_CXX_FLAGS} )
target_compile_definitions( Sample PRIVATE ${LANIAKEA_DEFINITIONS} )
target_link_libraries ( Sample PRIVATE Laniakea-Core Laniakea-Render Laniakea-ECS )

add_custom_target(copy-sample ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Sample>
        ${LANIAKEA_OUTPUT_DIRECTORY}
        )

add_dependencies(copy-sample Sample)