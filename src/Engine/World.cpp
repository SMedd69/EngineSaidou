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
	Texture* cubeTexture = AssetsManager::CreateTexture("CubeFaceTexture","assets/textures/RedTiles/Red_Tiles_DIFF.jpg");
	Texture* cubeSpecularTexture = AssetsManager::CreateTexture("CubeSpecularTexture","assets/textures/RedTiles/Red_Tiles_SPEC.jpg");

	//Initialise Mesh
	Mesh* cubeMesh = MeshUtilities::CreateCustomCuveUV("CubeMesh", .1f, MeshUtilities::CubeUVInfo());
	Mesh* cylinderMesh = MeshUtilities::CreateCylinder("CylinderMesh", .5f, 24, 2.0f);

	//Initialise Materials
	Material* material = AssetsManager::CreateMaterial("Material0", cubeTexture, cubeTexture, cubeSpecularTexture, Color(1, 0, 0, 1), Color(1, 0, 0, 1), Color(1, 1, 1, 1),32);
	Material* material2 = AssetsManager::CreateMaterial("Material1", cubeTexture, cubeTexture, cubeSpecularTexture, Color(0, 1, 0, 1), Color(0, 1, 0, 1), Color(1, 1, 0, 1), 32);
}

void World::InitWorld()
{
	InitAssets();

	//Intialise Camera Entity
	Vector3 cameraPosition = Vector3(0.0f, 0.0f, -10.8f);
	Vector3 cameraAngles = Vector3(0.0f, 0.0f, 0.0f);

	Entity* cameraEntity = CreateEntity<Entity>();
	{
		Camera* cameraComponent = cameraEntity->AddComponent<Camera>();
		cameraComponent->SetPosition(cameraPosition);
		cameraComponent->SetAngle(cameraAngles);
		cameraComponent->SetProjectionMode(Camera::EProjectionMode::ORTHOGRAPHIC);
		cameraComponent->SetFov(75);
	}

	//Intialise Cornell Box Entities

	std::vector<Vector3> entitiesPosition = std::vector<Vector3>{ Vector3(0.0f, 0.5f, 5.0f),
																	Vector3(0.0f, 0.0f, 5.0f)};

	std::vector<Vector3> entitiesScale = std::vector<Vector3>{ Vector3(1.0f, 1.0f, 1.0f),
																Vector3(1.0f, 1.0f, 1.0f)};

	std::vector<Quaternion> entitiesRotation = std::vector<Quaternion>{ Quaternion::AxisAngle(Vector3::Right,180),
																	 Quaternion::AxisAngle(Vector3::Forward,90)};
	
	LightingSettings::m_globalAmbiantColor = Color(0.5, 0.5, 0.5, 1.0f);

	for (int i = 0; i < 2; i++)
	{
		Entity* cubeEntity = CreateEntity<Entity>();
		{
			Transform* transformComponent = cubeEntity->AddComponent<Transform>();
			transformComponent->SetPosition(entitiesPosition[i]);
			transformComponent->SetRotation(entitiesRotation[i]);
			transformComponent->SetScale(entitiesScale[i]);

			MeshRenderer* meshRendererComponent = cubeEntity->AddComponent<MeshRenderer>();
			meshRendererComponent->SetMesh(AssetsManager::GetAsset<Mesh>( i < 1 ? "CubeMesh" : "CylinderMesh"));
			meshRendererComponent->SetTransform(transformComponent);
			meshRendererComponent->SetShader(AssetsManager::GetAsset<Shader>("BlinnPhongShader"));
			meshRendererComponent->SetMaterial(AssetsManager::GetAsset<Material>("Material" + std::to_string(i)));
		}
	}


	//Initialise Directional Light entity
	DirectionalLightEntity* lightEntity = CreateEntity<DirectionalLightEntity>();
	{
		DirectionalLight* dLightComponent = lightEntity->AddComponent<DirectionalLight>();
		dLightComponent->m_direction = Vector3(0, 0, 1).Normalized();
		dLightComponent->m_ambiantColor = Color(0, 0, 0, 1.0f);
		dLightComponent->m_specularColor = Color(0.3f, 0.3f, 0.3f, 1.0f);
		dLightComponent->m_intensity = 3.0f;
		
		lightEntity->SetDirectionalLightComponent(dLightComponent);

		DirectionalLightControllerComponent* dLightControllerComponent = lightEntity->AddComponent<DirectionalLightControllerComponent>();
		dLightControllerComponent->SetDirectionalLightComponent(dLightComponent);
	}	

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
}

void World::RegisterComponent(Component* component)
{
	m_components.insert(component);

	MeshRenderer* m = dynamic_cast<MeshRenderer*>(component);
	if (m)
		m_meshRenderers.insert(m);

	Light* l = dynamic_cast<Light*>(component);
	if (l)
		m_lights.insert(l);

	Camera* c = dynamic_cast<Camera*>(component);
	if (c)
		m_cameras.insert(c);
}