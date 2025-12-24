#include <BunnyGL/Utils/Log.h>

namespace BunnyGL {

    void Log::Output(LogLevel level, const std::string& sender, const std::string& message) {
        // ANSI Color Codes
        const char* colorCode = "\033[0m"; // Default
        const char* levelName = "LOG";

        switch (level) {
            case LogLevel::Trace: colorCode = "\033[94m"; levelName = "TRACE"; break; // Blue
            case LogLevel::Info:  colorCode = "\033[92m"; levelName = "INFO "; break; // Green
            case LogLevel::Warn:  colorCode = "\033[93m"; levelName = "WARN "; break; // Yellow
            case LogLevel::Error: colorCode = "\033[91m"; levelName = "ERROR"; break; // Red
            case LogLevel::Fatal: colorCode = "\033[41m"; levelName = "FATAL"; break; // Red Background
        }

        std::cout << colorCode << "[" << GetTimestamp() << "] "
                  << sender << " " << levelName << ": "
                  << message << "\033[0m" << std::endl;
    }

    std::string Log::GetTimestamp() {
        std::time_t now = std::time(nullptr);
        char buf[10];
        std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&now));
        return std::string(buf);
    }

}