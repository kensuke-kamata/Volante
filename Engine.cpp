#include "Engine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ranges>

namespace Volante {

Engine* Engine::Instance = nullptr;

Engine::Engine() {
    Instance = this;
}

Engine::~Engine() {
    Shutdown();
    Instance = nullptr;
}

bool Engine::Initialize(const WindowContext& WindowContext) {
    try {
        Window = Window::Create(WindowContext);
        if (!Window) {
            throw std::runtime_error("Failed to create window");
        }

        Window->GetGraphicsContext()->MakeCurrent();

        std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        World = std::make_unique<class World>();
        Renderer = std::make_unique<class Renderer>(Window.get());
        InputManager = std::make_unique<class InputManager>(Window.get());

        Subsystems.push_back(Renderer.get());
        Subsystems.push_back(InputManager.get());

        for (auto& Subsystem : Subsystems) {
            Subsystem->Initialize();
        }

        Window->SetResizeCallback([this](int Width, int Height) {
            HandleWindowResize(Width, Height);
        });

        Window->Show();
        Running = true;
        LastFrameTime = std::chrono::steady_clock::now();

        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

void Engine::Run() {
    while (Running && !Window->ShouldClose()) {
        const auto CurrentTime = std::chrono::steady_clock::now();
        const float DeltaTime = std::chrono::duration<float>(CurrentTime - LastFrameTime).count();
        LastFrameTime = CurrentTime;

        Window->PollEvents();
        Update(DeltaTime);
        Render();
    }
}

void Engine::Shutdown() {
    if (!Running) { return; }

    Running = false;

    for (const auto& Subsystem : std::ranges::reverse_view(Subsystems)) {
        Subsystem->Shutdown();
    }

    Subsystems.clear();
    InputManager.reset();
    Renderer.reset();
    World.reset();
    Window.reset();
}

void Engine::Update(float DeltaTime) {
    InputManager->Update(DeltaTime);

    if (InputManager->IsKeyPressed(GLFW_KEY_ESCAPE)) {
        RequestExit();
    }

    for (const auto& Subsystem : Subsystems) {
        Subsystem->Update(DeltaTime);
    }

    World->Update(DeltaTime);
}

void Engine::Render() {
    Renderer->BeginFrame();
    Renderer->Clear();

    World->Render(Renderer.get());

    Renderer->EndFrame();
}

void Engine::HandleWindowResize(int Width, int Height) {
    Renderer->SetViewport(0, 0, Width, Height);
}

void World::Update(float DeltaTime) {
    // Update all entities/actors
}

void World::Render(Renderer* Renderer) {
    // Render all entities/actors
}

Renderer::Renderer(IWindow* Window) : Window(Window), Context(Window->GetGraphicsContext()) {}

void Renderer::Initialize() {
    Context->MakeCurrent();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Renderer::Shutdown() {
    // Cleanup rendering resources
}

void Renderer::Update(float DeltaTime) {
    // Update rendering-related state
}

void Renderer::BeginFrame() {
    Context->MakeCurrent();
}

void Renderer::EndFrame() {
    Window->SwapBuffers();
}

void Renderer::SetViewport(int X, int Y, int Width, int Height) {
    glViewport(X, Y, Width, Height);
}

void Renderer::Clear(float R, float G, float B, float A) {
    glClearColor(R, G, B, A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

InputManager::InputManager(IWindow* Window) : Window(Window) {}

void InputManager::Initialize() {
    // Set up input callbacks if needed
}

void InputManager::Shutdown() {
    // Cleanup input resources
}

void InputManager::Update(float DeltaTime) {
    // Process input state
}

bool InputManager::IsKeyPressed(int Key) const {
    return Window->IsKeyPressed(Key);
}

void InputManager::GetMousePosition(double& X, double& Y) const {
    Window->GetCursorPos(X, Y);
}

}