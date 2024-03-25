#pragma once
#include <vector>
#include "Core.h"

namespace lk
{
namespace gfx
{

namespace detail
{
	void LANIAKEA_RENDER_API _SetAttributeImpl ( unsigned int handle, const void * data, unsigned int size, unsigned int length );
}
struct LANIAKEA_RENDER_API AttributeDescriptor
{
	unsigned int Slot;
	unsigned int Size;
	unsigned int Type; // GLenum type (GL_FLOAT, GL_INT etc)
	int Stride;
	unsigned int Offset;
};

class LANIAKEA_RENDER_API Attribute
{
	public:
		Attribute ();

		~Attribute ();

		Attribute ( const Attribute & ) = delete;

		Attribute & operator = ( const Attribute & ) = delete;

		template <typename T>
		void Set ( T * Array, unsigned int Length )
		{
			m_Count = Length;
			detail::_SetAttributeImpl ( m_Handle, ( void * ) Array, sizeof ( T ), Length );
		}
		template <typename T>
		void Set ( std::vector <T> & Array )
		{
			Set ( Array.data(), Array.size() );
		}

		void BindTo ( const AttributeDescriptor & Descriptor );

		void UnbindFrom ( unsigned int Slot );

		unsigned int GetCount () const;

		unsigned int GetHandle () const;

	private:
		unsigned int m_Count;
		unsigned int m_Handle;
};
} // namespace gfx
} // namespace lk