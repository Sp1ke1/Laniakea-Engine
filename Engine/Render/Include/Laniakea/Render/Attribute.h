#pragma once
#include <vector>
#include "Core.h"

namespace lk
{
namespace gfx
{

struct  AttributeDescriptor
{
	unsigned int Slot;
	unsigned int Size;
	unsigned int Type; // GLenum type (GL_FLOAT, GL_INT etc)
	int Stride;
	unsigned int Offset;
};

class  Attribute
{
	public:
		Attribute ();

		~Attribute ();

		Attribute ( const Attribute & ) = delete;

		Attribute & operator = ( const Attribute & ) = delete;

		template <typename T>
		void Set ( T * Array, unsigned int Lenght );

		template <typename T>
		void Set ( std::vector <T> & Array );

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