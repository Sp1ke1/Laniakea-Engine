#include "glad/glad.h"
#include "Laniakea/Render/Attribute.h"

namespace lk
{
namespace gfx
{

Attribute::Attribute ()
{
	glGenBuffers ( 1, & m_Handle );
	m_Count = 0;
}

Attribute::~Attribute ()
{
	glDeleteBuffers ( 1, & m_Handle );
}


unsigned int Attribute::GetHandle () const
{
	return m_Handle;
}

unsigned int Attribute::GetCount () const
{
	return m_Count;
}

template <typename T>
void Attribute::Set ( T * Array, unsigned int Length )
{
	m_Count = Length;
	unsigned int size = sizeof ( T );
	glBindBuffer ( GL_ARRAY_BUFFER, m_Handle );
	glBufferData ( GL_ARRAY_BUFFER, size * m_Count, Array, GL_STATIC_DRAW );
	glBindBuffer ( GL_ARRAY_BUFFER, 0 );
}

template <typename T>
void Attribute::Set ( std::vector <T> & Array )
{
	Set ( Array.data(), ( unsigned int ) Array . size () );
}


void Attribute::BindTo ( const AttributeDescriptor & Descriptor )
{
	glBindBuffer ( GL_ARRAY_BUFFER, m_Handle );
	glEnableVertexAttribArray ( Descriptor . Slot );
	glVertexAttribPointer ( Descriptor . Slot, Descriptor . Size, GL_FALSE, Descriptor . Type, Descriptor . Stride,
							( void * ) ( uintptr_t ) Descriptor . Offset );
	glBindBuffer ( GL_ARRAY_BUFFER, 0 );
}

void Attribute::UnbindFrom ( unsigned int Slot )
{
	glBindBuffer ( GL_ARRAY_BUFFER, m_Handle );
	glDisableVertexAttribArray ( Slot );
	glBindBuffer ( GL_ARRAY_BUFFER, m_Handle );
}

} // namespace gfx
} // namespace lk