#include <BunnyGL/Core/Log.hpp>
#include <BunnyGL/Core/Application.hpp>
#include <glad/glad.h>

int main() {

    BG_INFO("Program starting");

    BunnyGL::Application app;
    app.Run();

    BG_INFO("Program ending...");
    return 0;
}