// --- RenderCommand.h ---
#pragma once
#include "VertexArray.h"
#include <glm/glm.hpp> // Assumes you have GLM included

namespace BunnyGL {

    class RenderCommand {
    public:
        // Initialize renderer state (blending, depth test)
        static void Init();

        // Update the viewport size (e.g. on window resize)
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        // Set the color to clear the screen to
        static void SetClearColor(const glm::vec4& color);

        // Clear the screen (color and depth buffer)
        static void Clear();

        // The raw draw call - this is the only place glDrawElements should exist
        static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
    };

}