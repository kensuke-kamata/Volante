#include "GLFWWindow.h"

namespace Volante {

std::unordered_map<GLFWwindow*, GLFWWindow*> GLFWWindow::Registry;

class GLFWInitializer {
public:
    GLFWInitializer() {
        if (glfwInit() == GLFW_FALSE) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        Initialized = true;
    }

    ~GLFWInitializer() {
        if (Initialized) {
            glfwTerminate();
        }
    }

    static void Initialize() { static GLFWInitializer initializer; }

private:
    bool Initialized = false;
};

GLContext::GLContext(GLFWwindow* InWindow) : Window(InWindow) {}

void GLContext::MakeCurrent() { glfwMakeContextCurrent(Window); }

void GLContext::SwapBuffers() { glfwSwapBuffers(Window); }

void GLContext::SetVSync(bool Enabled) { glfwSwapInterval(Enabled ? 1 : 0); }

GLFWWindow::GLFWWindow(const WindowContext& WindowContext) {
    GLFWInitializer::Initialize();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if (WindowContext.Samples > 1) {
        glfwWindowHint(GLFW_SAMPLES, WindowContext.Samples);
    }

    GLFWmonitor* monitor = WindowContext.Fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    Window = glfwCreateWindow(WindowContext.Width, WindowContext.Height,
                              WindowContext.Title.c_str(), monitor, nullptr);

    if (!Window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    Registry[Window] = this;

    Context = std::make_unique<GLContext>(Window);
    Context->MakeCurrent();

    auto GLLoader = [](const char* name) -> void* {
        return reinterpret_cast<void*>(glfwGetProcAddress(name));
    };
    if (!gladLoadGLLoader(GLLoader)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetFramebufferSizeCallback(Window, OnResize);
    glfwSetKeyCallback(Window, OnKeyEvent);
    glfwSetMouseButtonCallback(Window, OnMouseButtonEvent);
    glfwSetCursorPosCallback(Window, OnMoveCursorPos);

    Context->SetVSync(WindowContext.Vsync);

    glEnable(GL_DEPTH_TEST);

    int FbWidth, FbHeight;
    glfwGetFramebufferSize(Window, &FbWidth, &FbHeight);
    glViewport(0, 0, FbWidth, FbHeight);
}

GLFWWindow::~GLFWWindow() {
    if (Window) {
        Registry.erase(Window);
        glfwDestroyWindow(Window);
    }
}

void GLFWWindow::Show() { glfwShowWindow(Window); }

void GLFWWindow::Hide() { glfwHideWindow(Window); }

void GLFWWindow::Close() { glfwSetWindowShouldClose(Window, GLFW_TRUE); }

bool GLFWWindow::ShouldClose() const { return glfwWindowShouldClose(Window); }

void GLFWWindow::SetTitle(const std::string& Title) { glfwSetWindowTitle(Window, Title.c_str()); }

void GLFWWindow::SetSize(int Width, int Height) { glfwSetWindowSize(Window, Width, Height); }

void GLFWWindow::GetSize(int& Width, int& Height) const {
    glfwGetWindowSize(Window, &Width, &Height);
}

void GLFWWindow::GetFramebufferSize(int& Width, int& Height) const {
    glfwGetFramebufferSize(Window, &Width, &Height);
}

IGraphicsContext* GLFWWindow::GetGraphicsContext() const { return Context.get(); }

void GLFWWindow::SwapBuffers() { Context->SwapBuffers(); }

void GLFWWindow::PollEvents() { glfwPollEvents(); }

bool GLFWWindow::IsKeyPressed(int Key) const { return glfwGetKey(Window, Key) == GLFW_PRESS; }

void GLFWWindow::GetCursorPos(double& x, double& y) const { glfwGetCursorPos(Window, &x, &y); }

void GLFWWindow::SetResizeCallback(const IWindow::ResizeCallback& Callback) {
    ResizeCallback = Callback;
}

void GLFWWindow::SetKeyCallback(const IWindow::KeyCallback& Callback) { KeyCallback = Callback; }

void GLFWWindow::SetMouseButtonCallback(const IWindow::MouseButtonCallback& Callback) {
    MouseButtonCallback = Callback;
}

void GLFWWindow::SetCursorPosCallback(const IWindow::CursorPosCallback& Callback) {
    CursorPosCallback = Callback;
}

void GLFWWindow::OnResize(GLFWwindow* Window, int Width, int Height) {
    if (const auto It = Registry.find(Window); It != Registry.end() && It->second->ResizeCallback) {
        It->second->ResizeCallback(Width, Height);
    }
}

void GLFWWindow::OnKeyEvent(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods) {
    if (const auto It = Registry.find(Window); It != Registry.end() && It->second->KeyCallback) {
        It->second->KeyCallback(Key, Scancode, Action, Mods);
    }
}

void GLFWWindow::OnMouseButtonEvent(GLFWwindow* Window, int Button, int Action, int Mods) {
    if (const auto It = Registry.find(Window);
        It != Registry.end() && It->second->MouseButtonCallback) {
        It->second->MouseButtonCallback(Button, Action, Mods);
    }
}

void GLFWWindow::OnMoveCursorPos(GLFWwindow* Window, double XPos, double YPos) {
    if (const auto It = Registry.find(Window);
        It != Registry.end() && It->second->CursorPosCallback) {
        It->second->CursorPosCallback(XPos, YPos);
    }
}

std::unique_ptr<IWindow> Window::Create(const WindowContext& InWindowContext) {
    return std::make_unique<GLFWWindow>(InWindowContext);
}

} // namespace Volante