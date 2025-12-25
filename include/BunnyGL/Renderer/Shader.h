// --- Shader.h ---
#pragma once
#include <string>
#include <unordered_map>

namespace BunnyGL {

    class Shader {
    public:
        // Constructor that reads from file paths
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        // Constructor that takes raw source code strings
        Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Uniform Utility Functions
        void SetInt(const std::string& name, int value);
        void SetFloat(const std::string& name, float value);
        void SetFloat3(const std::string& name, float v0, float v1, float v2);
        void SetMat4(const std::string& name, const float* matrixPointer);

    private:
        // Helper to read file content into string
        std::string ReadFile(const std::string& filepath);
        // Helper to compile individual shaders
        uint32_t CompileShader(uint32_t type, const std::string& source);
        // Links vertex and fragment shaders
        uint32_t CreateProgram(const std::string& vertexShader, const std::string& fragmentShader);
        // Finds or retrieves cached uniform location
        int GetUniformLocation(const std::string& name);

        uint32_t m_RendererID;
        std::string m_Name;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    };
}