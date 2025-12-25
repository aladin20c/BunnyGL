// --- Buffer.h ---
#pragma once
#include "BufferLayout.h"
#include <cstdint>

namespace BunnyGL {

    // --- Vertex Buffer ---
    class VertexBuffer {
    public:
        // Create a static buffer with data
        VertexBuffer(const void* vertices, uint32_t size);
        // Create a dynamic buffer for batch rendering
        VertexBuffer(uint32_t size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        // Push new data into the buffer (for dynamic rendering)
        void SetData(const void* data, uint32_t size);

        const BufferLayout& GetLayout() const { return m_Layout; }
        void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    // --- Index Buffer ---
    class IndexBuffer {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        uint32_t GetCount() const { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}