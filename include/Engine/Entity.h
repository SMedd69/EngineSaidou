#ifndef  _ENTITY_H_
#define _ENTITY_H_
#include <set>
#include <list>
#include <Engine/World.h>
#include <Engine/Entity.h>

class World;
class Component;
class Entity
{
	std::set<Component*> m_components;

public:
	
	Entity();
	Entity(const std::string& nameEntity);
	~Entity();

	void Destroy();
	virtual void Start();
	virtual void Update();

	void SetNameEntity(std::string& nameEntity);

	const std::string& GetName()const;
	const std::vector<Component*>& GetAllComponents()const;

	template<class T>
	T* AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		T* t = new T();
		Component* c = dynamic_cast<Component*>(t);
		c->SetOwnEntity(this);
		m_components.insert(t);
		m_componentAll.push_back(c);

		World::Instance()->RegisterComponent(c);
		return t;
	};

	template<class T>
	T* GetComponent() {
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

		for (auto it = m_components.begin(); it != m_components.end(); ++it)
		{
			T* t = dynamic_cast<T*>(*it);
			if (t != nullptr)
				return t;
		}

		return nullptr;
	};

	template<class T>
	std::set<T*> GetComponents()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		std::set<T*> componentsOfTypeT;

		for (auto it = m_components.begin(); it != m_components.end(); ++it)
		{
			T* t = dynamic_cast<T*>(*it);
			if (t != nullptr)
				componentsOfTypeT.insert(t);
		}

		return componentsOfTypeT;
	};

	void DestroyComponent(Component* component);

	private:
		std::string m_nameEntity = "Unnamed Entity";
		std::vector<Component*> m_componentAll;
};

#include "Component.h"

#endif

