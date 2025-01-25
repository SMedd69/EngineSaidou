#include <Engine/Engine.h>
#include <ctime>

Engine::Engine(bool running):
    m_Running(running)
{
    Run(m_Running);
}

int Engine::CreateCube(Vector3 position, Quaternion rotation, Vector3 scale, Mesh* mesh, Shader* shader, Material* material, Texture* texture, std::vector<Transform>& transforms, std::vector<MeshRenderer*>& meshRenderers)
{
	Transform cubeTransform = Transform(position, scale, rotation);
	MeshRenderer* cubeRenderer = new MeshRenderer(mesh, cubeTransform, shader, material, texture);
	transforms.push_back(cubeTransform);
	meshRenderers.push_back(cubeRenderer);

	return meshRenderers.size()-1;
}

void Engine::SetRotation(int index, Quaternion rotation, std::vector<MeshRenderer*> meshRenderers)
{
	Transform tr = meshRenderers[index]->GetTransform();
	tr.SetRotation(rotation);
	meshRenderers[index]->SetTransform(tr);
}

void Engine::SetPosition(int index, Vector3 position, std::vector<MeshRenderer*> meshRenderers)
{
	Transform tr = meshRenderers[index]->GetTransform();
	tr.SetPosition(position);
	meshRenderers[index]->SetTransform(tr);
}

Vector3 Engine::GetPosition(int index, std::vector<MeshRenderer*> meshRenderers)
{
	Transform tr = meshRenderers[index]->GetTransform();
	return tr.GetPosition();
}

Quaternion Engine::GetRotation(int index, std::vector<MeshRenderer*> meshRenderers)
{
	Transform tr = meshRenderers[index]->GetTransform();
	return tr.GetRotation();
}

