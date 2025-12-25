// --- Renderer.h ---
#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <memory>

namespace BunnyGL {

    class Renderer {
    public:
        // Start up the renderer system
        static void Init();

        // Handle window resizing events
        static void OnWindowResize(uint32_t width, uint32_t height);

        // Begin a scene context: Sets up the camera view/projection matrices
        // Note: You would typically pass a Camera object here, but we use a matrix for flexibility
        static void BeginScene(const glm::mat4& viewProjectionMatrix);

        // End the scene context
        static void EndScene();

        // Submit a mesh to be rendered
        // shader: The material to use
        // vertexArray: The geometry
        // transform: The position/rotation/scale of the object (Model Matrix)
        static void Submit(const std::shared_ptr<Shader>& shader,
                           const std::shared_ptr<VertexArray>& vertexArray,
                           const glm::mat4& transform = glm::mat4(1.0f));

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static std::unique_ptr<SceneData> s_SceneData;
    };
}