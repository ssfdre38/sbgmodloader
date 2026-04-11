#pragma once
#include <Windows.h>
#include <string>
#include <fstream>

namespace ModLoader {

/// Internal logging for mod loader
class Log {
public:
    static void Write(const std::string& category, const std::string& message);
    static void Info(const char* format, ...);
    static void Warn(const char* format, ...);
    static void Error(const char* format, ...);
    
private:
    static std::string GetLogFile();
    static std::string GetTimestamp();
};

}  // namespace ModLoader

#define LOG_INFO(fmt, ...) ModLoader::Log::Info(fmt, __VA_ARGS__)
#define LOG_WARN(fmt, ...) ModLoader::Log::Warn(fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...) ModLoader::Log::Error(fmt, __VA_ARGS__)
