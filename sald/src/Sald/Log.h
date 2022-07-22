#pragma once
#include "Core.h"

#include <limits>
#include <stdio.h>
#include <stdarg.h>

namespace Sald
{
    class Log
    {
    public:
        SALD_API static void Debug(const char *format, ...);
        SALD_API static void Warning(const char *format, ...);
        SALD_API static void Error(const char *format, ...);
    };
}

#define LOG(format, ...) ::Sald::Log::Debug(format, __VA_ARGS__)
#define LOG_WARNING(format, ...) ::Sald::Log::Warning(format, __VA_ARGS__)
#define LOG_ERROR(format, ...) ::Sald::Log::Error(format, __VA_ARGS__)
