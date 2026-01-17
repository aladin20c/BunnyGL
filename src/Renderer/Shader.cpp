#include <BunnyGL/Renderer/Shader.hpp>
#include <BunnyGL/Resources/FileSystem.hpp>
#include <BunnyGL/Core/Log.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace BunnyGL {

    // Constructor from separate files
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : m_RendererID(0) {

        // Read shader files
        std::string vertexSource = FileSystem::ReadFile(vertexPath);
        std::string fragmentSource = FileSystem::ReadFile(fragmentPath);

        if (vertexSource.empty() || fragmentSource.empty()) {
            BG_ERROR("Failed to load shader files:", vertexPath," or ", fragmentPath);
            return;
        }

        m_RendererID = CreateShader(vertexSource, fragmentSource);
    }

    // Destructor
    Shader::~Shader() {
        if (m_RendererID != 0) {glDeleteProgram(m_RendererID);}
    }

    // Move constructor
    Shader::Shader(Shader&& other) noexcept : m_RendererID(other.m_RendererID), m_UniformLocationCache(std::move(other.m_UniformLocationCache)) {
        other.m_RendererID = 0;
    }

    // Move assignment
    Shader& Shader::operator=(Shader&& other) noexcept {
        if (this != &other) {
            if (m_RendererID != 0) {
                glDeleteProgram(m_RendererID);
            }

            m_RendererID = other.m_RendererID;
            m_UniformLocationCache = std::move(other.m_UniformLocationCache);
            other.m_RendererID = 0;
        }
        return *this;
    }

    // Bind shader
    void Shader::Bind() const {
        if (m_RendererID != 0) {
            glUseProgram(m_RendererID);
        }
    }

    // Unbind shader
    void Shader::Unbind() const {
        glUseProgram(0);
    }

    // Compile individual shader
    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
        unsigned int shader = glCreateShader(type);
        if (shader == 0) {
            BG_FATAL("Failed to create shader object");
            return 0;
        }

        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        // Check compilation status
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            char* message = new char[length];
            glGetShaderInfoLog(shader, length, nullptr, message);

            BG_ERROR("Failed to compile shader:",message);
            delete[] message;
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    // Create complete shader program
    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

        if (vertexShader.empty() || fragmentShader.empty()) {
            BG_ERROR("Empty shader source provided");
            return 0;
        }
        // Create program
        unsigned int program = glCreateProgram();
        if (program == 0) {
            BG_ERROR("Failed to create shader program");
            return 0;
        }

        // Compile shaders
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        if (vs == 0 || fs == 0) {
            glDeleteProgram(program);
            return 0;
        }

        // Attach and link
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        // Check linking status
        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            char* message = new char[length];
            glGetProgramInfoLog(program, length, nullptr, message);
            BG_ERROR("Failed to link shader program:", message);
            delete[] message;
            glDeleteShader(vs);
            glDeleteShader(fs);
            glDeleteProgram(program);
            return 0;
        }

        // Cleanup individual shaders
        glDetachShader(program, vs);
        glDetachShader(program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    // Get uniform location with caching
    int Shader::GetUniformLocation(const std::string& name) {
        // Check cache first
        auto it = m_UniformLocationCache.find(name);
        if (it != m_UniformLocationCache.end()) {
            return it->second;
        }

        // Get from OpenGL
        int location = glGetUniformLocation(m_RendererID, name.c_str());

        // Cache result (even if -1 to avoid repeated lookups)
        m_UniformLocationCache[name] = location;

        if (location == -1) {
            BG_WARN("Uniform ",name," not found in shader (ID:",m_RendererID,")");
        }

        return location;
    }

    // Uniform setters (with location check)
    void Shader::SetUniform1i(const std::string& name, int value) {
        int location = GetUniformLocation(name);
        if (location != -1) {
            glUniform1i(location, value);
        }
    }

    void Shader::SetUniform1f(const std::string& name, float value) {
        int location = GetUniformLocation(name);
        if (location != -1) {
            glUniform1f(location, value);
        }
    }

    void Shader::SetUniform2f(const std::string& name, float v0, float v1) {
        int location = GetUniformLocation(name);
        if (location != -1) {
            glUniform2f(location, v0, v1);
        }
    }

    void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
        int location = GetUniformLocation(name);
        if (location != -1) {
            glUniform3f(location, v0, v1, v2);
        }
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
        int location = GetUniformLocation(name);
        if (location != -1) {
            glUniform4f(location, v0, v1, v2, v3);
        }
    }

    void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix) {
        int location = GetUniformLocation(name);
        if (location != -1) {
            glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]);
        }
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
        int location = GetUniformLocation(name);
        if (location != -1) {
            glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
        }
    }

    void Shader::SetUniformVec2(const std::string& name, const glm::vec2& value) {
        SetUniform2f(name, value.x, value.y);
    }

    void Shader::SetUniformVec3(const std::string& name, const glm::vec3& value) {
        SetUniform3f(name, value.x, value.y, value.z);
    }

    void Shader::SetUniformVec4(const std::string& name, const glm::vec4& value) {
        SetUniform4f(name, value.x, value.y, value.z, value.w);
    }
}