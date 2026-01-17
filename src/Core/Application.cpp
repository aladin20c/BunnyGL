#include <BunnyGL/Core/Application.hpp>
#include <BunnyGL/Core/Log.hpp>
#include <BunnyGL/Scene/Scene.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BunnyGL {

    Application::Application() {
        BG_INFO("Application Starting ...");

        // Create window
        m_Window = new Window();

        // Initialize OpenGL loader (GLAD)
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            BG_FATAL("Failed to initialize GLAD");
        }

        // Log OpenGL info
        BG_INFO("OpenGL Info:");
        BG_INFO("  Vendor: ", glGetString(GL_VENDOR));
        BG_INFO("  Renderer: ", glGetString(GL_RENDERER));
        BG_INFO("  Version: ", glGetString(GL_VERSION));

        m_LastFrameTime = static_cast<float>(glfwGetTime());
    }

    Application::~Application() {
        delete m_Window;
        BG_INFO("Application Shutdown ...");
    }

    void Application::SetScene(std::unique_ptr<Scene> scene) {
        if (m_CurrentScene) {
            m_CurrentScene->OnDetach();
        }
        m_CurrentScene = std::move(scene);
        if (m_CurrentScene) {
            m_CurrentScene->OnAttach();
        }
    }

    void Application::SetTargetFPS(float fps) {
        // For simplicity, we'll just store it
        // Actual limiting would be done in the loop
    }


    void Application::Run() {
        BG_INFO("Entering Main Loop ...");
        
        while (m_Running && !m_Window->ShouldClose()) {
            // Update timing
            UpdateTime();
            CalculateFPS();
            
            // Clear screen
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Update and render scene
            if (m_CurrentScene) {
                m_CurrentScene->OnUpdate(m_DeltaTime);
                m_CurrentScene->OnRender();
            }
            
            // Swap buffers
            m_Window->SwapBuffers();
            m_Window->PollEvents();
            
            m_FrameCount++;
        }
    }
    
    void Application::UpdateTime() {
        float currentTime = static_cast<float>(glfwGetTime());
        m_DeltaTime = currentTime - m_LastFrameTime;
        m_LastFrameTime = currentTime;
        m_TotalTime = currentTime;
    }
    
    void Application::CalculateFPS() {
        if (m_TotalTime - m_LastFPSCalcTime > 1.0f) { // Every second
            m_FPS = static_cast<float>(m_FrameCount) / (m_TotalTime - m_LastFPSCalcTime);
            m_LastFPSCalcTime = m_TotalTime;
            m_FrameCount = 0;
            
            // Log FPS every 5 seconds
            static float lastLogTime = 0.0f;
            if (m_TotalTime - lastLogTime > 5.0f) {
                BG_RAW("FPS:", m_FPS, "Delta: ",m_DeltaTime * 1000.0f,"ms");
                lastLogTime = m_TotalTime;
            }
        }
    }
}   