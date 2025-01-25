#ifndef __IMGUI_TEST_H__
    #define __IMGUI_TEST_H__

    #include <GLFW/glfw3.h>
    #include <Imgui/imgui.h>
    #include <Imgui/backends/imgui_impl_glfw.h>
    #include <Imgui/backends/imgui_impl_opengl3.h>
    #include <Utilities/Color.h>
    #include <vector>

    class ImGUITest
    {
    public:
        ImGUITest(GLFWwindow* window, bool running);
        void Init();
        void Run(float customColor[4], Vector4 colorBackGround, float camPos[3], float camRot[3], float windowWidth, float windowHeight);

        void SetRunning(bool running);
        bool GetRunning()const;
    private:
        GLFWwindow* m_window;
        bool m_running;
    };
#endif