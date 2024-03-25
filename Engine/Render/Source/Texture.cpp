#include "Laniakea/Render/Texture.h"
#include "Laniakea/Render/RenderException.h"
#include "glad/glad.h"
#include "stb/stb_image.h"


namespace lk
{
namespace gfx
{

Texture::Texture ( const std::string & Path )
: m_Width ( 0 ), m_Height ( 0 ), m_Channels ( 0 ), m_Handle ( 0 ) {
	glGenTextures ( 1, &m_Handle );
	Load ( Path );
}

Texture::~Texture ()
{
	glDeleteTextures ( 1, &m_Handle );
}

unsigned int Texture::GetHandle () const
{
	return m_Handle;
}

void Texture::Load ( const std::string & Path )
{
	int Width, Height, NOfChannels;
	unsigned char * TextureData = stbi_load(Path.c_str(), &Width, &Height, &NOfChannels, 0);

	if (!TextureData)
	{
		stbi_image_free(TextureData);
		throw RenderException ( "Can't load texture from given path: " + Path );
	}
	glBindTexture ( GL_TEXTURE_2D, m_Handle );

	GLenum TextureFormat = GL_RGB;
	if (NOfChannels == 1)
		TextureFormat = GL_RED;
	else if (NOfChannels == 3)
		TextureFormat = GL_RGB;
	else if (NOfChannels == 4)
		TextureFormat = GL_RGBA;

	// Load texture data and generate mipmaps;
	glTexImage2D(GL_TEXTURE_2D, 0, TextureFormat, Width, Height, 0, TextureFormat, GL_UNSIGNED_BYTE, TextureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set parameters of borders wrapping and magnification / minification ( SuperSampling )
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(TextureData);
	LK_RENDER_CHECK_ERROR()
}

	void Texture::Set ( unsigned int UniformIndex, unsigned int TextureIndex )
	{
		glActiveTexture ( GL_TEXTURE0 + TextureIndex );
		glBindTexture ( GL_TEXTURE_2D, m_Handle );
		glUniform1i ( UniformIndex, TextureIndex );
		LK_RENDER_CHECK_ERROR()
	}

	void Texture::Unset ( unsigned int TextureIndex )
	{
		glActiveTexture ( GL_TEXTURE0 + TextureIndex );
		glBindTexture ( GL_TEXTURE_2D, 0 );
		glActiveTexture ( GL_TEXTURE0 );
		LK_RENDER_CHECK_ERROR()
	}
} // lk
} // gfx