#pragma once

#include "IWindow.h"

namespace Volante {

class World;
class Renderer;
class InputManager;

class IEngineSubsystem {
public:
    virtual ~IEngineSubsystem() = default;

    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void Update(float DeltaTime) = 0;
};

class Engine {
public:
    Engine();
    ~Engine();

    bool Initialize(const WindowContext& WindowContext);
    void Run();
    void Shutdown();
    void RequestExit() { Running = false; }

    [[nodiscard]] IWindow* GetWindow() const { return Window.get(); }
    [[nodiscard]] World* GetWorld() const { return World.get(); }
    [[nodiscard]] Renderer* GetRenderer() const { return Renderer.get(); }
    [[nodiscard]] InputManager* GetInputManager() const { return InputManager.get(); }

    static Engine* Get() { return Instance; }

private:
    void Update(float DeltaTime);
    void Render();
    void HandleWindowResize(int Width, int Height);

    static Engine* Instance;

    std::unique_ptr<IWindow> Window;
    std::unique_ptr<World> World;
    std::unique_ptr<Renderer> Renderer;
    std::unique_ptr<InputManager> InputManager;

    std::vector<IEngineSubsystem*> Subsystems;

    bool Running = false;
    std::chrono::steady_clock::time_point LastFrameTime;
};

class World {
public:
    World() = default;
    ~World() = default;

    void Update(float DeltaTime);
    void Render(Renderer* Renderer);

    // Entity management would go here
    // void SpawnActor(...);
    // void DestroyActor(...);
};

class Renderer : public IEngineSubsystem {
public:
    explicit Renderer(IWindow* Window);
    ~Renderer() override = default;

    void Initialize() override;
    void Shutdown() override;
    void Update(float DeltaTime) override;

    void BeginFrame();
    void EndFrame();
    void SetViewport(int X, int Y, int Width, int Height);
    void Clear(float R = 0.0f, float G = 0.0f, float B = 0.0f, float A = 1.0f);

private:
    IWindow* Window;
    IGraphicsContext* Context;
};

class InputManager : public IEngineSubsystem {
public:
    explicit InputManager(IWindow* Window);
    ~InputManager() override = default;

    void Initialize() override;
    void Shutdown() override;
    void Update(float DeltaTime) override;

    [[nodiscard]] bool IsKeyPressed(int kKey) const;
    void GetMousePosition(double& X, double& Y) const;

private:
    IWindow* Window;
};

}