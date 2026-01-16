#include <BunnyGL/Core/Window.hpp>
#include <BunnyGL/Core/Log.hpp>

#include <GLFW/glfw3.h>


namespace BunnyGL {

    static void GLFWErrorCallback(int error, const char* description) {
        BG_ERROR("GLFW Error (", error, "): ", description);
    }

    Window::Window(int width, int height, const std::string& title) : m_Width(width), m_Height(height) {

        BG_INFO("Creating window '", title, "' (", width, "x", height,")");

        // Initialize GLFW
        if (!glfwInit()) {
            BG_FATAL("Failed to initialize GLFW");
        }

        glfwSetErrorCallback(GLFWErrorCallback);

        // Configure OpenGL 3.3 Core Profile (required for Mac)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        // Create the window
        m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            glfwTerminate();
            BG_FATAL("Failed to create GLFW window");
        }

        // Make OpenGL context current
        glfwMakeContextCurrent(m_Window);

        // Disable VSync initially for better debugging
        glfwSwapInterval(0);

        BG_INFO("Window created successfully");
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        BG_INFO("Window destroyed");
    }

    void Window::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_Window);
    }

}