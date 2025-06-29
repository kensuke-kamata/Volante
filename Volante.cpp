#include <iostream>

#include "Engine.h"

constexpr unsigned int SCR_WIDTH = 1280;
constexpr unsigned int SCR_HEIGHT = 720;
constexpr const char* TITLE = "Volante Engine";

int main() {
    Volante::Engine Engine;

    Volante::WindowDesc WindowContext;
    WindowContext.width = SCR_WIDTH;
    WindowContext.height = SCR_HEIGHT;
    WindowContext.title = TITLE;
    WindowContext.vsync = true;
    WindowContext.samples = 4;

    if (!Engine.Initialize(WindowContext)) {
        std::cerr << "FAILED: Initialize Volante Engine" << std::endl;
        return -1;
    }

    Engine.Run();
    return 0;
}
