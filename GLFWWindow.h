#pragma once

#include "IWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Volante {

class GLContext final : public IGraphicsContext {
public:
    explicit GLContext(GLFWwindow* Window);
    ~GLContext() override = default;

    void MakeCurrent() override;
    void SwapBuffers() override;
    void SetVSync(bool Enabled) override;

private:
    GLFWwindow* Window;
};

class GLFWWindow final : public IWindow {
public:
    explicit GLFWWindow(const WindowContext& InWindowContext);
    ~GLFWWindow() override;

    void Show() override;
    void Hide() override;
    void Close() override;
    [[nodiscard]] bool ShouldClose() const override;

    void SetTitle(const std::string& Title) override;
    void SetSize(int Width, int Height) override;
    void GetSize(int& Width, int& Height) const override;
    void GetFramebufferSize(int& Width, int& Height) const override;

    [[nodiscard]] IGraphicsContext* GetGraphicsContext() const override;
    void SwapBuffers() override;

    void PollEvents() override;
    [[nodiscard]] bool IsKeyPressed(int Key) const override;
    void GetCursorPos(double& X, double& Y) const override;

    void SetResizeCallback(const IWindow::ResizeCallback& Callback) override;
    void SetKeyCallback(const IWindow::KeyCallback& Callback) override;
    void SetMouseButtonCallback(const IWindow::MouseButtonCallback& Callback) override;
    void SetCursorPosCallback(const IWindow::CursorPosCallback& Callback) override;

private:
    static void OnResize(GLFWwindow* Window, int Width, int Height);
    static void OnKeyEvent(GLFWwindow* Window, int Key, int Scancode, int action, int Mods);
    static void OnMouseButtonEvent(GLFWwindow* Window, int Button, int action, int Mods);
    static void OnMoveCursorPos(GLFWwindow* Window, double XPos, double YPos);

    static std::unordered_map<GLFWwindow*, GLFWWindow*> Registry;

    GLFWwindow* Window;
    std::unique_ptr<GLContext> Context;

    ResizeCallback ResizeCallback;
    KeyCallback KeyCallback;
    MouseButtonCallback MouseButtonCallback;
    CursorPosCallback CursorPosCallback;
};

} // namespace Volante
