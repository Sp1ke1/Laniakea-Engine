#pragma once
#include "Laniakea/Render/Core.h"
#include <string>
#include <exception>


void _CheckGlError ( const char * file, int line );

#ifdef LANIAKEA_BUILD_DEBUG
	#define LK_RENDER_CHECK_ERROR() _CheckGlError ( __FILE__, __LINE__ );
#else
	#define LK_RENDER_CHECK_ERROR()
#endif
namespace lk
{
namespace gfx
{
class LANIAKEA_RENDER_API RenderException : public std::exception
{
	public:
		RenderException ( const std::string & msg );

		RenderException ( std::string && msg );

		const char * what() const noexcept override;
	private:
		std::string m_Msg;
};

} // lk
} // gfx

