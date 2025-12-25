// --- Shader.cpp ---
#include <BunnyGL/Renderer/Shader.h>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace BunnyGL {

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vertexSrc = ReadFile(vertexPath);
        std::string fragmentSrc = ReadFile(fragmentPath);
        m_RendererID = CreateProgram(vertexSrc, fragmentSrc);
    }

    Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name) {
        m_RendererID = CreateProgram(vertexSrc, fragmentSrc);
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const {
        glUseProgram(0);
    }

    void Shader::SetInt(const std::string& name, int value) {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetFloat(const std::string& name, float value) {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetFloat3(const std::string& name, float v0, float v1, float v2) {
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }

    void Shader::SetMat4(const std::string& name, const float* matrixPointer) {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrixPointer);
    }

    std::string Shader::ReadFile(const std::string& filepath) {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        if (in) {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1) {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
            }
            else {
                std::cout << "Could not read from file: " << filepath << std::endl;
            }
        } else {
            std::cout << "Could not open file: " << filepath << std::endl;
        }
        return result;
    }

    int Shader::GetUniformLocation(const std::string& name) {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];

        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1) std::cout << "Warning: Uniform '" << name << "' doesn't exist!" << std::endl;

        m_UniformLocationCache[name] = location;
        return location;
    }

    uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Check compilation errors
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            // Dynamic allocation on stack for message
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    uint32_t Shader::CreateProgram(const std::string& vertexShader, const std::string& fragmentShader) {
        uint32_t program = glCreateProgram();
        uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }
}