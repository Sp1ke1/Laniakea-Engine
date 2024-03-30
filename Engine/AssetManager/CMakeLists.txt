file ( GLOB_RECURSE LANIAKEA_ASSETMANAGER_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Include/*.h")
file ( GLOB_RECURSE LANIAKEA_ASSETMANAGER_SOURCE RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "Source/*.cpp")

# laniakea-render library
set (LANIAKEA_ASSETMANAGER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include/" )
add_library (Laniakea-AssetManager SHARED ${LANIAKEA_ASSETMANAGER_SOURCE})
target_include_directories( Laniakea-AssetManager PUBLIC ${LANIAKEA_ASSETMANAGER_INCLUDE_DIR} )
target_link_libraries ( Laniakea-AssetManager cgltf )

# tests
add_executable( Test-AssetManager ${CMAKE_CURRENT_SOURCE_DIR}/Test/Test_AssetManager.cpp)
target_compile_definitions ( Test-AssetManager PRIVATE ${LANIAKEA_DEFINITIONS} )
target_compile_options( Test-AssetManager PRIVATE ${LANIAKEA_CXX_FLAGS} )
target_link_libraries (Test-AssetManager PRIVATE gtest Laniakea-AssetManager )

enable_testing()
add_test ( "Asset Manager test" Test-AssetManager )