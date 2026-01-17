#include <BunnyGL/Scene/Scene.hpp>
#include <BunnyGL/Core/Log.hpp>
#include <glad/glad.h>

namespace BunnyGL {

    // CONSTRUCTOR
    Scene::Scene() {
        BG_INFO("Scene created");
    }
    
    // DESTRUCTOR
    Scene::~Scene() {
        OnDetach();
        BG_INFO("Scene destroyed");
    }
    
    // OnAttach
    void Scene::OnAttach() {
        BG_INFO("Scene attached");
        
        // Load shader
        m_Shader = ResourceManager::LoadShader("basic",
            "resources/shaders/Basic.vert",
            "resources/shaders/Basic.frag");
        
        if (!m_Shader) {
            BG_FATAL("Failed to load shader!");
            return;
        }
        
        // Setup triangle geometry
        SetupTriangle();
    }
    
    // OnDetach
    void Scene::OnDetach() {
        BG_INFO("Scene detached");
        
        // Cleanup OpenGL resources
        if (m_VAO) {
            glDeleteVertexArrays(1, &m_VAO);
            m_VAO = 0;
        }
        if (m_VBO) {
            glDeleteBuffers(1, &m_VBO);
            m_VBO = 0;
        }
    }
    
    // OnUpdate
    void Scene::OnUpdate(float deltaTime) {
        // Simple rotation animation
        m_RotationAngle += 90.0f * deltaTime; // 90 degrees per second
        if (m_RotationAngle > 360.0f) {
            m_RotationAngle -= 360.0f;
        }
    }
    
    // OnRender
    void Scene::OnRender() {
        if (!m_Shader) return;
        
        // Bind shader
        m_Shader->Bind();
        
        // Create rotation matrix
        float angleRadians = glm::radians(m_RotationAngle);
        glm::mat4 transform = glm::rotate(
            glm::mat4(1.0f), 
            angleRadians, 
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        
        // Set uniform
        m_Shader->SetUniformMat4f("u_Transform", transform);
        
        // Draw triangle
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        // Unbind shader
        m_Shader->Unbind();
    }
    
    // SetupTriangle
    void Scene::SetupTriangle() {
        // Define triangle vertices: position (x,y,z) + color (r,g,b,a)
        m_Vertices = {
            // Bottom-left (Red)
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            
            // Bottom-right (Green)
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            
            // Top-center (Blue)
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };
        
        // Create VAO
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        
        // Create VBO
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, 
                    m_Vertices.size() * sizeof(float),
                    m_Vertices.data(), 
                    GL_STATIC_DRAW);
        
        // Set vertex attributes
        // Position (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                             7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // Color (location = 1)
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 
                             7 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        BG_INFO("Triangle setup complete");
    }

}