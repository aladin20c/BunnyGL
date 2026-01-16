#pragma once
#include <glad/glad.h>

namespace BunnyGL {
    class VertexBuffer {

    private:
        uint32_t m_RendererID;

    public:
        VertexBuffer(const void* data, uint32_t size) {
            glGenBuffers(1, &m_RendererID);
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        }

        ~VertexBuffer() {
            glDeleteBuffers(1, &m_RendererID);
        }
        void Bind() const {
            glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        }

    };

    class IndexBuffer {
    private:
        uint32_t m_RendererID, m_Count;

    public:
        IndexBuffer(const uint32_t* indices, uint32_t count) : m_Count(count) {
            glGenBuffers(1, &m_RendererID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        }

        void Bind() const {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        }

        uint32_t GetCount() const {
            return m_Count;
        }
    };
}