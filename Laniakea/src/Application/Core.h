#include "Logger.h"
#include "Input.h"
#include <cassert>

#ifdef LANIAKEA_PLATFORM_WINDOWS
    #ifdef LANIAKEA_BUILD_DLL
        #define LANIAKEA_API __declspec(dllexport)
    #else
        #define LANIAKEA_API __declspec(dllimport)
    #endif
#endif

#ifdef LANIAKEA_BUILD_DEBUG
    #define LK_ASSERT(Condition) { assert (Condition); }
    #define LK_LOG(LogTag, LogType, LogMessage) { Logger::Get() -> Log({LogTag, LogType, LogMessage}); }
#else
    #define LK_LOG(LogTag, LogType, LogMessage)
    #define LK_ASSERT(Condition)
#endif


#define BIT(x) (1 << x )
