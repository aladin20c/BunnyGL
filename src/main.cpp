#include <BunnyGL/Core/Log.hpp>
#include <BunnyGL/Core/Application.hpp>
#include <BunnyGL/Scene/Scene.hpp>
#include <memory>

int main() {
    BG_INFO("Triangle Demo Starting");
    
    // Create application
    BunnyGL::Application app;
    
    // Create and set scene
    auto scene = std::make_unique<BunnyGL::Scene>();
    app.SetScene(std::move(scene));
    
    // Run main loop
    app.Run();
    
    // Log stats
    BG_INFO("Triangle Demo Ending");
    BG_INFO("  Total runtime: ", app.GetTotalTime()," seconds");
    BG_INFO("  Average FPS: ", app.GetFPS());
    
    return 0;
}