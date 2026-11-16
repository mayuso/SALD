#pragma once

#include <utility> // std::forward, used by BIND_EVENT_FN

#if !defined(SALD_API)
#if defined(_WIN32)
#if defined(_BUILD_DLL)
#define SALD_API __declspec(dllexport) // Export when building DLL
#else
#define SALD_API __declspec(dllimport) // Import when using in other project
#endif
#elif defined(__GNUC__)
#define SALD_API __attribute__((visibility("default")))
#else
#define SALD_API
#endif
#endif // !defined(SALD_API)

#define BIT(x) (1 << (x))

#define BIND_EVENT_FN(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }