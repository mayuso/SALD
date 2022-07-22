#include "saldpch.h"
#include "Log.h"

void Sald::Log::Debug(const char *format, ...)
{
    std::string format_string("\033[32m");
    char message[512];
    va_list args;
    va_start(args, format);
    vsnprintf(message, 512, format, args);
    va_end(args);
    std::string message_string(message);
    std::cout << format_string + message_string << std::endl;
}

void Sald::Log::Warning(const char *format, ...)
{
    std::string format_string("\033[33m");
    char message[512];
    va_list args;
    va_start(args, format);
    vsnprintf(message, 512, format, args);
    va_end(args);
    std::string message_string(message);
    std::cout << format_string + message_string << std::endl;
}

void Sald::Log::Error(const char *format, ...)
{
    std::string format_string("\033[31m");
    char message[512];
    va_list args;
    va_start(args, format);
    vsnprintf(message, 512, format, args);
    va_end(args);
    std::string message_string(message);
    std::cerr << format_string + message_string << std::endl;
}
