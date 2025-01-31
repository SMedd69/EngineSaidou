#include <Engine/World.h>
#include <Engine/AssetsManager.h>
#include <Utilities/MeshUtilities.h>
#include <Engine/DirectionalLight.h>
#include <Game/DirectionalLightEntity.h>
#include <Game/DirectionalLightController.h>
#include <Engine/Transform.h>
#include <Engine/MeshRenderer.h>
#include <Engine/Camera.h>
#include <Engine/LightingSettings.h>
#include <Utilities/ImGui_Test.h>

World* World::m_world = nullptr;

World::World()
{

}

World* World::Instance()
{
	if (m_world == nullptr)
	{
		m_world = new World();
	}

	return m_world;
}

World::~World()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* entity = *it;
		delete entity;
	}

	m_entities.clear();
	m_components.clear();
	m_meshRenderers.clear();
	m_cameras.clear();
	m_lights.clear();

	if (m_world)
	{
		delete m_world;
		m_world = nullptr;
	}
}

void World::InitAssets()
{
	//Initialise Shader
	Shader* shader = AssetsManager::CreateShader("BlinnPhongShader", "assets/shaders/BlinnPhongShader.vert", "assets/shaders/BlinnPhongShader.frag");

	//Initialise Textures
	Texture* cubeTexture = AssetsManager::CreateTexture("CubeFaceTexture","assets/textures/Damiers/CubeTextureFace.png");
	Texture* cubeSpecularTexture = AssetsManager::CreateTexture("CubeSpecularTexture","assets/textures/Damiers/CubeTextureSpecular.png");

	//Initialise Mesh
	Mesh* cubeMesh = MeshUtilities::CreateGeodesicSphere("CubeMesh", .1f, 6);
	Mesh* cylinderMesh = MeshUtilities::CreateCylinder("CylinderMesh", .5f, 24, 2.0f);

	//Initialise Materials
	Material* material = AssetsManager::CreateMaterial("Material0", cubeTexture, cubeTexture, cubeSpecularTexture, Color(1, 0, 0, 1), Color(1, 0, 0, 1), Color(1, 1, 1, 1),32);
	Material* material2 = AssetsManager::CreateMaterial("Material1", cubeTexture, cubeTexture, cubeSpecularTexture, Color(0, 1, 0, 1), Color(0, 1, 0, 1), Color(1, 1, 0, 1), 32);
}

void World::InitWorld()
{
    InitAssets();

    /* // Initialiser la caméra
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
    } */

    /* std::string nameEntityCube = "Sphere";

    // Initialiser le cube
    Entity* cubeEntity = CreateEntity<Entity>();
    {
        cubeEntity->SetNameEntity(nameEntityCube);
        Transform* transformComponent = cubeEntity->AddComponent<Transform>();
        if (!transformComponent)
        {
            std::cerr << "Failed to create Transform Component" << std::endl;
            return;
        }

        transformComponent->SetPosition(Vector3(2.0f, 0.5f, 2.0f));
        transformComponent->SetRotation({0.0f, 0.0f, 0.0f, 1.0f});
        transformComponent->SetScale(Vector3(1.0f, 1.0f, 1.0f));

        MeshRenderer* meshRendererComponent = cubeEntity->AddComponent<MeshRenderer>();

        if (!meshRendererComponent)
        {
            std::cerr << "Failed to create MeshRenderer Component" << std::endl;
            return;
        }

        meshRendererComponent->SetMesh(AssetsManager::GetAsset<Mesh>("CubeMesh"));
        meshRendererComponent->SetTransform(transformComponent);
        meshRendererComponent->SetShader(AssetsManager::GetAsset<Shader>("BlinnPhongShader"));
        meshRendererComponent->SetMaterial(AssetsManager::GetAsset<Material>("Material0"));
    }

    std::string nameEntityCylinder = "Cylinder";

    // Initialiser le cylindre
    Entity* cylinderEntity = CreateEntity<Entity>();
    {
        cylinderEntity->SetNameEntity(nameEntityCylinder);
        Transform* transformComponent = cylinderEntity->AddComponent<Transform>();

        if (!transformComponent)
        {
            std::cerr << "Failed to create Transform Component" << std::endl;
            return;
        }

        transformComponent->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
        transformComponent->SetRotation(Quaternion::AxisAngle(Vector3::Forward, 0));
        transformComponent->SetScale(Vector3(1.0f, 1.0f, 1.0f));

        MeshRenderer* meshRendererComponent = cylinderEntity->AddComponent<MeshRenderer>();
        if (!meshRendererComponent)
        {
            std::cerr << "Failed to create MeshRenderer Component" << std::endl;
            return;
        }

        meshRendererComponent->SetMesh(AssetsManager::GetAsset<Mesh>("CylinderMesh"));
        meshRendererComponent->SetTransform(transformComponent);
        meshRendererComponent->SetShader(AssetsManager::GetAsset<Shader>("BlinnPhongShader"));
        meshRendererComponent->SetMaterial(AssetsManager::GetAsset<Material>("Material1"));
    }

    std::string nameEntityDLight = "Directional Light";

    // Initialiser la lumière directionnelle
    DirectionalLightEntity* lightEntity = CreateEntity<DirectionalLightEntity>();
    {
        DirectionalLight* dLightComponent = lightEntity->AddComponent<DirectionalLight>();
        if (!dLightComponent)
        {
            std::cerr << "Failed to create Directional Light Component" << std::endl;
            return;
        }

        dLightComponent->m_direction = Vector3(0, 0, 1).Normalized();
        dLightComponent->m_ambiantColor = Color(0, 0, 0, 1.0f);
        dLightComponent->m_specularColor = Color(0.3f, 0.3f, 0.3f, 1.0f);
        dLightComponent->m_intensity = 3.0f;

        lightEntity->SetDirectionalLightComponent(dLightComponent);
        lightEntity->SetNameEntity(nameEntityDLight);

        // DirectionalLightControllerComponent* dLightControllerComponent = lightEntity->AddComponent<DirectionalLightControllerComponent>();
        // dLightControllerComponent->SetDirectionalLightComponent(dLightComponent);
    } */

    // Démarrer chaque entité
    for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
    {
        Entity* entity = *it;
        entity->Start();
    }
}

void World::Update()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		Entity* entity = *it;

		entity->Update();
	}
	RenderUiGui();
}

void World::Display(Window* window)
{
	for (auto it = m_cameras.begin(); it != m_cameras.end(); ++it)
	{
		Camera* camera = *it;

		for (auto rendererIt = m_meshRenderers.begin(); rendererIt != m_meshRenderers.end(); ++rendererIt)
		{
			MeshRenderer* meshRenderer = *rendererIt;

			meshRenderer->Draw(camera, m_lights, window);
		}
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void World::RegisterComponent(Component* component)
{
	m_components.insert(component);

	MeshRenderer* m = dynamic_cast<MeshRenderer*>(component);
	if (m)
	{
		std::cout << "MeshRenderer registered: " << m << std::endl;
		m_meshRenderers.insert(m);
	}

	Light* l = dynamic_cast<Light*>(component);
	if (l)
	{
		std::cout << "Light registered: " << l << std::endl;
		m_lights.insert(l);
	}

	Camera* c = dynamic_cast<Camera*>(component);
	if (c)
	{
		std::cout << "Camera registered: " << c << std::endl;
		m_cameras.insert(c);
	}
}