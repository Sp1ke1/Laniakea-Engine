#include "Laniakea/AssetManager/GLTFLoader.h"
#include "Laniakea/AssetManager/AssetManagerException.h"
namespace lk {
namespace am {

GLTFLoader::GLTFLoader ( const std::string & Path )
{
	LoadFile ( Path );
};

GLTFLoader::~GLTFLoader ()
{
	cgltf_free ( m_Data );
}

cgltf_data * GLTFLoader::GetFileData () const
{
	return m_Data;
}

void GLTFLoader::LoadFile ( const std::string & Path )
{
	cgltf_options Options = {};
	cgltf_result Result = cgltf_parse_file ( &Options, Path.c_str(), &m_Data );
	if ( Result != cgltf_result_success )
	{
		cgltf_free ( m_Data );
		throw AssetManagerException ( "Can't load GLTF file with the given path: " + Path );
	}
	Result = cgltf_load_buffers ( &Options, m_Data, Path.c_str() );
	if ( Result != cgltf_result_success )
	{
		cgltf_free ( m_Data );
		throw AssetManagerException ( "Can't load buffers for GLTF file with the given path: " + Path );
	}
	Result = cgltf_validate ( m_Data );
	if ( Result != cgltf_result_success )
	{
		cgltf_free ( m_Data );
		throw AssetManagerException ( "Can't properly load GLTF file with the given path: " + Path + " GLTF file is invalid" );
	}
}

} // lk
} // gfx