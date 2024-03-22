file ( GLOB_RECURSE LANIAKEA_CORE_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Include/*.h")
file ( GLOB_RECURSE LANIAKEA_CORE_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Source/*.cpp")

set (LANIAKEA_CORE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include/")
add_library (Laniakea-Core SHARED ${LANIAKEA_CORE_SOURCE})
target_include_directories (Laniakea-Core PUBLIC ${LANIAKEA_CORE_INCLUDE_DIR} )
target_link_libraries( Laniakea-Core glfw glm )