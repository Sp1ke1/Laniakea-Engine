#include "Laniakea/AssetManager/Core.h"
#include "cgltf/cgltf.h"
#include <string>


namespace lk {
namespace am {

class LANIAKEA_ASSET_MANAGER_API GLTFLoader
{
public:
	GLTFLoader ( const std::string & Path );
	~GLTFLoader();
	cgltf_data * GetFileData () const;

	GLTFLoader ( const GLTFLoader & ) = delete;
	GLTFLoader & operator = ( GLTFLoader & ) = delete;

private:
	void LoadFile ( const std::string & Path );

private:
	cgltf_data * m_Data = nullptr;
};

} // lk
} // am