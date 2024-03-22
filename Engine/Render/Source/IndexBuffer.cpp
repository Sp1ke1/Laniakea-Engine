#include "glad/glad.h"
#include "Laniakea/Render/IndexBuffer.h"


namespace lk
{
namespace gfx
{

IndexBuffer::IndexBuffer ()
{
	glGenBuffers (1, &m_Handle);
	m_Count = 0;
}

IndexBuffer::~IndexBuffer ()
{
	glDeleteBuffers (1, &m_Handle);
}

unsigned int IndexBuffer::GetCount () const
{
	return m_Count;
}

unsigned int IndexBuffer::GetHandle () const
{
	return m_Handle;
}

void IndexBuffer::Set ( unsigned int * Array, unsigned int Length )
{
	m_Count = Length;
	unsigned int Size = sizeof ( unsigned int );

	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, m_Handle );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, Size * m_Count, Array, GL_STATIC_DRAW );
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void IndexBuffer::Set ( std::vector <unsigned int> & Array )
{
	Set ( Array.data(), (unsigned int) Array.size() );
}

} // lk
} // gfx