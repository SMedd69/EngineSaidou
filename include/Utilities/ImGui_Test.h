#ifndef __IMGUI_TEST_H__
    #define __IMGUI_TEST_H__

    // #include <GLFW/glfw3.h>
    #include <Imgui/imgui.h>
    #include <Imgui/backends/imgui_impl_glfw.h>
    #include <Imgui/backends/imgui_impl_opengl3.h>
    #include <Utilities/ColorEngine.h>
    #include <vector>

    class ImGUITest
    {
    public:
        ImGUITest(GLFWwindow* window);
        void Init();
    private:
        GLFWwindow* m_window;
    };
#endif