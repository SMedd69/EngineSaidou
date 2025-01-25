#include <Engine/Window.h>

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title)
{
    InitializeGLFW();
    CreateWindowGLFW();
    InitializeGlad();

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, SetTheFrameBufferSize);
}

void Window::SetTheFrameBufferSize(GLFWwindow* window, int width, int height)
{
    Window* win = (Window*)glfwGetWindowUserPointer(window);
    win->RefreshWidthAndHeight();
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const std::string& title, int glMajorVersion, int glMinorVersion)
    : m_width(width), m_height(height), m_title(title), m_glMajorVersion(glMajorVersion), m_glMinorVersion(glMinorVersion)
{
    InitializeGLFW();
    CreateWindowGLFW();
    InitializeGlad();
}

int Window::InitializeGLFW()
{
    int resultGLFW = glfwInit();

    if(resultGLFW == GLFW_FALSE)
    {
        Logger::getInstance().log("GLFW not Initialized.", Logger::LogLevel::ERR, __FILE__, __LINE__);
        return -1;
    } else if(resultGLFW == GLFW_TRUE)
    {
        Logger::getInstance().log("GLFW is Initialized.", Logger::LogLevel::SUCCESS, __FILE__, __LINE__);
    }

    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, m_glMajorVersion);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, m_glMinorVersion);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 1;
}

int Window::InitializeGlad()
{
    int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if(!result)
    {
        Logger::getInstance().log("Failed to initialize GLAD.", Logger::LogLevel::ERR, __FILE__, __LINE__);
        return -1;
    }
    else if(result)
    {
        Logger::getInstance().log("GLAD Initialized.", Logger::LogLevel::SUCCESS, __FILE__, __LINE__);
    }

    return 1;
}

int Window::CreateWindowGLFW()
{
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

    if(!m_window)
    {
        Logger::getInstance().log("Window Not Created.", Logger::LogLevel::ERR, __FILE__, __LINE__);
        glfwTerminate();
        return -1;
    } else
    {
        Logger::getInstance().log("Window Created.", Logger::LogLevel::SUCCESS, __FILE__, __LINE__);
    }

    glfwMakeContextCurrent(m_window);
    return 1;
}

GLFWwindow* Window::GetWindow() const
{
    return m_window;
}
float Window::GetWidth() const
{
    return m_width;
}
float Window::GetHeight() const
{
    return m_height;
}

void Window::RefreshWidthAndHeight()
{
    glfwGetWindowSize(m_window, &m_width, &m_height);
}