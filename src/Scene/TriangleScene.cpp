#include <BunnyGL/Scene/TriangleScene.hpp>
#include <BunnyGL/Core/Log.hpp>
#include <glad/glad.h>

namespace BunnyGL {

    TriangleScene::TriangleScene() {
        BG_INFO("TriangleScene created");
    }
    
    TriangleScene::~TriangleScene() {
        OnDetach();
        BG_INFO("TriangleScene destroyed");
    }
    
    void TriangleScene::OnAttach() {
        BG_INFO("TriangleScene attached");
        
        m_Shader = ResourceManager::LoadShader("basic",
            "resources/shaders/Basic.vert",
            "resources/shaders/Basic.frag");
        
        if (!m_Shader) {
            BG_ERROR("Failed to load shader!");
            return;
        }
        
        SetupTriangle();
    }
    
    void TriangleScene::OnDetach() {
        BG_INFO("TriangleScene detached");
        
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
        m_VAO = m_VBO = 0;
    }
    
    void TriangleScene::OnUpdate(float deltaTime) {
        m_RotationAngle += 90.0f * deltaTime;
        if (m_RotationAngle > 360.0f) {
            m_RotationAngle -= 360.0f;
        }
    }
    
    void TriangleScene::OnRender() {
        if (!m_Shader) return;
        
        m_Shader->Bind();
        
        float angleRadians = glm::radians(m_RotationAngle);
        glm::mat4 transform = glm::rotate(
            glm::mat4(1.0f), 
            angleRadians, 
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        
        m_Shader->SetUniformMat4f("u_Transform", transform);
        
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        m_Shader->Unbind();
    }
    
    void TriangleScene::SetupTriangle() {
        m_Vertices = {
            -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f
        };
        
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(float),m_Vertices.data(), GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        BG_INFO("Triangle setup complete");
    }

}