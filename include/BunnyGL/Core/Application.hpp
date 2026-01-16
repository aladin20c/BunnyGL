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
        virtual void OnInit();        // Override to initialize
        virtual void OnUpdate();     // Override for per-frame logic
        virtual void OnRender();      // Override for rendering
        virtual void OnShutdown();    // Override for cleanup

        Window& GetWindow() { return *m_Window; }
    };

}