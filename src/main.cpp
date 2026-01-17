#include <BunnyGL/Core/Log.hpp>
#include <BunnyGL/Core/Application.hpp>
#include <BunnyGL/Renderer/Shader.hpp>
#include <BunnyGL/Resources/ResourceManager.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace BunnyGL {

    class SandboxApp : public Application {
    private:
        // OpenGL objects
        unsigned int m_VAO;  // Vertex Array Object
        unsigned int m_VBO;  // Vertex Buffer Object
        std::shared_ptr<Shader> m_Shader;  // Our shader program

        // Triangle data
        std::vector<float> m_TriangleVertices;

        // For animation
        float m_RotationAngle = 0.0f;
        float m_LastFrameTime = 0.0f;

    public:
        void OnInit() override {
            BG_INFO("Initializing triangle demo...");

            // Initialize time
            m_LastFrameTime = static_cast<float>(glfwGetTime());

            // Load shader
            m_Shader = ResourceManager::LoadShader("basic","resources/shaders/Basic.vert","resources/shaders/Basic.frag");

            // Define triangle vertices (x, y, z, r, g, b, a)
            m_TriangleVertices = {
                // Bottom-left (Red)
                -0.5f, -0.5f, 0.0f,   // Position (x, y, z)
                1.0f, 0.0f, 0.0f, 1.0f,  // Color (r, g, b, a)

                // Bottom-right (Green)
                0.5f, -0.5f, 0.0f,    // Position
                0.0f, 1.0f, 0.0f, 1.0f,  // Color

                // Top-center (Blue)
                0.0f, 0.5f, 0.0f,     // Position
                0.0f, 0.0f, 1.0f, 1.0f   // Color
            };

            // Generate and bind Vertex Array Object
            glGenVertexArrays(1, &m_VAO);
            glBindVertexArray(m_VAO);

            // Generate and bind Vertex Buffer Object
            glGenBuffers(1, &m_VBO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, m_TriangleVertices.size() * sizeof(float),  m_TriangleVertices.data(), GL_STATIC_DRAW);

            // Set vertex attribute pointers
            // Position attribute (location = 0)
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // Color attribute (location = 1)
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // Unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

        }

        void OnUpdate() override {
            // Calculate delta time
            float currentTime = static_cast<float>(glfwGetTime());
            float deltaTime = currentTime - m_LastFrameTime;
            m_LastFrameTime = currentTime;

            // Update rotation (90 degrees per second)
            m_RotationAngle += 90.0f * deltaTime;
            if (m_RotationAngle > 360.0f) {
                m_RotationAngle -= 360.0f;
            }
        }

        void OnRender() override {
            if (!m_Shader) return;

            // Use our shader
            m_Shader->Bind();

            // Create a simple rotation matrix
            float angleRadians = glm::radians(m_RotationAngle);
            glm::mat4 transform = glm::rotate(glm::mat4(1.0f), angleRadians, glm::vec3(0.0f, 0.0f, 1.0f));

            // Set transformation uniform
            m_Shader->SetUniformMat4f("u_Transform", transform);

            // Draw the triangle
            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // Optional: Unbind
            glBindVertexArray(0);
            m_Shader->Unbind();
        }

        void OnShutdown() override {
            BG_INFO("Cleaning up triangle demo...");

            // Cleanup OpenGL resources
            if (m_VAO) {
                glDeleteVertexArrays(1, &m_VAO);
                m_VAO = 0;
            }

            if (m_VBO) {
                glDeleteBuffers(1, &m_VBO);
                m_VBO = 0;
            }

            // Clear shader cache (optional)
            ResourceManager::ClearAll();

            BG_INFO("Triangle demo cleaned up!");
        }
    };
}

int main() {
    BG_INFO("Program starting");


    // Create the application
    BunnyGL::SandboxApp app;
    app.OnInit();

    // Run the main loop
    app.Run();


    app.OnShutdown();

    BG_INFO("Program ending...");
    return 0;
}