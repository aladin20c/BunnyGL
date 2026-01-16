#pragma once
#include <string>
#include <glad/glad.h>

namespace BunnyGL {
    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader() { glDeleteProgram(m_RendererID); }
        void Bind() const { glUseProgram(m_RendererID); }
    private:
        uint32_t m_RendererID;
    };
}