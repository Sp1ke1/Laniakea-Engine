#include "Types.h"

bool ComponentInfo::operator < ( const ComponentInfo & rhs ) const
{
	return Type < rhs . Type;
}

bool ComponentInfo::operator == ( const ComponentInfo & rhs ) const
{
	return Type == rhs . Type;
}