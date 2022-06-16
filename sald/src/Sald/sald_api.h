#if !defined(SALD_API)
#define SALD_API /* NOTHING */

#if defined(WIN32) || defined(WIN64)
	#undef SALD_API
	#if defined(SALD_API)
		#define SALD_API __declspec(dllexport)
	#else
		#define SALD_API __declspec(dllimport)
	#endif // defined(DLib_EXPORTS)
#endif // defined(WIN32) || defined(WIN64)

#if defined(__GNUC__) || defined(LINUX)
	#if defined(SALD_API)
		#undef SALD_API
		#define SALD_API __attribute__((visibility("default")))
	#endif // defined(DLib_EXPORTS)
#endif // defined(__GNUC__) || defined(__APPLE__) || defined(LINUX)

#endif // !defined(SALD_API)