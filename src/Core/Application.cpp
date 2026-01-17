#include <BunnyGL/Core/Application.hpp>
#include <BunnyGL/Core/Log.hpp>
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
    }

    Application::~Application() {
        delete m_Window;
        BG_INFO("Application Shutdown ...");
    }

    void Application::Run() {
        BG_INFO("Entering Main Loop ...");
        while (m_Running && !m_Window->ShouldClose()) {
            // Update logic
            OnUpdate();

            // Render
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            OnRender();

            // Swap buffers and poll events
            m_Window->SwapBuffers();
            m_Window->PollEvents();
        }
    }


}