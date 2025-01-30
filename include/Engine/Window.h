#ifndef __WINDOW_H__
    #define __WINDOW_H__
    
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>
    #include <iostream>
    #include <string>

    #include <Utilities/Logger.h>
    #include <Engine/InputSystem.h>
    
    class Window
    {
        public:        
        Window(int width, int height, const std::string& title);
        Window(int width, int height, const std::string& title, int glMajorVersion, int glMinorVersion);

        GLFWwindow* GetWindow() const;
        float GetWidth() const;
        float GetHeight() const;

        void RefreshWidthAndHeight();
        static void SetTheFrameBufferSize(GLFWwindow* window, int width, int height);

        static InputCode ConvertGLFWInputKeyCode(int keyCode);

        static InputCode ConvertGLFWInputMouseCode(int mouseInput);
        static float ConvertGLFWInputAction(int action);

        void LockMouseInput(bool lock);
        float lastPositionX = 0.0f;
        float lastPositionY = 0.0f;

        private:
        int m_glMajorVersion = GLVersion.major;
        int m_glMinorVersion = GLVersion.minor;

        int m_width = 1280;
        int m_height = 720;
        std::string m_title =  "New Window";
        
        GLFWwindow* m_window;
        int InitializeGLFW();
        int CreateWindowGLFW();
        int InitializeGlad();

        void InitialiseGLFWCallback();
        
    };
#endif