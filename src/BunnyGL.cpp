#include <BunnyGL/Core/Application.h>

int main() {
    // We wrap this in a scope so the app is destroyed
    // before the program fully exits (RAII)
    {
        BunnyGL::Application app("BunnyGL - Cube Project", 1600, 900);
        app.Run();
    }

    return 0;
}