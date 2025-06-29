#include "GLFWWindow.h"

#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "GLFWKeyMapper.h"

namespace Volante
{

//================================================================
// GLFWInitializer
//================================================================
class GLFWInitializer
{
public:
    GLFWInitializer()
    {
        if (glfwInit() == GLFW_FALSE)
        {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        Initialized = true;
    }

    ~GLFWInitializer()
    {
        if (Initialized)
        {
            glfwTerminate();
        }
    }

    static void Initialize()
    {
        static GLFWInitializer initializer;
    }

private:
    bool Initialized = false;
};

//================================================================
// GLFWContext
//================================================================
GLFWContext::GLFWContext(GLFWwindow* window) : window_(window)
{
}

void GLFWContext::MakeCurrent()
{
    glfwMakeContextCurrent(window_);
}

void GLFWContext::SwapBuffers()
{
    glfwSwapBuffers(window_);
}

void GLFWContext::SetVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
}

//================================================================
// GLFWWindow
//================================================================
std::unordered_map<GLFWwindow*, GLFWWindow*> GLFWWindow::Registry;

GLFWWindow::GLFWWindow(const WindowDesc& windowDesc)
{
    GLFWInitializer::Initialize();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if (windowDesc.samples > 1)
    {
        glfwWindowHint(GLFW_SAMPLES, windowDesc.samples);
    }

    GLFWmonitor* monitor = windowDesc.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
    Window = glfwCreateWindow(windowDesc.width, windowDesc.height,
                              windowDesc.title.c_str(), monitor, nullptr);

    if (!Window)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    Registry[Window] = this;

    Context = std::make_unique<GLFWContext>(Window);
    Context->MakeCurrent();

    auto GLLoader = [](const char* name) -> void* {
        return reinterpret_cast<void*>(glfwGetProcAddress(name));
    };
    if (!gladLoadGLLoader(GLLoader))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetFramebufferSizeCallback(Window, GLFWResizeCallback);
    glfwSetKeyCallback(Window, GLFWKeyCallback);
    glfwSetMouseButtonCallback(Window, GLFWMouseButtonCallback);
    glfwSetCursorPosCallback(Window, GLFWCursorPosCallback);

    Context->SetVSync(windowDesc.vsync);

    glEnable(GL_DEPTH_TEST);

    int FbWidth, FbHeight;
    glfwGetFramebufferSize(Window, &FbWidth, &FbHeight);
    glViewport(0, 0, FbWidth, FbHeight);
}

GLFWWindow::~GLFWWindow()
{
    if (Window)
    {
        Registry.erase(Window);
        glfwDestroyWindow(Window);
    }
}

void GLFWWindow::Show()
{
    glfwShowWindow(Window);
}

void GLFWWindow::Hide()
{
    glfwHideWindow(Window);
}

void GLFWWindow::Close()
{
    glfwSetWindowShouldClose(Window, GLFW_TRUE);
}

bool GLFWWindow::ShouldClose() const
{
    return glfwWindowShouldClose(Window);
}

void GLFWWindow::SetTitle(const std::string& Title)
{
    glfwSetWindowTitle(Window, Title.c_str());
}

void GLFWWindow::SetSize(int Width, int Height)
{
    glfwSetWindowSize(Window, Width, Height);
}

void GLFWWindow::GetSize(int& Width, int& Height) const
{
    glfwGetWindowSize(Window, &Width, &Height);
}

void GLFWWindow::GetFramebufferSize(int& Width, int& Height) const
{
    glfwGetFramebufferSize(Window, &Width, &Height);
}

void* GLFWWindow::GetNativeHandle() const
{
    return Window;
}

IGraphicsContext* GLFWWindow::GetGraphicsContext() const
{
    return Context.get();
}

void GLFWWindow::SwapBuffers()
{
    Context->SwapBuffers();
}

void GLFWWindow::PollEvents()
{
    glfwPollEvents();
}

bool GLFWWindow::IsKeyPressed(KeyCode key) const
{
    return glfwGetKey(Window, GLFWKeyMapper::ToGLFWKey(key)) == GLFW_PRESS;
}

void GLFWWindow::GetCursorPos(double& x, double& y) const
{
    glfwGetCursorPos(Window, &x, &y);
}

void GLFWWindow::SetResizeCallback(const ResizeCallback& callback)
{
    resizeCallback_ = callback;
}

void GLFWWindow::SetKeyCallback(const KeyCallback& callback)
{
    keyCallback_ = callback;
}

void GLFWWindow::SetMouseButtonCallback(const MouseButtonCallback& callback)
{
    mouseButtonCallback_ = callback;
}

void GLFWWindow::SetCursorPosCallback(const CursorPosCallback& callback)
{
    cursorPosCallback_ = callback;
}

void GLFWWindow::GLFWResizeCallback(GLFWwindow* window, int width, int height)
{
    if (const auto It = Registry.find(window); It != Registry.end() && It->second->resizeCallback_)
    {
        It->second->resizeCallback_(width, height);
    }
}

void GLFWWindow::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (const auto It = Registry.find(window); It != Registry.end() && It->second->keyCallback_)
    {
        It->second->keyCallback_(GLFWKeyMapper::FromGLFWKey(key), GLFWKeyMapper::FromGLFWAction(action));
    }
}

void GLFWWindow::GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (const auto It = Registry.find(window);
        It != Registry.end() && It->second->mouseButtonCallback_)
    {
        It->second->mouseButtonCallback_(GLFWKeyMapper::FromGLFWButton(button), GLFWKeyMapper::FromGLFWAction(action));
    }
}

void GLFWWindow::GLFWCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (const auto It = Registry.find(window);
        It != Registry.end() && It->second->cursorPosCallback_)
    {
        It->second->cursorPosCallback_(xpos, ypos);
    }
}

std::unique_ptr<IWindow> Window::Create(const WindowDesc& windowDesc)
{
    return std::make_unique<GLFWWindow>(windowDesc);
}

} // namespace Volante