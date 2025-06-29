#include "Engine.h"

#include <iostream>

constexpr unsigned int SCR_WIDTH = 1280;
constexpr unsigned int SCR_HEIGHT = 720;
constexpr const char* TITLE = "Volante Engine";

int main() {
    Volante::Engine Engine;

    Volante::WindowContext WindowContext;
    WindowContext.Width = SCR_WIDTH;
    WindowContext.Height = SCR_HEIGHT;
    WindowContext.Title = TITLE;
    WindowContext.Vsync = true;
    WindowContext.Samples = 4;

    if (!Engine.Initialize(WindowContext)) {
        std::cerr << "FAILED: Initialize Volante Engine" << std::endl;
        return -1;
    }

    Engine.Run();
    return 0;
}
