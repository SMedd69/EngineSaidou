#include <Utilities/ImGui_Test.h>
#include <Utilities/MeshUtilities.h>
#include <Engine/AssetsManager.h>
#include <Engine/World.h>
#include <Engine/DirectionalLight.h>
#include <Engine/PointLight.h>
#include <Engine/SpotLight.h>
#include <Math/Mathf.h>

ImGUITest::ImGUITest(GLFWwindow* window)
    : m_window(window)
{
    Init();
}

void ImGUITest::Init()
{
    // Initialisation d'ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

// ----------------------- World UI Rendering -----------------------

void World::RenderUiGui()
{

    // Fenêtre pour créer des entités
    ImGui::Begin("Create Cube");
    if (ImGui::Button("Create Cube##CreateCube"))
    {
        CreateMeshCube(MeshUtilities::CreateCube("New Cube", 1.0f), "New Cube");  // Crée une nouvelle entité de type Cube
    }
    ImGui::End();

    ImGui::Begin("Create Sphere");
    if (ImGui::Button("Create Sphere##CreateSphere"))
    {
        CreateMeshCube(MeshUtilities::CreateUVSphere("New Sphere", 1.0f, 24, 24), "New Sphere");  // Crée une nouvelle entité de type Sphere
    }
    ImGui::End();

    ImGui::Begin("Create GeodesicSphere");
    if (ImGui::Button("Create GeodesicSphere##GeodesicSphere"))
    {
        CreateMeshCube(MeshUtilities::CreateGeodesicSphere("New GeodesicSphere", 1.0f, 3), "New GeodesicSphere");  // Crée une nouvelle entité de type GeodesicSphere
    }
    ImGui::End();

    ImGui::Begin("Create Plane");
    if (ImGui::Button("Create Plane##CreatePlane"))
    {
        CreateMeshCube(MeshUtilities::CreatePlane("New Plane", 1.0f), "New Plane");  // Crée une nouvelle entité de type Plane
    }
    ImGui::End();
    
    ImGui::Begin("Create Cone");
    if (ImGui::Button("Create Cone##CreateCone"))
    {
        CreateMeshCube(MeshUtilities::CreateCone("New Cone", 1.0f, 0.0f, 24, 2.0f), "New Cone");  // Crée une nouvelle entité de type Cone
    }
    ImGui::End();
    
    ImGui::Begin("Create Prism");
    if (ImGui::Button("Create Prism##CreatePrism"))
    {
        CreateMeshCube(MeshUtilities::CreatePrism("New Prism", 5.0f, 64), "New Prism");  // Crée une nouvelle entité de type Prism
    }
    ImGui::End();
    
    ImGui::Begin("Create Pyramid");
    if (ImGui::Button("Create Pyramid##CreatePyramid"))
    {
        CreateMeshCube(MeshUtilities::CreatePyramid("New Pyramid", 1.0f), "New Pyramid");  // Crée une nouvelle entité de type Pyramid
    }
    ImGui::End();
    
    ImGui::Begin("Create Torus");
    if (ImGui::Button("Create Torus##CreateTorus"))
    {
        CreateMeshCube(MeshUtilities::CreateTorus("New Torus", 1.0f, 1.0f, 24, 24), "New Torus");  // Crée une nouvelle entité de type Torus
    }
    ImGui::End();
    
    ImGui::Begin("Create Stair");
    if (ImGui::Button("Create Stair##CreateStair"))
    {
        CreateMeshCube(MeshUtilities::CreateStaircase("New Stair", 1.0f, 3.0f, 24, 24), "New Stair");  // Crée une nouvelle entité de type Stair
    }
    ImGui::End();
    
    ImGui::Begin("Create Capsule");
    if (ImGui::Button("Create Capsule##CreateCapsule"))
    {
        CreateMeshCube(MeshUtilities::CreateCapsule("New Capsule", 1.0f, 2.0f, 24, 24), "New Capsule");  // Crée une nouvelle entité de type Capsule
    }
    ImGui::End();

    ImGui::Begin("Create Water");
    if (ImGui::Button("Create Water##CreateWater"))
    {
        CreateMeshCube(MeshUtilities::CreateWaterMesh("New Water Mesh", 1, 1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.1f), "New Water");  // Crée une nouvelle entité de type Water
    }
    ImGui::End();
    
    ImGui::Begin("Create Terrain Procedural");
    if (ImGui::Button("Create Terrain Procedural##CreateTerrainProcedural"))
    {
        CreateMeshCube(MeshUtilities::CreateProceduralTerrain("New Terrain Procedural", 1, 1, 1, 1, 1, 1), "New Terrain Procedural");  // Crée une nouvelle entité de type Terrain Procedural
    }
    ImGui::End();
    
    ImGui::Begin("Create Camera");
    if (ImGui::Button("Create Camera##CreateCamera"))
    {
        // Initialiser la caméra
        Vector3 cameraPosition = Vector3(0.0f, 0.5f, -10.8f);
        Vector3 cameraAngles = Vector3(0.0f, 0.0f, 0.0f);
        
        std::string nameEntityCamera = "Camera";

        Entity* cameraEntity = CreateEntity<Entity>();
        {
            cameraEntity->SetNameEntity(nameEntityCamera);
            Camera* cameraComponent = cameraEntity->AddComponent<Camera>();
            if (!cameraComponent)
            {
                std::cerr << "Failed to create Camera Component" << std::endl;
                return;
            }
            cameraComponent->SetPosition(cameraPosition);
            cameraComponent->SetAngle(cameraAngles);
            cameraComponent->SetProjectionMode(Camera::EProjectionMode::PERSPECTIVE);
            cameraComponent->SetFov(60.0f);
        }
    }
    ImGui::End();
    
    ImGui::Begin("Create Directional Light");
    if (ImGui::Button("Create Directional Light##DirectionalLight"))
    {   
        std::string nameEntityCamera = "Directional Light";

        Entity* cameraEntity = CreateEntity<Entity>();
        {
            cameraEntity->SetNameEntity(nameEntityCamera);
            Transform* transform = cameraEntity->AddComponent<Transform>();
            if (!transform)
            {
                std::cerr << "Failed to create Transform Component" << std::endl;
                return;
            }
            transform->SetPosition({0, 0, 0});
            transform->SetScale({1, 1, 1});
            transform->SetRotation(Quaternion::Identity());

            DirectionalLight* directionalLight = cameraEntity->AddComponent<DirectionalLight>();
            if (!directionalLight)
            {
                std::cerr << "Failed to create Camera Component" << std::endl;
                return;
            }
            directionalLight->SetTypeLight(Light::LightType::Directional);
        }
    }
    ImGui::End();
    
    ImGui::Begin("Create Point Light");
    if (ImGui::Button("Create Point Light##PointLight"))
    {   
        std::string nameEntityCamera = "Point Light";

        Entity* cameraEntity = CreateEntity<Entity>();
        {
            cameraEntity->SetNameEntity(nameEntityCamera);
            Transform* transform = cameraEntity->AddComponent<Transform>();
            if (!transform)
            {
                std::cerr << "Failed to create Transform Component" << std::endl;
                return;
            }
            transform->SetPosition({0, 0, 0});
            transform->SetScale({1, 1, 1});
            transform->SetRotation(Quaternion::Identity());

            PointLight* pointLight = cameraEntity->AddComponent<PointLight>();
            if (!pointLight)
            {
                std::cerr << "Failed to create Camera Component" << std::endl;
                return;
            }
            pointLight->SetTypeLight(Light::LightType::Point);
        }
    }
    ImGui::End();
    
    ImGui::Begin("Create Spot Light");
    if (ImGui::Button("Create Spot Light##SpotLight"))
    {   
        std::string nameEntityCamera = "Spot Light";

        Entity* cameraEntity = CreateEntity<Entity>();
        {
            cameraEntity->SetNameEntity(nameEntityCamera);
            Transform* transform = cameraEntity->AddComponent<Transform>();
            if (!transform)
            {
                std::cerr << "Failed to create Transform Component" << std::endl;
                return;
            }
            transform->SetPosition({0, 0, 0});
            transform->SetScale({1, 1, 1});
            transform->SetRotation(Quaternion::Identity());

            SpotLight* spotLight = cameraEntity->AddComponent<SpotLight>();
            if (!spotLight)
            {
                std::cerr << "Failed to create Camera Component" << std::endl;
                return;
            }
            spotLight->SetTypeLight(Light::LightType::Spot);
        }
    }
    ImGui::End();

    // Affiche les composants de chaque entité
    RenderComponentsUI();
}

// ----------------------- Création d'une entité Cube -----------------------

void World::CreateMeshCube(Mesh* meshObj, std::string nameEntity)
{
    // Position, rotation et échelle par défaut du cube
    // Vector3 cubePosition(0.0f, 0.0f, 5.0f);
    // Vector3 cubeScale(1.0f, 1.0f, 1.0f);
    // Quaternion cubeRotation = Quaternion::Identity();

    // Crée une nouvelle entité pour le cube
    Entity* cubeEntity = CreateEntity<Entity>();
    if (!cubeEntity)
    {
        std::cerr << "Failed to create Cube Entity." << std::endl;
        return;
    }

    cubeEntity->SetNameEntity(nameEntity);

    // Ajout et configuration du Transform
    Transform* transformComponent = cubeEntity->AddComponent<Transform>();
    if (!transformComponent)
    {
        std::cerr << "Failed to create Transform Component for Cube." << std::endl;
        return;
    }
    else
    std::cout << "Success to create Transform Component for Cube." << std::endl;

    // transformComponent->SetPosition(cubePosition);
    // transformComponent->SetScale(cubeScale);
    // transformComponent->SetRotation(cubeRotation);

    // Ajout et configuration du MeshRenderer
    MeshRenderer* meshRenderer = cubeEntity->AddComponent<MeshRenderer>();
    if (!meshRenderer)
    {
        std::cerr << "Failed to create MeshRenderer Component for Cube." << std::endl;
        return;
    }

    // Configure le MeshRenderer avec des ressources
    Mesh* cubeMesh = meshObj;
    Shader* shader = AssetsManager::GetAsset<Shader>("BlinnPhongShader");
    Material* material = AssetsManager::GetAsset<Material>("Material0");

    if (!cubeMesh || !shader || !material)
    {
        std::cerr << "Missing resources for CubeMesh." << std::endl;
        return;
    }

    meshRenderer->SetMesh(cubeMesh);
    meshRenderer->SetShader(shader);
    meshRenderer->SetMaterial(material);
    meshRenderer->SetTransform(transformComponent);
    m_entities.insert(cubeEntity);

    for (Entity* e : m_entities)
    {
        std::cout << "Entity in world: " << e->GetName() << std::endl;
    }

    // Initialisation de l'entité
    cubeEntity->Start();
}

// ----------------------- Affichage et gestion des entités -----------------------

void World::RenderComponentsUI()
{
    // Fenêtre principale pour afficher les entités et leurs composants
    ImGui::Begin("Scene Components");

    // Vérifie si des entités sont disponibles
    if (m_entities.empty())
    {
        ImGui::Text("No entities in the scene.");
        ImGui::End();
        return;
    }

    // Parcourt toutes les entités
    for (Entity* entity : m_entities)
    {
        // Crée un ID basé sur l'adresse de l'entité pour éviter les conflits
        ImGui::PushID(entity);

        // Titre collapsible pour chaque entité
        if (ImGui::CollapsingHeader((entity->GetName() + "##" + std::to_string(reinterpret_cast<std::uintptr_t>(entity))).c_str()))
        {
            // Buffer de nom propre à chaque entité
            std::string entityName = entity->GetName();
            char nameBuffer[256];
            strncpy(nameBuffer, entityName.c_str(), sizeof(nameBuffer));
            nameBuffer[sizeof(nameBuffer) - 1] = '\0'; // Assurer la terminaison correcte

            if (ImGui::InputText(("Name##" + std::to_string(reinterpret_cast<std::uintptr_t>(entity))).c_str(),
                                nameBuffer, sizeof(nameBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
            {
                entity->SetNameEntity(std::string(nameBuffer));
            }

            // Affichage des composants de l'entité
            std::vector<Component*> components = entity->GetAllComponents();

            if (components.empty())
            {
                ImGui::Text("No components for this entity.");
            }
            else
            {
                for (size_t i = 0; i < components.size(); ++i)
                {
                    Component* component = components[i];

                    // ID basé sur l'adresse de l'entité et l'indice du composant
                    ImGui::PushID((void*)((uintptr_t)entity + i));

                    if (Transform* transform = dynamic_cast<Transform*>(component))
                    {
                        ImGui::Text("Transform:");
                        Vector3 position = transform->GetPosition();
                        Vector3 scale = transform->GetScale();
                        Quaternion rotation = transform->GetRotation();

                        ImGui::DragFloat3(("Position##TransformPosition_" + std::to_string(i)).c_str(), &position.m_x, 0.1f);
                        ImGui::DragFloat3(("Scale##TransformScale_" + std::to_string(i)).c_str(), &scale.m_x, 0.1f);
                        ImGui::DragFloat3(("Rotation##TransformRotation_" + std::to_string(i)).c_str(), &rotation.m_x, 0.1f);


                        transform->SetPosition(position);
                        transform->SetScale(scale);
                        transform->SetEulerAngles({rotation.m_x, rotation.m_y, rotation.m_z});
                    }
                    else if (Camera* camera = dynamic_cast<Camera*>(component))
                    {
                        ImGui::Text("Camera:");
                        Vector3 position = camera->GetPosition();
                        Vector3 angles = camera->GetAngle();

                        float _near = camera->GetNear();
                        float _far = camera->GetFar();
                        float _fov = camera->GetFov();

                        ImGui::DragFloat3("Position##CameraPosition", &position.m_x, 0.1f);
                        ImGui::DragFloat3("Rotation##CameraRotation", &angles.m_x, 0.1f);
                        ImGui::DragFloat("FieldOfView##CameraFov", &_fov, 0.1f);
                        ImGui::DragFloat("Near##CameraNear", &_near, 0.1f);
                        ImGui::DragFloat("Far##CameraFar", &_far, 0.1f);

                        camera->SetPosition(position);
                        camera->SetAngle(angles);
                        camera->SetFov(_fov);
                        camera->SetNear(_near);
                        camera->SetFar(_far);
                    }
                    /* else if (Light* light = dynamic_cast<Light*>(component))
                    {
                        ImGui::Text("Light:");
                        const char* lightTypeNames[] = {"Directional", "Point", "Spot"};

                        int currentItem  = static_cast<int>(light->m_lightType);
                        if(ImGui::Combo(("Light Type" + std::to_string(i)).c_str(), &currentItem, lightTypeNames, IM_ARRAYSIZE(lightTypeNames)))
                        {
                            Light::LightType o = static_cast<Light::LightType>(currentItem);
                            light->SetTypeLight(o);
                        }
                        ImGui::ColorEdit4(("Ambient Color##LightAmbientColor_" + std::to_string(i)).c_str(), &light->m_ambiantColor.m_r);
                        ImGui::ColorEdit4(("Specular Color##LightSpecularColor_" + std::to_string(i)).c_str(), &light->m_specularColor.m_r);
                        ImGui::DragFloat(("Intensity##LightIntensity_" + std::to_string(i)).c_str(), &light->m_intensity, 0.1f);

                    } */
                    else if (DirectionalLight* dLight = dynamic_cast<DirectionalLight*>(component))
                    {
                        ImGui::Text("Directional Light:");

                        ImGui::ColorEdit4(("Ambient Color##LightAmbientColor_" + std::to_string(i)).c_str(), &dLight->m_ambiantColor.m_r);
                        ImGui::ColorEdit4(("Specular Color##LightSpecularColor_" + std::to_string(i)).c_str(), &dLight->m_specularColor.m_r);
                        ImGui::ColorEdit4(("Diffuse Color##SpotLightDiffuseColor_" + std::to_string(i)).c_str(), &dLight->m_diffuseColor.m_r);
                        ImGui::DragFloat3(("Direction##LightDirection_" + std::to_string(i)).c_str(), &dLight->m_direction.m_x, 0.1f);
                        ImGui::DragFloat(("Intensity##LightIntensity_" + std::to_string(i)).c_str(), &dLight->m_intensity, 0.1f);

                    }
                    else if (PointLight* pLight = dynamic_cast<PointLight*>(component))
                    {
                        ImGui::Text("Point Light:");

                        ImGui::ColorEdit4(("Ambient Color##PointLightAmbientColor_" + std::to_string(i)).c_str(), &pLight->m_ambiantColor.m_r);
                        ImGui::ColorEdit4(("Specular Color##PointLightSpecularColor_" + std::to_string(i)).c_str(), &pLight->m_specularColor.m_r);
                        ImGui::ColorEdit4(("Diffuse Color##SpotLightDiffuseColor_" + std::to_string(i)).c_str(), &pLight->m_diffuseColor.m_r);
                        ImGui::DragFloat3(("Position##PointLightPosition_" + std::to_string(i)).c_str(), &pLight->m_position.m_x, 0.1f);
                        ImGui::DragFloat(("Intensity##PointLightIntensity_" + std::to_string(i)).c_str(), &pLight->m_intensity, 0.1f);
                        ImGui::DragFloat(("ConstantValue##PointLightConstantValue_" + std::to_string(i)).c_str(), &pLight->m_constantValue, 0.1f);
                        ImGui::DragFloat(("LinearValue##PointLightLinearValue_" + std::to_string(i)).c_str(), &pLight->m_linearValue, 0.1f);
                        ImGui::DragFloat(("QuadraticValue##PointLightQuadraticValue_" + std::to_string(i)).c_str(), &pLight->m_quadraticValue, 0.1f);
                    }
                    else if (SpotLight* sLight = dynamic_cast<SpotLight*>(component))
                    {
                        ImGui::Text("Spot Light:");

                        ImGui::ColorEdit4(("Ambient Color##SpotLightAmbientColor_" + std::to_string(i)).c_str(), &sLight->m_ambiantColor.m_r);
                        ImGui::ColorEdit4(("Diffuse Color##SpotLightDiffuseColor_" + std::to_string(i)).c_str(), &sLight->m_diffuseColor.m_r);
                        ImGui::ColorEdit4(("Specular Color##SpotLightSpecularColor_" + std::to_string(i)).c_str(), &sLight->m_specularColor.m_r);
                        ImGui::DragFloat3(("Position##SpotLightPosition_" + std::to_string(i)).c_str(), &sLight->m_position.m_x, 0.1f);
                        ImGui::DragFloat3(("Direction##SpotLightDirection" + std::to_string(i)).c_str(), &sLight->m_direction.m_x, 0.1f);
                        ImGui::DragFloat(("Intensity##SpotLightIntensity_" + std::to_string(i)).c_str(), &sLight->m_intensity, 0.1f);
                        ImGui::DragFloat(("SpotAngle##SpotAngle_" + std::to_string(i)).c_str(), &sLight->m_spotAngle, 0.1f);
                        ImGui::DragFloat(("SmoothValue##SpotLightSmoothValue_" + std::to_string(i)).c_str(), &sLight->m_spotSmoothValue, 0.1f);
                        ImGui::DragFloat(("ConstantValue##SpotLightConstantValue_" + std::to_string(i)).c_str(), &sLight->m_constantValue, 0.1f);
                        ImGui::DragFloat(("LinearValue##SpotLightLinearValue_" + std::to_string(i)).c_str(), &sLight->m_linearValue, 0.1f);
                        ImGui::DragFloat(("QuadraticValue##SpotLightQuadraticValue_" + std::to_string(i)).c_str(), &sLight->m_quadraticValue, 0.1f);
                    }
                    else if (MeshRenderer* meshRenderer = dynamic_cast<MeshRenderer*>(component))
                    {
                        ImGui::Text("MeshRenderer: %s", typeid(*meshRenderer).name());

                        const Mesh* mesh = meshRenderer->GetMesh();
                        if (mesh)
                        {
                            std::string meshName = entity->GetName();
                            ImGui::Text("Mesh Type: %s", meshName.c_str());

                            if (meshName.find("Cube") != std::string::npos)
                            {
                                static float cubeSize = 1.0f;
                                static bool polygonMode;
                                ImGui::DragFloat("Size##Cube", &cubeSize, 0.1f, 0.1f, 10.0f);
                                ImGui::Checkbox("PolygonMode Fill##Cube", &polygonMode);
                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                if (ImGui::Button("Apply##Cube"))
                                {
                                    meshRenderer->SetMesh(MeshUtilities::CreateCube("Modified Cube", cubeSize));
                                }
                            }
                            else if (meshName.find("Sphere") != std::string::npos)
                            {
                                static float radius = 1.0f;
                                static int segments = 24, rings = 24;
                                static bool polygonMode;
                                ImGui::DragFloat("Radius##Sphere", &radius, 0.1f, 0.1f, 10.0f);
                                ImGui::DragInt("Segments##Sphere", &segments, 1, 3, 64);
                                ImGui::DragInt("Rings##Sphere", &rings, 1, 3, 64);
                                ImGui::Checkbox("PolygonMode Fill##Sphere", &polygonMode);
                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                if (ImGui::Button("Apply##Sphere"))
                                {
                                    meshRenderer->SetMesh(MeshUtilities::CreateUVSphere("Modified Sphere", radius, segments, rings));
                                }
                            }
                            else if (meshName.find("GeodesicSphere") != std::string::npos)
                            {
                                static float radius = 1.0f;
                                static int subdivisions = 3;
                                static bool polygonMode;
                                ImGui::DragFloat("Radius##GeodesicSphere", &radius, 0.1f, 0.1f, 10.0f);
                                ImGui::DragInt("Segments##GeodesicSphere", &subdivisions, 1, 3, 64);
                                ImGui::Checkbox("PolygonMode Fill##GeodesicSphere", &polygonMode);
                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                meshRenderer->SetMesh(MeshUtilities::CreateGeodesicSphere("Modified GeodesicSphere", radius, subdivisions));
                            }
                            else if (meshName.find("Stair") != std::string::npos)
                            {
                                static float stepWidth = 1.0f, stepHeight = 0.2f, stepDepth = 1.0f;
                                static int stepCount = 5;
                                static bool polygonMode;
                                static bool autoApply = false;
                                ImGui::DragFloat("Width##Stair", &stepWidth, 0.1f, 0.1f, 10.0f);
                                ImGui::DragFloat("Step Height##Stair", &stepHeight, 0.05f, 0.1f, 5.0f);
                                ImGui::DragFloat("Step Depth##Stair", &stepDepth, 0.1f, 0.1f, 10.0f);
                                ImGui::DragInt("Step Count##Stair", &stepCount, 1, 1, 50);
                                ImGui::Checkbox("PolygonMode Fill##Stair", &polygonMode);
                                ImGui::Checkbox("Auto Apply##Stair", &autoApply);
                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                if(autoApply)
                                {
                                    if (ImGui::Button("Apply##Stair"))
                                    {
                                        meshRenderer->SetMesh(MeshUtilities::CreateStaircase("Modified Stair", stepWidth, stepHeight, stepDepth, stepCount));
                                    }
                                } else
                                    meshRenderer->SetMesh(MeshUtilities::CreateStaircase("Modified Stair", stepWidth, stepHeight, stepDepth, stepCount));

                            }
                            else if (meshName.find("Torus") != std::string::npos)
                            {
                                static float majorRadius = 1.0f, minorRadius = 0.3f;
                                static int segments = 24, rings = 24;
                                static bool polygonMode;
                                ImGui::DragFloat("Major Radius##Torus", &majorRadius, 0.1f, 0.1f, 10.0f);
                                ImGui::DragFloat("Minor Radius##Torus", &minorRadius, 0.05f, 0.1f, 5.0f);
                                ImGui::DragInt("Segments##Torus", &segments, 1, 3, 64);
                                ImGui::DragInt("Rings##Torus", &rings, 1, 3, 64);
                                ImGui::Checkbox("PolygonMode Fill##Torus", &polygonMode);
                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                if (ImGui::Button("Apply##Torus"))
                                {
                                    meshRenderer->SetMesh(MeshUtilities::CreateTorus("Modified Torus", majorRadius, minorRadius, segments, rings));
                                }
                            }
                            else if (meshName.find("Capsule") != std::string::npos)
                            {
                                static float radius = 1.0f, height = 1.0f;
                                static int segments = 24, rings = 24;
                                static bool polygonMode;
                                ImGui::DragFloat("Radius##Capsule", &radius, 0.1f, 0.1f, 10.0f);
                                ImGui::DragFloat("Height##Capsule", &height, 0.1f, 0.1f, 10.0f);
                                ImGui::DragInt("Segments##Capsule", &segments, 1, 3, 64);
                                ImGui::DragInt("Rings##Capsule", &rings, 1, 3, 64);
                                ImGui::Checkbox("PolygonMode Fill##Capsule", &polygonMode);
                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                if (ImGui::Button("Apply##Capsule"))
                                {
                                    meshRenderer->SetMesh(MeshUtilities::CreateCapsule("Modified Capsule", radius, height, segments, rings));
                                }
                            }
                            else if (meshName.find("Prism") != std::string::npos)
                            {
                                static float size = 1.0f;
                                static int side = 24;
                                static bool polygonMode;
                                ImGui::DragFloat("Size##Prism", &size, 0.1f, 0.1f, 10.0f);
                                ImGui::DragInt("Side##Prism", &side, 1, 3, 64);
                                ImGui::Checkbox("PolygonMode Fill##Prism", &polygonMode);
                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                if (ImGui::Button("Apply##Prism"))
                                {
                                    meshRenderer->SetMesh(MeshUtilities::CreatePrism("Modified Prism", size, side));
                                }
                            }
                            else if (meshName.find("Water") != std::string::npos)
                            {
                                static int width = 1, height = 1;
                                static float tileSize = 10, waveHeight = 10, waveLength = 1, waveSpeed = 0.1f, waveSteepness = 0.3f, time = 0.1f;
                                static bool polygonMode;
                                ImGui::DragInt("Width##Water", &width, 1, 3, 1);
                                ImGui::DragInt("Height##Water", &height, 1, 3, 1);
                                ImGui::DragFloat("TileSize##Water", &tileSize, 0.1f, -500.f, 500.f);
                                ImGui::DragFloat("WaveHeight##Water", &waveHeight, 0.1f, 0.1f);
                                ImGui::DragFloat("WaveSpeed##Water", &waveSpeed, 0.1f, 0.1f);
                                ImGui::DragFloat("WaveSteepness##Water", &waveSteepness, 0.1f, 0.1f);
                                ImGui::DragFloat("Time##Water", &time, 0.1f);
                                ImGui::Checkbox("PolygonMode Fill##Water", &polygonMode);

                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                meshRenderer->SetMesh(MeshUtilities::CreateWaterMesh("Modified Water", width, height, tileSize, waveHeight, waveLength, waveSpeed, waveSteepness, time));
                            }
                            else if (meshName.find("Terrain Procedural") != std::string::npos)
                            {
                                static int width = 1, height = 1;
                                static float tileSize, maxHeight, noiseScale, noiseStrength;
                                static bool polygonMode;
                                ImGui::DragInt("Width##TerrainProcedural", &width, 1, 3, 1);
                                ImGui::DragInt("Height##TerrainProcedural", &height, 1, 3, 1);
                                ImGui::DragFloat("TileSize##TerrainProcedural", &tileSize, 0.1f, -500.f, 500.f);
                                ImGui::DragFloat("MaxHeight##TerrainProcedural", &maxHeight, 0.1f, 0.1f);
                                ImGui::DragFloat("NoiseScale##TerrainProcedural", &noiseScale, 0.1f, 0.1f);
                                ImGui::DragFloat("NoiseStrength##TerrainProcedural", &noiseStrength, 0.1f, 0.1f);
                                ImGui::Checkbox("PolygonMode Fill##TerrainProcedural", &polygonMode);

                                meshRenderer->SetPolygonMode(polygonMode ? PolygonMode::Fill : PolygonMode::Line);
                                meshRenderer->SetMesh(MeshUtilities::CreateProceduralTerrain("Modified Terrain Procedural", width, height, tileSize, maxHeight, noiseScale, noiseStrength));
                            }
                        }
                    }
                    else
                    {
                        ImGui::Text("Unknown Component");
                    }

                    ImGui::PopID();
                }
            }
        }

        ImGui::PopID();  // Fin de PushID pour l'entité
    }

    ImGui::End();
}
