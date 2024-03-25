#pragma once
#include "Laniakea/Render/Core.h"



namespace lk
{
namespace gfx
{

class IndexBuffer;

enum class DrawMode
{
	Points,
	LineStrip,
	LineLoop,
	Lines,
	Triangles,
	TriangleStrip,
	TriangleFan
};

class LANIAKEA_RENDER_API Renderer
{
public:
	static void Render ( IndexBuffer & IndexBuffer, DrawMode DrawMode );
	static void Render ( unsigned int VertexCount, DrawMode DrawMode );


private:
	static unsigned int GetGLDrawModeFromDrawMode ( DrawMode DrawMode );
};

}
}
;