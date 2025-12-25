// --- RenderCommand.cpp ---
#include <BunnyGL/Renderer/RenderCommand.h>
#include <glad/glad.h>

namespace BunnyGL {

    void RenderCommand::Init() {
        // Enable Depth Testing (Z-buffer) so objects overlap correctly
        glEnable(GL_DEPTH_TEST);

        // Enable Alpha Blending (for transparency)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }

    void RenderCommand::SetClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void RenderCommand::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
        // Render geometry using the Vertex Array and its associated Index Buffer
        vertexArray->Bind();
        // Uses the count from the IndexBuffer to know how many vertices to draw
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}