#pragma once

#include "PlatformTypes.h"
#include <functional>
#include <string>

namespace Volante {

struct WindowDesc {
    int width = 800;
    int height = 600;
    std::string title = "Volante";
    bool fullscreen = false;
    bool vsync = true;
    int samples = 1;
};

class IGraphicsContext {
public:
    virtual ~IGraphicsContext() = default;

    virtual void MakeCurrent() = 0;
    virtual void SwapBuffers() = 0;
    virtual void SetVSync(bool Enabled) = 0;
};

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Close() = 0;
    [[nodiscard]] virtual bool ShouldClose() const = 0;

    virtual void SetTitle(const std::string& title) = 0;
    virtual void SetSize(int width, int height) = 0;
    virtual void GetSize(int& width, int& height) const = 0;
    virtual void GetFramebufferSize(int& width, int& height) const = 0;

    [[nodiscard]] virtual void* GetNativeHandle() const = 0;
    [[nodiscard]] virtual IGraphicsContext* GetGraphicsContext() const = 0;
    virtual void SwapBuffers() = 0;

    virtual void PollEvents() = 0;
    [[nodiscard]] virtual bool IsKeyPressed(KeyCode key) const = 0;
    virtual void GetCursorPos(double& x, double& y) const = 0;

    using ResizeCallback = std::function<void(int, int)>;
    using KeyCallback = std::function<void(KeyCode, InputAction)>;
    using MouseButtonCallback = std::function<void(MouseButton, InputAction)>;
    using CursorPosCallback = std::function<void(double, double)>;

    virtual void SetResizeCallback(const ResizeCallback& callback) = 0;
    virtual void SetKeyCallback(const KeyCallback& callback) = 0;
    virtual void SetMouseButtonCallback(const MouseButtonCallback& callback) = 0;
    virtual void SetCursorPosCallback(const CursorPosCallback& callback) = 0;
};

class Window {
public:
    static std::unique_ptr<IWindow> Create(const WindowDesc& InWindowContext);
};

}