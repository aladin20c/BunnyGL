#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

namespace BunnyGL {

    enum class LogLevel { Trace = 0, Info, Warn, Error, Fatal };

    class Log {
    public:

        // Main generic log function
        template<typename... Args>
        static void WriteLog(LogLevel level, const std::string& sender, Args&&... args) {
            std::ostringstream oss;
            (oss << ... << args); // C++17 Fold Expression

            Output(level, sender, oss.str());
        }

    private:
        static void Output(LogLevel level, const std::string& sender, const std::string& message);
        static std::string GetTimestamp();
    };

}

// --- Professional Macros ---
// These make it easy to use and allow us to strip logs out later if needed.
#define BGL_CORE_TRACE(...) ::BunnyGL::Log::WriteLog(::BunnyGL::LogLevel::Trace, "CORE", __VA_ARGS__)
#define BGL_CORE_INFO(...)  ::BunnyGL::Log::WriteLog(::BunnyGL::LogLevel::Info,  "CORE", __VA_ARGS__)
#define BGL_CORE_WARN(...)  ::BunnyGL::Log::WriteLog(::BunnyGL::LogLevel::Warn,  "CORE", __VA_ARGS__)
#define BGL_CORE_ERROR(...) ::BunnyGL::Log::WriteLog(::BunnyGL::LogLevel::Error, "CORE", __VA_ARGS__)