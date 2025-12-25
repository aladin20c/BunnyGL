// --- VertexArray.h ---
#pragma once
#include <memory>
#include <vector>
#include "Buffer.h"

namespace BunnyGL {

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        // Automatically sets up attribute pointers based on VBO layout
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

        // Sets the element buffer
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}