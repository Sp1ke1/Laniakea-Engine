#include "glad/glad.h"
#include "Laniakea/Render/Attribute.h"
#include "Laniakea/Render/RenderException.h"




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

void Attribute::BindTo ( const AttributeDescriptor & Descriptor )
{
	glBindBuffer ( GL_ARRAY_BUFFER, m_Handle );
	glEnableVertexAttribArray ( Descriptor . Slot );
	glVertexAttribPointer ( Descriptor . Slot, Descriptor . Size, Descriptor . Type, GL_FALSE, Descriptor . Stride,
							( void * ) ( uintptr_t ) Descriptor . Offset );
	glBindBuffer ( GL_ARRAY_BUFFER, 0 );
	LK_RENDER_CHECK_ERROR()
}

void Attribute::UnbindFrom ( unsigned int Slot )
{
	glBindBuffer ( GL_ARRAY_BUFFER, m_Handle );
	glDisableVertexAttribArray ( Slot );
	glBindBuffer ( GL_ARRAY_BUFFER, m_Handle );
	LK_RENDER_CHECK_ERROR()
}

} // namespace gfx
} // namespace lk


namespace lk {
namespace gfx {
namespace detail {

	void _SetAttributeImpl(unsigned int handle, const void* data, unsigned int size, unsigned int length) {
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(GL_ARRAY_BUFFER, size * length, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		LK_RENDER_CHECK_ERROR()
	}

} // namespace detail
} // namespace gfx
} // namespace lk
