#pragma once
#include <string>

struct GLFWwindow;

namespace BunnyGL {

    class Window {

    private:
        GLFWwindow* m_Window;
        int m_Width;
        int m_Height;

    public:
        Window(int width = 1280, int height = 720, const std::string& title = "BunnyGL");
        ~Window();

        void SwapBuffers();
        void PollEvents();
        bool ShouldClose() const;

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
        GLFWwindow* GetNativeWindow() const { return m_Window; }
    };

}