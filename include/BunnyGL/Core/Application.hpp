#pragma once
#include <BunnyGL/Core/Window.hpp>

namespace BunnyGL {

    class Application {

    private:
        Window* m_Window;
        bool m_Running = true;

    public:
        Application();
        virtual ~Application();
        void Run();

    protected:
        virtual void OnInit() = 0;     //  to initialize
        virtual void OnUpdate() = 0;     //  for per-frame logic
        virtual void OnRender() = 0;      //  for rendering
        virtual void OnShutdown() = 0;    //  for cleanup

        Window& GetWindow() { return *m_Window; }
    };

}