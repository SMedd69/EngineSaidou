#include <Engine/Engine.h>
#include <Utilities/ImGui_Test.h>
#include <ImGUI/imgui.h>
#include <Engine/World.h>
#include <Engine/InputSystem.h>
#include <ctime>

Engine::Engine(bool running):
    m_Running(running)
{
    Run(m_Running);
}

void Engine::Run(bool running)
{
    Logger& logger = InitLogger();

    // Log du démarrage avec dessin
    PrintStartBanner();
    std::string titleWindow = "Engine Saidou : 0 fps";
    Window* window = new Window(1920, 1080, titleWindow);

    ImGUITest* imGuiTest = new ImGUITest(window->GetWindow());

    World* world = World::Instance();
    world->InitWorld();

    glEnable(GL_DEPTH_TEST);

    InputSystem* inputSystem = InputSystem::Instance();

    float cameraAngle = 0.0f;
    float stepLight = 1.0f;

    // Variables pour le calcul du FPS
    double lastTime = glfwGetTime();
    int frameCount = 0;

    // Dans la boucle principale, juste avant de dessiner
    while (!glfwWindowShouldClose(window->GetWindow()) && running)
    {
        double currentTime = glfwGetTime();
        frameCount++;

        // Mettre à jour le titre chaque seconde
        if (currentTime - lastTime >= 1.0)
        {
            int fps = frameCount;
            titleWindow = "Engine Saidou : " + std::to_string(fps) + " fps";
            glfwSetWindowTitle(window->GetWindow(), titleWindow.c_str());

            frameCount = 0;
            lastTime = currentTime;
        }

        glfwPollEvents();
        inputSystem->ProcessInput(window);

        // Démarrer une nouvelle frame ImGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Effacer l'écran
        glClearColor(0.3f, 0.3f, 0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world->Update();
        world->Display(window);

        glfwSwapBuffers(window->GetWindow());
    }

    #pragma region Destructors

    // Nettoyage ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete window;
    window = nullptr;

    glfwTerminate();

    // Log de l'arrêt avec dessin
    PrintStopBanner();

    // Ne pas oublier de fermer le fichier log à la fin
    logger.closeLogFile();

    #pragma endregion
}

#pragma region LOGGER
Logger& Engine::InitLogger()
{
    Logger& logger = Logger::getInstance();
    logger.setLogFile("./logs/log.txt");

    return logger;
}
void Engine::PrintStartBanner()
{
    // Afficher la date et l'heure dans la console
    time_t now = time(0);
    char* dt = ctime(&now);

    // Affichage dans la console (pas besoin de réinitialiser le fichier ici)
    Logger& logger = Logger::getInstance();
    logger.logWithoutFileAndLine("_____________________________\n", Logger::LogLevel::INFO);
    logger.logWithoutFileAndLine("    Program Starting...", Logger::LogLevel::SUCCESS);
    logger.logWithoutFileAndLine("    Start Time: " + std::string(dt), Logger::LogLevel::WARNING);
    logger.logWithoutFileAndLine("_____________________________\n", Logger::LogLevel::INFO);
}

void Engine::PrintStopBanner()
{
    // Afficher la date et l'heure dans la console
    time_t now =  time(0);
    char* dt = ctime(&now);


    // Affichage dans la console (pas besoin de réinitialiser le fichier ici)
    Logger& logger = Logger::getInstance();
    logger.logWithoutFileAndLine("_____________________________\n", Logger::LogLevel::INFO);
    logger.logWithoutFileAndLine("    Program Stopped", Logger::LogLevel::SUCCESS);
    logger.logWithoutFileAndLine("    End Time: " + std::string(dt), Logger::LogLevel::WARNING);
    logger.logWithoutFileAndLine("_____________________________\n", Logger::LogLevel::INFO);
}
#pragma endregion