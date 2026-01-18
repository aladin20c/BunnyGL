#pragma once
#include <BunnyGL/Scene/Scene.hpp>
#include <BunnyGL/Renderer/Shader.hpp>
#include <BunnyGL/Resources/ResourceManager.hpp>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BunnyGL {

    class PlanetScene : public Scene {
    private:
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;
        std::shared_ptr<Shader> m_Shader;
        std::vector<float> m_Vertices;
        float m_RotationAngle = 0.0f;
        
    public:
        PlanetScene();
        virtual ~PlanetScene();
        
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        
    private:
        void SetupTriangle();
    };

}