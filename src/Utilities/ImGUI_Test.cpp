#include <Utilities/ImGui_Test.h>
#include <Utilities/MeshUtilities.h>
#include <Engine/AssetsManager.h>
#include <Engine/World.h>
#include <Engine/DirectionalLight.h>

ImGUITest::ImGUITest(GLFWwindow* window, bool running)
    : m_window(window), m_running(running)
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

void ImGUITest::Run(float customColor[4], Vector4 colorBackGround, float camPos[3], float camRot[3],
                    float windowWidth, float windowHeight, float* light,
                    float ambientColor[4], float diffuseColor[4], float specularColor[4])
{
    // Démarre une nouvelle frame pour ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGUITest::SetRunning(bool running)
{
    m_running = running;
}

bool ImGUITest::GetRunning() const
{
    return m_running;
}

// ----------------------- World UI Rendering -----------------------

void World::RenderUiGui()
{
    ImGui::Begin("yoo");

    // Vérification : S'il y a au moins une caméra
    if (!m_cameras.empty())
    {
        Camera* camera = *m_cameras.begin();
        Vector3 position = camera->GetPosition();
        Vector3 angles = camera->GetAngle();

        // Contrôles de la caméra
        if (ImGui::CollapsingHeader("Camera Controls"))
        {
            ImGui::Text("Position");
            ImGui::DragFloat3("Position##CameraPosition", &position.m_x, 0.1f);
            camera->SetPosition(position);

            ImGui::Text("Rotation");
            ImGui::DragFloat3("Rotation##CameraRotation", &angles.m_x, 0.1f);
            camera->SetAngle(angles);
        }
    }
    ImGui::End();

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


    ImGui::Begin("Create Plane");
    if (ImGui::Button("Create Plane##CreatePlane"))
    {
        CreateMeshCube(MeshUtilities::CreatePlane("New Sphere", 1.0f), "New Plane");  // Crée une nouvelle entité de type Plane
    }
    ImGui::End();

    // Affiche les composants de chaque entité
    RenderComponentsUI();
}

// ----------------------- Création d'une entité Cube -----------------------

void World::CreateMeshCube(Mesh* meshObj, std::string nameEntity)
{
    // Position, rotation et échelle par défaut du cube
    Vector3 cubePosition(0.0f, 0.0f, 5.0f);
    Vector3 cubeScale(1.0f, 1.0f, 1.0f);
    Quaternion cubeRotation = Quaternion::Identity();

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

    transformComponent->SetPosition(cubePosition);
    transformComponent->SetScale(cubeScale);
    transformComponent->SetRotation(cubeRotation);

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
    ImGui::Begin("Scene Components Viewer");

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
                        ImGui::DragFloat4(("Rotation (Quat)##TransformRotation_" + std::to_string(i)).c_str(), &rotation.m_x, 0.1f);

                        transform->SetPosition(position);
                        transform->SetScale(scale);
                        transform->SetRotation(rotation);
                    }
                    else if (Light* light = dynamic_cast<Light*>(component))
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

                    }
                    else if (DirectionalLight* dLight = dynamic_cast<DirectionalLight*>(component))
                    {
                        ImGui::Text("Directional Light:");
                        Vector3 positionDLight = dLight->m_direction;
                        ImGui::ColorEdit4(("Ambient Color##LightAmbientColor_" + std::to_string(i)).c_str(), &dLight->m_ambiantColor.m_r);
                        ImGui::ColorEdit4(("Specular Color##LightSpecularColor_" + std::to_string(i)).c_str(), &dLight->m_specularColor.m_r);
                        ImGui::DragFloat(("Intensity##LightIntensity_" + std::to_string(i)).c_str(), &dLight->m_intensity, 0.1f);
                        ImGui::DragFloat3(("Position##LightPosition_" + std::to_string(i)).c_str(), &dLight->m_direction.m_x, 0.1f);

                    }
                    else if (MeshRenderer* meshRenderer = dynamic_cast<MeshRenderer*>(component))
                    {
                        ImGui::Text("MeshRenderer: %s", typeid(*meshRenderer).name());
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
