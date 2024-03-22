#pragma once

#include "cstdint"
#define NULL_HANDLE (-1ULL)

#ifdef LANIAKEA_PLATFORM_WINDOWS
	#ifdef LANIAKEA_BUILD_DLL
		#define LANIAKEA_ECS_API __declspec (dllexport)
	#else
		#define LANIAKEA_ECS_API __declspec(dllimport)
	#endif
#else
	#error Laniakea supports only windows
#endif



typedef std::size_t ObjectHandle;
typedef ObjectHandle EntityHandle;
typedef ObjectHandle SystemHandle;
typedef ObjectHandle ComponentHandle;
typedef std::size_t ComponentType;
typedef std::size_t SystemType;


/**
 * @brief Struct representing information about a component attached to an entity.
 */
struct LANIAKEA_ECS_API ComponentInfo
{
	ComponentType Type; /** < The type identifier of the component. */
	ComponentHandle Handle; /** < The handle of the component within its respective ObjectManager. */

	bool operator < ( const ComponentInfo & rhs ) const;

	bool operator == ( const ComponentInfo & rhs ) const;
};

