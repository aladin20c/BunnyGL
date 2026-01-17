#pragma once

#include <BunnyGL/Renderer/Shader.hpp>
#include <BunnyGL/Resources/ResourceManager.hpp>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BunnyGL {

    class Scene {
    private:
        // Triangle data
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;
        std::shared_ptr<Shader> m_Shader;
        std::vector<float> m_Vertices;
        float m_RotationAngle = 0.0f;

    public:
        Scene();
        virtual ~Scene();
        
        // Lifecycle
        virtual void OnAttach();
        virtual void OnDetach();
        
        // Core methods
        virtual void OnUpdate(float deltaTime);
        virtual void OnRender();
        
        // Optional overrides
        virtual void OnWindowResize(int width, int height) {}
        virtual void OnKeyPressed(int key, int mods) {}
        virtual void OnKeyReleased(int key, int mods) {}
        virtual void OnMouseMoved(double x, double y) {}
        virtual void OnMouseButton(int button, int action, int mods) {}
        
    private:
        void SetupTriangle();
    };

}