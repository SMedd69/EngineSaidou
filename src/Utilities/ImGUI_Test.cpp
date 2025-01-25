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

void ImGUITest::Run(float customColor[4], Vector4 colorBackGround, float camPos[3], float camRot[3], float windowWidth, float windowHeight)
{
    // Récupère la taille de la fenêtre depuis la classe Window
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Fenêtre "Control Panel"
    ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.5f, windowHeight * 0.3f), ImGuiCond_Always);  // 50% de la largeur, 30% de la hauteur
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

    // Mise à jour de la couleur de fond
    colorBackGround = Vector4(customColor[0], customColor[1], customColor[2], customColor[3]);
    glClearColor(colorBackGround.m_x, colorBackGround.m_y, colorBackGround.m_z, colorBackGround.m_w);

    // Fenêtre "Inspector" (ajuste sa taille en fonction de la fenêtre OpenGL)
    ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.3f, windowHeight * 0.5f), ImGuiCond_Always);  // 30% de la largeur, 50% de la hauteur
    ImGui::Begin("Inspector");
    ImGui::Text("Adjust the Transform Camera:");
    ImGui::DragFloat3("Position", camPos, 0.1f);  // Ajuste la position avec une petite sensibilité

    // Réinitialisation de la position de la caméra avec un bouton
    if (ImGui::Button("Reset Position Camera")) {
        camPos[0] = 0.0f;
        camPos[1] = 0.0f;
        camPos[2] = 0.0f;
    }
    ImGui::DragFloat3("Rotation", camRot, 0.1f);  // Ajuste la position avec une petite sensibilité

    // Réinitialisation de la rotation de la caméra avec un bouton
    if (ImGui::Button("Reset Rotation Camera")) {
        camRot[0] = 0.0f;
        camRot[1] = 0.0f;
        camRot[2] = -5.0f;
    }
    ImGui::End();

    // Fenêtre "Info"
    ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.2f, windowHeight * 0.2f), ImGuiCond_Always);  // 20% de la largeur et hauteur
    ImGui::Begin("Info");
    ImGui::Text("Application running at %.1f FPS", ImGui::GetIO().Framerate);
    ImGui::End();

    // Fenêtre "Menu"
    ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.2f, windowHeight * 0.3f), ImGuiCond_Always);  // 20% de la largeur et 30% de la hauteur
    ImGui::Begin("Menu");
    ImGui::BeginPopupContextWindow("Pop Up");
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

