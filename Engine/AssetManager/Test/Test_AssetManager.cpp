#include "gtest/gtest.h"
#include "Laniakea/AssetManager/GLTFLoader.h"
#include "Laniakea/AssetManager/AssetManagerException.h"



TEST ( GLTFLoader, FileLoad )
{
	using namespace lk::am;
	std::string ModelPath ( "Models/Box.gltf");
	std::string WrongPath ( "Models/Box12345.gltf");

	EXPECT_THROW ( GLTFLoader l1 ( WrongPath ), AssetManagerException  );
	EXPECT_NO_THROW ( GLTFLoader l2 ( ModelPath ) );
	GLTFLoader l3 ( ModelPath );
	EXPECT_TRUE ( l3 . GetFileData() != nullptr );
}


int main ( int argc, char ** argv )
{
	testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}