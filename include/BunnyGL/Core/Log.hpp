#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace BunnyGL {

    // Terminal color codes (ANSI)
    namespace Colors {
        static const std::string RESET = "\033[0m";
        static const std::string BLACK = "\033[30m";
        static const std::string RED = "\033[31m";
        static const std::string GREEN = "\033[32m";
        static const std::string YELLOW = "\033[33m";
        static const std::string BLUE = "\033[34m";
        static const std::string MAGENTA = "\033[35m";
        static const std::string CYAN = "\033[36m";
        static const std::string WHITE = "\033[37m";
        static const std::string BOLD = "\033[1m";
    }

    class Log {
    private:
        static std::string getCurrentTime() {
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time), "%H:%M:%S");
            return ss.str();
        }

        static std::string getSourceFile(const std::string& filepath) {
            // Extract just the filename from full path
            size_t lastSlash = filepath.find_last_of("/\\");
            if (lastSlash != std::string::npos) {
                return filepath.substr(lastSlash + 1);
            }
            return filepath;
        }

    public:
        // Info - Green
        template<typename... Args>
        static void Info(const std::string& file, Args... args) {
            std::cout << Colors::GREEN << "[" << getCurrentTime() << "]"
                      << "[INFO]"
                      << "[" << getSourceFile(file) << "] ";
            printArgs(args...);
            std::cout << Colors::RESET << std::endl;
        }

        // Warn - Yellow
        template<typename... Args>
        static void Warn(const std::string& file, Args... args) {
            std::cout << Colors::YELLOW << "[" << getCurrentTime() << "]"
                      << "[WARN]"
                      << "[" << getSourceFile(file) << "] ";
            printArgs(args...);
            std::cout << Colors::RESET << std::endl;
        }

        // Error - Red
        template<typename... Args>
        static void Error(const std::string& file, Args... args) {
            std::cerr << Colors::RED << "[" << getCurrentTime() << "]"
                      << "[ERROR]"
                      << "[" << getSourceFile(file) << "] ";
            printArgs(args...);
            std::cerr << Colors::RESET << std::endl;
        }

        // Fatal - Red Bold (stops program)
        template<typename... Args>
        [[noreturn]] static void Fatal(const std::string& file, Args... args) {
            std::cerr << Colors::BOLD << Colors::RED << "[" << getCurrentTime() << "]"
                      << "[FATAL]"
                      << "[" << getSourceFile(file) << "] ";
            printArgs(args...);
            std::cerr << Colors::RESET << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Raw logging without formatting (for custom messages)
        template<typename... Args>
        static void Raw(Args... args) {
            printArgs(args...);
            std::cout << std::endl;
        }

    private:
        // Base case for recursive template
        static void printArgs() {}

        // Recursive variadic template to print all arguments
        template<typename T, typename... Args>
        static void printArgs(T first, Args... rest) {
            std::cout << first;
            if constexpr(sizeof...(rest) > 0) {
                std::cout << " ";
                printArgs(rest...);
            }
        }
    };

} // namespace BunnyGL

// Convenience macros (these automatically add __FILE__)
#define BG_INFO(...)    BunnyGL::Log::Info(__FILE__, __VA_ARGS__)
#define BG_WARN(...)    BunnyGL::Log::Warn(__FILE__, __VA_ARGS__)
#define BG_ERROR(...)   BunnyGL::Log::Error(__FILE__, __VA_ARGS__)
#define BG_FATAL(...)   BunnyGL::Log::Fatal(__FILE__, __VA_ARGS__)
#define BG_RAW(...)     BunnyGL::Log::Raw(__VA_ARGS__)