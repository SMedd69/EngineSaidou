#include <Utilities/ImGui_Test.h>

ImGUITest::ImGUITest(GLFWwindow* window, bool running) : m_window(window), m_running(running)
{
    Init();
}

void ImGUITest::Init()
{
    // Initialisation
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& iO = ImGui::GetIO(); (void)iO;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGUITest::Run(float customColor[4], Vector4 colorBackGround, float camPos[3], float camRot[3])
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Exemple d'interface utilisateur ImGui
    ImGui::Begin("Control Panel");
    ImGui::Text("Adjust the background color:");
    ImGui::ColorEdit4("Background Color", customColor);
    if (ImGui::Button("Reset Color")) {
        customColor[0] = Color::Orange().ToVector4().m_x;
        customColor[1] = Color::Orange().ToVector4().m_y;
        customColor[2] = Color::Orange().ToVector4().m_z;
        customColor[3] = Color::Orange().ToVector4().m_w;
    }
    ImGui::End();

    colorBackGround = Vector4(customColor[0], customColor[1], customColor[2], customColor[3]);
    glClearColor(colorBackGround.m_x, colorBackGround.m_y, colorBackGround.m_z, colorBackGround.m_w);
    ImGui::Begin("Inspector"); // Fenêtre des transformations
    ImGui::Text("Adjust the Transform Camera:");
    ImGui::DragFloat3("Position", camPos, 0.1f);  // On ajuste la position avec une petite sensibilité

    // Réinitialisation de la position de la caméra avec un bouton
    if (ImGui::Button("Reset Position Camera")) {
        camPos[0] = 0.0f;
        camPos[1] = 0.0f;
        camPos[2] = 0.0f;  // Réinitialiser la position à la valeur par défaut
    }
    ImGui::DragFloat3("Rotation", camRot, 0.1f);  // On ajuste la position avec une petite sensibilité

    // Réinitialisation de la position de la caméra avec un bouton
    if (ImGui::Button("Reset Rotation Camera")) {
        camRot[0] = 0.0f;
        camRot[1] = 0.0f;
        camRot[2] = -5.0f;  // Réinitialiser la position à la valeur par défaut
    }
    ImGui::End();

    ImGui::Begin("Info");
    ImGui::Text("Application running at %.1f FPS", ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Begin("Menu");
    ImGui::BeginPopupContextWindow("Pop Pup");
    ImGui::Text("Yooo");
    
    if(ImGui::Button("Quit"))
    {
        m_running = false;
    }

    ImGui::End();
}

void ImGUITest::SetRunning(bool running)
{
    m_running = running;
}

bool ImGUITest::GetRunning()const
{
    return m_running;
}

