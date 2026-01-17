#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace BunnyGL {
    class Shader {
    private:
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

    public:
        // Constructors
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        // Delete copy constructor/assignment (OpenGL resources can't be copied)
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        // Move constructor/assignment
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        // Binding
        void Bind() const;
        void Unbind() const;

        // Uniform setters
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform2f(const std::string& name, float v0, float v1);
        void SetUniform3f(const std::string& name, float v0, float v1, float v2);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
        void SetUniformVec2(const std::string& name, const glm::vec2& value);
        void SetUniformVec3(const std::string& name, const glm::vec3& value);
        void SetUniformVec4(const std::string& name, const glm::vec4& value);

        // Getter
        unsigned int GetRendererID() const { return m_RendererID; }

    private:
        // Helper methods
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        int GetUniformLocation(const std::string& name);
    };
}