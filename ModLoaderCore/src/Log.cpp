#include "Log.h"
#include <cstdarg>
#include <cstdio>
#include <Windows.h>
#include <shlobj.h>

namespace ModLoader {

std::string Log::GetLogFile() {
    char path[MAX_PATH];
    // Get user's documents folder
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path))) {
        strcat_s(path, MAX_PATH, "\\sbg-mod-loader");
        CreateDirectoryA(path, NULL);
        strcat_s(path, MAX_PATH, "\\mod-loader.log");
        return std::string(path);
    }
    return "C:\\sbg-mod-loader.log";
}

std::string Log::GetTimestamp() {
    time_t now = time(nullptr);
    tm timeinfo;
    localtime_s(&timeinfo, &now);
    
    char buffer[32];
    strftime(buffer, sizeof(buffer), "%H:%M:%S.000", &timeinfo);
    return std::string(buffer);
}

void Log::Write(const std::string& category, const std::string& message) {
    try {
        std::ofstream file(GetLogFile(), std::ios::app);
        if (file.is_open()) {
            file << "[" << GetTimestamp() << "] [" << category << "] " << message << "\n";
            file.close();
        }
    } catch (...) {
        // Silently fail on logging errors
    }
}

void Log::Info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, args);
    va_end(args);
    
    Write("INFO", std::string(buffer));
}

void Log::Warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, args);
    va_end(args);
    
    Write("WARN", std::string(buffer));
}

void Log::Error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, args);
    va_end(args);
    
    Write("ERROR", std::string(buffer));
}

}  // namespace ModLoader
