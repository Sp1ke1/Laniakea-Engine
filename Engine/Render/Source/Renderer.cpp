#include "Laniakea/Render/Renderer.h"
#include "Laniakea/Render/IndexBuffer.h"
#include "Laniakea/Render/RenderException.h"
#include "glad/glad.h"

namespace lk
{
namespace gfx
{

	void Renderer::Render ( unsigned int VertexCount, DrawMode DrawMode )
	{
		glDrawArrays ( GetGLDrawModeFromDrawMode ( DrawMode ), 0, VertexCount );
		LK_RENDER_CHECK_ERROR()
	}

	void Renderer::Render ( IndexBuffer & IndexBuffer, DrawMode DrawMode )
	{
		auto Handle = IndexBuffer.GetHandle();
		auto NumIndices = IndexBuffer.GetCount();

		glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, Handle );
		glDrawElements ( GetGLDrawModeFromDrawMode ( DrawMode ), NumIndices, GL_UNSIGNED_INT, 0 );
		glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );
		LK_RENDER_CHECK_ERROR()
	}

	unsigned int Renderer::GetGLDrawModeFromDrawMode ( DrawMode DrawMode )
	{
		switch ( DrawMode )
		{
			case DrawMode::LineLoop:
			{
				return GL_LINE_LOOP;
			}
			case DrawMode::LineStrip:
			{
				return GL_LINE_STRIP;
			}
			case DrawMode::Lines:
			{
				return GL_LINES;
			}
			case DrawMode::Points:
			{
				return GL_POINTS;
			}
			case DrawMode::TriangleFan:
			{
				return GL_TRIANGLE_FAN;
			}
			case DrawMode::TriangleStrip:
			{
				return GL_TRIANGLE_STRIP;
			}
			case DrawMode::Triangles:
			{
				return GL_TRIANGLES;
			}
			default:
			{
				throw RenderException ( "Undefined DrawMode" );
			}
		}
	}
}
}


