#include "Laniakea/ECS/Core.h"

bool ComponentInfo::operator < ( const ComponentInfo & rhs ) const
{
	return Type < rhs . Type;
}

bool ComponentInfo::operator == ( const ComponentInfo & rhs ) const
{
	return Type == rhs . Type;
}