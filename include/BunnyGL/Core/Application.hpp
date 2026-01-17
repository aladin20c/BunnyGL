#pragma once
#include <BunnyGL/Core/Window.hpp>
#include <memory>

namespace BunnyGL {
    class Scene;

    class Application {
    
    private:
        Window* m_Window;
        std::unique_ptr<Scene> m_CurrentScene;
        bool m_Running = true;
        // Simple time management
        float m_LastFrameTime = 0.0f;
        float m_DeltaTime = 0.0f;
        float m_TotalTime = 0.0f;
        // FPS tracking
        int m_FrameCount = 0;
        float m_FPS = 0.0f;
        float m_LastFPSCalcTime = 0.0f;
        
    public:
        Application();
        virtual ~Application();
        
        void Run();
        
        // Scene management
        void SetScene(std::unique_ptr<Scene> scene);
        Scene* GetCurrentScene() { return m_CurrentScene.get(); }
        
        // Simple FPS control
        void SetTargetFPS(float fps);
        
        // Getters
        float GetDeltaTime() const { return m_DeltaTime; }
        float GetTotalTime() const { return m_TotalTime; }
        float GetFPS() const { return m_FPS; }
        
    protected:
        Window& GetWindow() { return *m_Window; }
        
    private:
        void UpdateTime();
        void CalculateFPS();
    };
}