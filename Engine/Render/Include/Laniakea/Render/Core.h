#ifdef LANIAKEA_PLATFORM_WINDOWS
	#ifdef LANIAKEA_BUILD_DLL
		#define LANIAKEA_RENDER_API __declspec (dllexport)
	#else
		#define LANIAKEA_RENDER_API __declspec(dllimport)
	#endif
#else
	#error Laniakea supports only windows
#endif

