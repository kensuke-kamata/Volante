#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <unordered_map>

#include "Runtime/Core/HAL/IWindow.h"

namespace Volante
{

class GLFWContext final : public IGraphicsContext
{
public:
    explicit GLFWContext(GLFWwindow* window);
    ~GLFWContext() override = default;

    void MakeCurrent() override;
    void SwapBuffers() override;
    void SetVSync(bool enabled) override;

private:
    GLFWwindow* window_;
};

class GLFWWindow final : public IWindow
{
public:
    explicit GLFWWindow(const WindowDesc& windowDesc);
    ~GLFWWindow() override;

    void Show() override;
    void Hide() override;
    void Close() override;
    [[nodiscard]] bool ShouldClose() const override;

    void SetTitle(const std::string& Title) override;
    void SetSize(int Width, int Height) override;
    void GetSize(int& Width, int& Height) const override;
    void GetFramebufferSize(int& Width, int& Height) const override;

    [[nodiscard]] void* GetNativeHandle() const override;
    [[nodiscard]] IGraphicsContext* GetGraphicsContext() const override;
    void SwapBuffers() override;

    void PollEvents() override;
    [[nodiscard]] bool IsKeyPressed(KeyCode key) const override;
    void GetCursorPos(double& X, double& Y) const override;

    void SetResizeCallback(const ResizeCallback& Callback) override;
    void SetKeyCallback(const KeyCallback& Callback) override;
    void SetMouseButtonCallback(const MouseButtonCallback& Callback) override;
    void SetCursorPosCallback(const CursorPosCallback& Callback) override;

private:
    static void GLFWResizeCallback(GLFWwindow* Window, int Width, int Height);
    static void GLFWKeyCallback(GLFWwindow* Window, int Key, int Scancode, int action, int Mods);
    static void GLFWMouseButtonCallback(GLFWwindow* Window, int Button, int action, int Mods);
    static void GLFWCursorPosCallback(GLFWwindow* Window, double XPos, double YPos);

    static std::unordered_map<GLFWwindow*, GLFWWindow*> Registry;

    GLFWwindow* Window;
    std::unique_ptr<GLFWContext> Context;

    ResizeCallback resizeCallback_;
    KeyCallback keyCallback_;
    MouseButtonCallback mouseButtonCallback_;
    CursorPosCallback cursorPosCallback_;
};

} // namespace Volante
