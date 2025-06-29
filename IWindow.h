#pragma once

#include <functional>
#include <memory>
#include <string>

namespace Volante {

class IGraphicsContext;

struct WindowContext {
    int Width = 800;
    int Height = 600;
    std::string Title = "Volante";
    bool Fullscreen = false;
    bool Vsync = true;
    int Samples = 1;
};

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Close() = 0;
    [[nodiscard]] virtual bool ShouldClose() const = 0;

    virtual void SetTitle(const std::string& Title) = 0;
    virtual void SetSize(int Width, int Height) = 0;
    virtual void GetSize(int& Width, int& Height) const = 0;
    virtual void GetFramebufferSize(int& Width, int& Height) const = 0;

    [[nodiscard]] virtual IGraphicsContext* GetGraphicsContext() const = 0;
    virtual void SwapBuffers() = 0;

    virtual void PollEvents() = 0;
    [[nodiscard]] virtual bool IsKeyPressed(int Key) const = 0;
    virtual void GetCursorPos(double& X, double& Y) const = 0;

    using ResizeCallback = std::function<void(int, int)>;
    using KeyCallback = std::function<void(int, int, int, int)>;
    using MouseButtonCallback = std::function<void(int, int, int)>;
    using CursorPosCallback = std::function<void(double, double)>;

    virtual void SetResizeCallback(const ResizeCallback& Callback) = 0;
    virtual void SetKeyCallback(const KeyCallback& Callback) = 0;
    virtual void SetMouseButtonCallback(const MouseButtonCallback& Callback) = 0;
    virtual void SetCursorPosCallback(const CursorPosCallback& Callback) = 0;
};

class IGraphicsContext {
public:
    virtual ~IGraphicsContext() = default;

    virtual void MakeCurrent() = 0;
    virtual void SwapBuffers() = 0;
    virtual void SetVSync(bool Enabled) = 0;
};

class Window {
public:
    static std::unique_ptr<IWindow> Create(const WindowContext& InWindowContext);
};

} // namespace Volante
