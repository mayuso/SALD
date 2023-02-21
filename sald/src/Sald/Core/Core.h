#pragma once

#if !defined(SALD_API)
#if defined(WIN32) || defined(WIN64)
#if defined(_BUILD_DLL)
#define SALD_API __declspec(dllexport) // Export when building DLL
#else
#define SALD_API __declspec(dllimport) // Import when using in other project
#endif
#endif // defined(WIN32) || defined(WIN64)

#if defined(__GNUC__) || defined(LINUX)
#define SALD_API __attribute__((visibility("default")))
#endif // defined(__GNUC__) || defined(LINUX)

#endif // !defined(SALD_API)	

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }