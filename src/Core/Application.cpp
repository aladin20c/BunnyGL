#include <BunnyGL/Core/Application.h>
#include <BunnyGL/Utils/Log.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BunnyGL {

    Application::Application(const std::string& name, uint32_t width, uint32_t height)
        : m_Name(name), m_Width(width), m_Height(height)
    {
        BGL_CORE_INFO("Creating Application: ", name, " (", width, "x", height, ")");

        if (!Init()) {
            BGL_CORE_ERROR("Application failed to initialize!");
        }
    }

    Application::~Application() {
        BGL_CORE_INFO("Shutting down Application...");
        Shutdown();
    }

    bool Application::Init() {
        if (!glfwInit()) {
            BGL_CORE_ERROR("Failed to initialize GLFW!");
            return false;
        }

        // macOS Specific Hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_Window = glfwCreateWindow((int)m_Width, (int)m_Height, m_Name.c_str(), nullptr, nullptr);

        if (!m_Window) {
            BGL_CORE_ERROR("Failed to create GLFW window!");
            return false;
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            BGL_CORE_ERROR("Failed to initialize GLAD!");
            return false;
        }

        BGL_CORE_INFO("OpenGL Context Initialized.");
        BGL_CORE_INFO("Vendor:   ", glGetString(GL_VENDOR));
        BGL_CORE_INFO("Renderer: ", glGetString(GL_RENDERER));
        BGL_CORE_INFO("Version:  ", glGetString(GL_VERSION));

        return true;
    }

    void Application::Run() {
        if (!m_Window) return;

        while (m_Running) {
            if (glfwWindowShouldClose(m_Window))
                m_Running = false;

            // Render Commands
            glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }

    void Application::Shutdown() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
        }
        glfwTerminate();
    }

}