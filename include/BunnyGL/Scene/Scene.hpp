#pragma once
#include <memory>

namespace BunnyGL {
    
    class Scene {
    public:
        virtual ~Scene() = default;
        
        // Lifecycle
        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        
        // Core methods
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnRender() = 0;
        
        // Optional overrides
        virtual void OnWindowResize(int width, int height) {}
        virtual void OnKeyPressed(int key, int mods) {}
        virtual void OnKeyReleased(int key, int mods) {}
        virtual void OnMouseMoved(double x, double y) {}
        virtual void OnMouseButton(int button, int action, int mods) {}
    };

}