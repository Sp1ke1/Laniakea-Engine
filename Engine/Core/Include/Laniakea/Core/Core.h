#pragma once
#include <assert.h>

#ifdef LANIAKEA_PLATFORM_WINDOWS
	#ifdef LANIAKEA_BUILD_DLL
		#define LANIAKEA_CORE_API __declspec (dllexport)
	#else
		#define LANIAKEA_CORE_API __declspec(dllimport)
	#endif
#else
	#error Laniakea supports only windows
#endif



#ifdef LANIAKEA_BUILD_DEBUG
    #define LK_ASSERT(Condition) { assert (Condition); }
#else
    #define LK_ASSERT(Condition)
#endif

#define BIT(x) (1 << x )
/*

// STL containers
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

// I/O

#include <sstream>
#include <fstream>
#include <iostream>

// Utility

#include <functional>
#include <algorithm>
#include <cassert>
#include <cstdint>
*/

