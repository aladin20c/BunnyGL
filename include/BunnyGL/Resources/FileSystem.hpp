#pragma once
#include <string>
#include <fstream>
#include <sstream>

namespace BunnyGL {

    class FileSystem {
    public:

        // Read entire file into string
        static std::string ReadFile(const std::string& filepath) {
            std::ifstream file(filepath, std::ios::in | std::ios::binary);
            if (!file.is_open()) {
                return "";
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }

        // Check if file exists
        static bool FileExists(const std::string& filepath) {
            std::ifstream file(filepath);
            return file.good();
        }

        // Get file extension
        static std::string GetExtension(const std::string& filepath) {
            size_t dotPos = filepath.find_last_of('.');
            if (dotPos == std::string::npos) {
                return "";
            }
            return filepath.substr(dotPos + 1);
        }
    };
}