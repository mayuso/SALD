#include "saldpch.h"
#include "Sald/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

std::shared_ptr<spdlog::logger> Sald::Log::s_Logger;
std::shared_ptr<spdlog::logger> Sald::Log::s_CoreLogger;

void Sald::Log::Init()
{
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Sald.log", true));

    logSinks[0]->set_pattern("%^[%T] %n: %v%$");
    logSinks[1]->set_pattern("[%T] [%l] %n: %v");

    s_Logger = std::make_shared<spdlog::logger>("App", begin(logSinks), end(logSinks));
    spdlog::register_logger(s_Logger);
    s_Logger->set_level(spdlog::level::trace);
    s_Logger->flush_on(spdlog::level::trace);

    s_CoreLogger = std::make_shared<spdlog::logger>("Sald", begin(logSinks), end(logSinks));
    spdlog::register_logger(s_CoreLogger);
    s_CoreLogger->set_level(spdlog::level::trace);
    s_CoreLogger->flush_on(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Sald::Log::GetLogger()
{
    return s_Logger;
}

std::shared_ptr<spdlog::logger>& Sald::Log::GetCoreLogger()
{
    return s_CoreLogger;
}
