#pragma once

#include <string>
#include <memory>

typedef struct GLFWwindow GLFWwindow;
/**
 * @namespace BunnyGL
 * The primary namespace for all BunnyGL engine systems.
 */
namespace BunnyGL {

    /**
     * @class Application
     * @brief The core engine class that manages the application lifecycle.
     * * This class is responsible for initializing the window, managing the main
     * game loop, and ensuring proper shutdown of all engine subsystems.
     */
    class Application {
    public:
        /**
         * @brief Constructs the Application and initializes engine subsystems.
         * @param name The title of the window.
         * @param width The initial width of the window.
         * @param height The initial height of the window.
         */
        Application(const std::string& name = "BunnyGL Engine", uint32_t width = 1280, uint32_t height = 720);
        /**
         * @brief Virtual destructor to ensure clean cleanup of derived applications.
         */
        virtual ~Application();
        /**
         * @brief Starts the main engine loop.
         * This function will block until the window is closed or m_Running is set to false.
         */
        void Run();
        /**
         * @brief Signals the application to close at the end of the current frame.
         */
        void Close() { m_Running = false; }

    private:
        /**
         * @brief Internal initialization for GLFW and OpenGL.
         * @return true if successful, false if a critical error occurred.
         */
        bool Init();
        /**
         * @brief Internal cleanup of all engine resources.
         */
        void Shutdown();

    private:
        std::string m_Name;
        uint32_t m_Width, m_Height;

        struct GLFWwindow* m_Window = nullptr; // Raw pointer because GLFW is a C-API
        bool m_Running = true;

    private:
        // Delete copy constructor and assignment operator to prevent "Professional"
        // engine logic from being accidentally copied.
        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
    };

}