void Engine::Run(bool running)
{
    Logger& logger = InitLogger();

    // Log du démarrage avec dessin
    PrintStartBanner();

    std::vector<Mesh*> meshes;
	std::vector<Transform> transforms;
	std::vector<MeshRenderer*> meshRenderers;
	std::vector<Texture*> textures;
	std::vector<Material*> materials;
	std::vector<Light*> lights;

    Window* window = new Window(780, 450, "OpenGL");

    ImGUITest* imGuiTest = new ImGUITest(window->GetWindow(), running);

    Vector4 colorBackGround = ColorEngine::Orange().ToVector4();
    float customColor[4] = { colorBackGround.m_x, colorBackGround.m_y, colorBackGround.m_z, colorBackGround.m_w};
    

    #pragma region ShadersAndCamera

    const char* vsFilename = "assets/shaders/BlinnPhongShader.vert";
    std::string vertexShaderSourceString = FileSystem::get_file_content(vsFilename);
    const char* vertexShaderSource = vertexShaderSourceString.c_str();

    const char* fsFilename = "assets/shaders/BlinnPhongShader.frag";
    std::string fragmentShaderSourceString = FileSystem::get_file_content(fsFilename);
    const char* fragmentShaderSource = fragmentShaderSourceString.c_str();

    Vector3 cameraPosition = Vector3(2.5f, 2.0f, -5.f);
    Vector3 cameraRotation = Vector3(0.f, 0.f, 0.f);
    
    Camera* camera = new Camera(cameraPosition, cameraRotation, 10, true, false);
    camera->SetFov(60);
    camera->SetFar(2000);
    Shader* shader = new Shader(vertexShaderSource, fragmentShaderSource);

    #pragma endregion

    #pragma region MESHES

    Texture* m_texture2 = new Texture("assets/textures/RedTiles/Red_Tiles_DIFF.jpg");
    m_texture2->SetAnisotropy(.5f);
    textures.push_back(m_texture2);
    Texture* m_texture = new Texture("assets/textures/Rock/Rock_DIFF.png");
    m_texture->SetAnisotropy(.5f);
    textures.push_back(m_texture);

    /* Mesh* cubeMesh = MeshUtilities::CreateCube(1.0f);
    Transform cubeTransform = Transform(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));
    MeshRenderer* cubeRenderer = new MeshRenderer(cubeMesh, cubeTransform, shader, m_texture, Vector2(1.0f, 1.0f), Vector2(0.0f, 0.0f));
    meshes.push_back(cubeMesh);
    transforms.push_back(cubeTransform);
    meshRenderers.push_back(cubeRenderer);

    Mesh* customUVCubeMesh = MeshUtilities::CreateCustomCuveUV(1.0f, MeshUtilities::CubeUVInfo());
    Transform cubeUVTransform = Transform(Vector3(0.0f, 2.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));
    MeshRenderer* cubeUVRenderer = new MeshRenderer(customUVCubeMesh, cubeUVTransform, shader, m_texture, Vector2(4.0f, 4.0f), Vector2(0.0f, 0.0f));
    meshes.push_back(customUVCubeMesh);
    transforms.push_back(cubeUVTransform);
    meshRenderers.push_back(cubeUVRenderer);

    // Créer un mesh de type Sphere
    Mesh* sphereMesh = MeshUtilities::CreateGeodesicSphere(1.0f, 0);
    Transform sphereTransform = Transform(Vector3(2.0f, 0.0f, 2.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));
    MeshRenderer* sphereRenderer = new MeshRenderer(sphereMesh, sphereTransform, shader, m_texture, Vector2(3.0f, 3.0f), Vector2(0.0f, 0.0f));
    meshes.push_back(sphereMesh);
    transforms.push_back(sphereTransform);
    meshRenderers.push_back(sphereRenderer);

    // Créer un mesh de type Plane
    Mesh* planeMesh = MeshUtilities::CreatePlane(800.0f);
    Transform planeTransform = Transform(Vector3(0.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));

    float tillingX = 100.f;
    float tillingY = 100.f;
    Vector2 tilling = Vector2(tillingX, tillingY);

    float offsetX = 0.0f;
    float offsetY = 0.0f;
    Vector2 offset = Vector2(offsetX, offsetY);
    MeshRenderer* planeRenderer = new MeshRenderer(planeMesh, planeTransform, shader, m_texture2, tilling, offset);
    meshes.push_back(planeMesh);
    transforms.push_back(planeTransform);
    meshRenderers.push_back(planeRenderer);

    // Créer un mesh de type UV Sphere
    Mesh* uvSphereMesh = MeshUtilities::CreateUVSphere(1.0f, 32, 32);
    Transform uvSphereTransform = Transform(Vector3(6.0f, 0.0f, 6.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));
    MeshRenderer* uvSphereRenderer = new MeshRenderer(uvSphereMesh, uvSphereTransform, shader, m_texture, Vector2(1.0f, 1.0f), Vector2(0.0f, 0.0f));
    meshes.push_back(uvSphereMesh);
    transforms.push_back(uvSphereTransform);
    meshRenderers.push_back(uvSphereRenderer);

    // Créer un mesh de type Cylinder
    Mesh* cylinderMesh = MeshUtilities::CreateCylinder(1.0f, 24, 2.0f);
    Transform cylinderTransform = Transform(Vector3(8.0f, 0.0f, 8.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));
    MeshRenderer* cylinderRenderer = new MeshRenderer(cylinderMesh, cylinderTransform, shader, m_texture, Vector2(1.0f, 1.0f), Vector2(0.0f, 0.0f));
    meshes.push_back(cylinderMesh);
    transforms.push_back(cylinderTransform);
    meshRenderers.push_back(cylinderRenderer);

    // Créer un mesh de type Cone
    Mesh* coneMesh = MeshUtilities::CreateCone(1.f, 0, 24, 2.0f);
    Transform coneTransform = Transform(Vector3(10.0f, 0.0f, 10.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));
    MeshRenderer* coneRenderer = new MeshRenderer(coneMesh, coneTransform, shader, m_texture, Vector2(1.0f, 1.0f), Vector2(0.0f, 0.0f));
    meshes.push_back(coneMesh);
    transforms.push_back(coneTransform);
    meshRenderers.push_back(coneRenderer);
    
    // Créer un mesh de type Capsule
    Mesh* capsuleMesh = MeshUtilities::CreateCapsule(.5f, 2.f, 24, 24);
    Transform capsuleTransform = Transform(Vector3(12.0f, 0.0f, 12.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));
    MeshRenderer* capsuleRenderer = new MeshRenderer(capsuleMesh, capsuleTransform, shader, m_texture, Vector2(1.0f, 1.0f), Vector2(0.0f, 0.0f));
    meshes.push_back(capsuleMesh);
    transforms.push_back(capsuleTransform);
    meshRenderers.push_back(capsuleRenderer); */

    Mesh* cubeMesh = MeshUtilities::CreateCube(1.0f);
    Transform cubeTransform = Transform();
    Vector3 positionCube{0.0f, .5f, 10.f};
    cubeTransform.SetPosition(positionCube);
    
    // Color ambientColor, Color diffuseColor, Color specularColor
    float ambientColor[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    float diffuseColor[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    float specularColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    Material* materialCube = new Material(m_texture, m_texture, m_texture, {ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]}, {diffuseColor[0], diffuseColor[1], diffuseColor[2], diffuseColor[3]}, {specularColor[0], specularColor[1], specularColor[2], specularColor[3]});
    MeshRenderer* meshCube = new MeshRenderer(cubeMesh, cubeTransform, shader, materialCube, m_texture2);

    meshes.push_back(cubeMesh);
    transforms.push_back(cubeTransform);
    meshRenderers.push_back(meshCube);

    DirectionalLight* directionalLight = new DirectionalLight();
    LightingSettings* lightSett = new LightingSettings();

    float lightIntensity;

    #pragma endregion

    // Variables pour la gestion de la caméra
    Vector3 cameraRelativePosition = Vector3(0.0f,0.0f,-5.0f);
    float* camPos = new float[3] {cameraRelativePosition.m_x, cameraRelativePosition.m_y, cameraRelativePosition.m_z};
    float* camRot = new float[3] {0, 0, 0};

    glEnable(GL_DEPTH_TEST);

    // Dans la boucle principale, juste avant de dessiner
    while (!glfwWindowShouldClose(window->GetWindow()) && running)
    {
        // Effacer l'écran
        glClearColor(colorBackGround.m_x, colorBackGround.m_y, colorBackGround.m_z, colorBackGround.m_w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        imGuiTest->Run(customColor, colorBackGround, camPos, camRot, window->GetWidth(), window->GetHeight(), &lightIntensity, ambientColor, diffuseColor, specularColor);
        running = imGuiTest->GetRunning();

        // Effacer l'écran avec la nouvelle couleur de fond

        // glClearColor(colorBackGround.m_x, colorBackGround.m_y, colorBackGround.m_z, colorBackGround.m_w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dessiner les objets
        for (int i = 0; i < meshRenderers.size(); i++)
        {
            meshRenderers[i]->Draw(camera, lights, window);
        }

        directionalLight->SetIntensity(lightIntensity);
        std::cout << "Intensity: " << directionalLight->m_intensity << std::endl;
        materialCube->SetAmbientColor({ambientColor[0], ambientColor[1], ambientColor[2], ambientColor[3]});
        materialCube->SetDiffuseColor({diffuseColor[0], diffuseColor[1], diffuseColor[2], diffuseColor[3]});
        materialCube->SetSpecularColor({specularColor[0], specularColor[1], specularColor[2], specularColor[3]});

        // Rotation de la caméra en mode FPS (First Person Shooter)
        camera->SetPosition(Vector3(camPos[0], camPos[1], camPos[2])); // Appliquer la nouvelle position directement
        camera->SetAngle(Vector3(camRot[0], camRot[1], camRot[2])); // Appliquer la nouvelle position directement

        // Rendu ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Échanger les buffers
        glfwSwapBuffers(window->GetWindow());
    }

    #pragma region Destructors

    // Nettoyage ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Libérer les ressources
    for (int i = 0; i < meshes.size(); i++)
    {
        delete meshes[i];
        meshes[i] = nullptr;
    }

    for (int i = 0; i < meshRenderers.size(); i++)
    {
        delete meshRenderers[i];
        meshRenderers[i] = nullptr;
    }

    meshes.clear();
    meshRenderers.clear();
    transforms.clear();

    delete camera;
    camera = nullptr;
    delete shader;
    shader = nullptr;
    delete m_texture;
    m_texture = nullptr;
    delete m_texture2;
    m_texture2 = nullptr;
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