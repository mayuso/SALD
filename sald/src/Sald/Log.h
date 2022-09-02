#pragma once
#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <limits>
#include <stdio.h>
#include <stdarg.h>
#include <memory>

namespace Sald
{
    class Log
    {
    public:
        static void Init();
        SALD_API static std::shared_ptr<spdlog::logger>& GetLogger();
        static std::shared_ptr<spdlog::logger>& GetCoreLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

#define SALD_LOG(...)      ::Sald::Log::GetLogger()->info(__VA_ARGS__)
#define SALD_WARN(...)     ::Sald::Log::GetLogger()->warn(__VA_ARGS__)
#define SALD_ERROR(...)    ::Sald::Log::GetLogger()->error(__VA_ARGS__)

#define SALD_CORE_LOG(...)      ::Sald::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SALD_CORE_WARN(...)     ::Sald::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SALD_CORE_ERROR(...)    ::Sald::Log::GetCoreLogger()->error(__VA_ARGS__)

