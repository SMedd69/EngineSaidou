#include <Engine/Window.h>

Window::Window(int width, int height, const std::string& title)
    : m_width(width), m_height(height), m_title(title)
{
    InitializeGLFW();
    CreateWindowGLFW();
    InitializeGlad();

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, SetTheFrameBufferSize);

    if (glfwRawMouseMotionSupported())
		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	InitialiseGLFWCallback();
}

void Window::InitialiseGLFWCallback()
{
	///TODO : use mods and handle special characters (-""...) using glfwSetCharCallback, check keyboard language, azerty, qwerty
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			InputSystem* inputSystem = InputSystem::Instance();

            std::cout << "Key: " << key << std::endl;
			if (action == GLFW_PRESS || action == GLFW_RELEASE)
            {
				inputSystem->RegisterInput(win, ConvertGLFWInputKeyCode(key), ConvertGLFWInputAction(action));
            }
		});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int mouseButton, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			InputSystem* inputSystem = InputSystem::Instance();
            std::cout << "Mouse Button: " << mouseButton << std::endl;

			if (action == GLFW_PRESS || action == GLFW_RELEASE)
				inputSystem->RegisterInput(win, ConvertGLFWInputMouseCode(mouseButton), ConvertGLFWInputAction(action));
		});

	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			InputSystem* inputSystem = InputSystem::Instance();
            std::cout << "Scroll X: " << xoffset << std::endl;
            std::cout << "Scroll Y: " << yoffset << std::endl;
			if (inputSystem->GetInputState(InputCode::E_MOUSE_SCROLL_X) != (float)xoffset)
				inputSystem->RegisterInput(win, InputCode::E_MOUSE_SCROLL_X, xoffset);

			if (inputSystem->GetInputState(InputCode::E_MOUSE_SCROLL_Y) != (float)yoffset)
				inputSystem->RegisterInput(win, InputCode::E_MOUSE_SCROLL_Y, yoffset);
		});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			InputSystem* inputSystem = InputSystem::Instance();

            std::cout << "Cursor X: " << xpos << std::endl;
            std::cout << "Cursor Y: " << ypos << std::endl;
			if (inputSystem->GetInputState(InputCode::E_MOUSE_POS_X) != (float)xpos)
				inputSystem->RegisterInput(win, InputCode::E_MOUSE_POS_X, xpos);

			if (inputSystem->GetInputState(InputCode::E_MOUSE_POS_Y) != (float)ypos)
				inputSystem->RegisterInput(win, InputCode::E_MOUSE_POS_Y, ypos);
		});
}

void Window::LockMouseInput(bool lock)
{
	if (lock)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

InputCode Window::ConvertGLFWInputKeyCode(int keyCode)
{	
	return (InputCode)keyCode;
}

InputCode Window::ConvertGLFWInputMouseCode(int mouseInput)
{
	if (mouseInput == 0)
		return InputCode::E_MOUSE_BUTTON_1;
	else if (mouseInput == 1)
		return InputCode::E_MOUSE_BUTTON_2;
	else if (mouseInput == 2)
		return InputCode::E_MOUSE_BUTTON_3;
	else if (mouseInput == 3)
		return InputCode::E_MOUSE_BUTTON_4;
	else if (mouseInput == 4)
		return InputCode::E_MOUSE_BUTTON_5;
	else if (mouseInput == 5)
		return InputCode::E_MOUSE_BUTTON_6;
	else if (mouseInput == 6)
		return InputCode::E_MOUSE_BUTTON_7;
	else if (mouseInput == 7)
		return InputCode::E_MOUSE_BUTTON_8;

	return InputCode::E_UNKNOWN;
}

float Window::ConvertGLFWInputAction(int action)
{
	if (action == GLFW_PRESS)
		return 1.0f;
	else if (action == GLFW_RELEASE)
		return 0.0f;
	else if(action == GLFW_REPEAT)
		return 0.0f;
	else
		return 0.0f;
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