#ifndef  _WORLD_H_
#define _WORLD_H_
#include <Engine/Camera.h>
#include <Engine/MeshRenderer.h>
#include <Engine/Light.h>
#include <Engine/Window.h>


class Entity;
class World
{
	std::set<Entity*> m_entities;
	std::set<Camera*> m_cameras;
	std::set<Light*> m_lights;
	std::set<MeshRenderer*> m_meshRenderers;
	std::set<Component*> m_components;

	void RegisterComponent(Component* component);
	friend class Entity;

protected:
	static World* m_world;
	World();
	~World();

public :

	static World* Instance();

	World(World& other) = delete;

	template<class T>
	T* CreateEntity()
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");
		T* entity = new T();
		m_entities.insert(entity);

		return entity;
	}

	void InitAssets();
	void InitWorld();
	void Update();
	void Display(Window* window);

	void RenderUiGui();
	void CreateMeshCube(Mesh* meshObj, std::string nameEntity);
	void RenderComponentsUI();
	void CreatedMesh();
};

#include "Entity.h"

#endif