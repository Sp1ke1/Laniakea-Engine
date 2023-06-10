#include "Logger.h"
#include "Input.h"

#ifdef LANIAKEA_PLATFORM_WINDOWS
    #ifdef LANIAKEA_BUILD_DLL
        #define LANIAKEA_API __declspec(dllexport)
    #else
        #define LANIAKEA_API __declspec(dllimport)
    #endif
#endif
