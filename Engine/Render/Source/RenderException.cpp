#include "glad/glad.h"
#include "Laniakea/Render/RenderException.h"

void _CheckGlError ( const char * file, int line )
{
	GLenum ErrorCode;
	ErrorCode = glGetError();
	if ( ErrorCode == GL_NO_ERROR )
		return;
	std::string GLErrorMessage;
	std::string FileLine = std::string ( file ) + std::to_string ( line );
	switch (ErrorCode)
	{
		case GL_INVALID_ENUM:                  GLErrorMessage = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 GLErrorMessage = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             GLErrorMessage = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                GLErrorMessage = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               GLErrorMessage = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 GLErrorMessage = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: GLErrorMessage = "INVALID_FRAMEBUFFER_OPERATION"; break;
	}
	throw lk::gfx::RenderException ( "Render error in: " + FileLine + "GL error: " + GLErrorMessage  );
}

namespace lk
{
namespace gfx

{

RenderException::RenderException ( std::string && msg )
: m_Msg ( std::move ( msg ) )
{

}

RenderException::RenderException ( const std::string & msg )
: m_Msg( msg )
{
}

const char * RenderException::what () const noexcept
{
	return m_Msg.c_str();
}

} // lk
} // gfx