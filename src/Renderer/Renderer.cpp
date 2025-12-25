// --- Renderer.cpp ---
#include <BunnyGL/Renderer/Renderer.h>
namespace BunnyGL {

    // Define the static scene data
    std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::Init() {
        RenderCommand::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(const glm::mat4& viewProjectionMatrix) {
        s_SceneData->ViewProjectionMatrix = viewProjectionMatrix;
    }

    void Renderer::EndScene() {
        // If we were batching, we would "flush" the batch here.
        // For now, we draw immediately in Submit(), so this is empty.
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader,
                          const std::shared_ptr<VertexArray>& vertexArray,
                          const glm::mat4& transform) {

        // 1. Bind the shader (Material)
        shader->Bind();

        // 2. Upload Scene Uniforms (Camera)
        // Ensure your shader has a uniform named "u_ViewProjection"
        shader->SetMat4("u_ViewProjection", &s_SceneData->ViewProjectionMatrix[0][0]);

        // 3. Upload Object Uniforms (Transform)
        // Ensure your shader has a uniform named "u_Transform" or "u_Model"
        shader->SetMat4("u_Transform", &transform[0][0]);

        // 4. Submit the draw call
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}