#include "Laniakea/Render/Core.h"
#include <string>

namespace lk
{
namespace gfx
{

class LANIAKEA_RENDER_API Texture
{
public:
	Texture ( const std::string & Path );
	~Texture ();

	unsigned int GetHandle () const;

	Texture ( const Texture & ) = delete;
	Texture & operator = ( const Texture & ) = delete;

	void Set ( unsigned int UniformIndex, unsigned int TextureIndex );
	void Unset ( unsigned int TextureIndex );

private:
	void Load ( const std::string & Path );

	unsigned int m_Width;
	unsigned int m_Height;
	unsigned int m_Channels;
	unsigned int m_Handle;
};

} // lk
} // gfx
