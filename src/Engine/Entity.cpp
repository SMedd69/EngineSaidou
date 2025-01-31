#include <Engine/Entity.h>
#include <algorithm>
#include <cassert>
#include <type_traits>
#include <Engine/World.h>
Entity::Entity()
{
	m_nameEntity = "Unnamed Entity";
}

Entity::Entity(const std::string& nameEntity)
	: m_nameEntity(nameEntity)
{
}


Entity::~Entity()
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = *it;

		delete component;
	}

	m_components.clear();
}

void Entity::Destroy()
{

}

void Entity::Start()
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = *it;

		component->Start();
	}
}

void Entity::Update()
{
	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		Component* component = *it;

		component->Update();
	}
}



void Entity::DestroyComponent(Component* component)
{
	if (component != nullptr)
	{
		m_components.erase(component);
		delete component;
	}
}

const std::string& Entity::GetName() const
{
	return m_nameEntity;
}

const std::vector<Component*>& Entity::GetAllComponents()const
{
	return m_componentAll;
}

void Entity::SetNameEntity(const std::string& nameEntity)
{
	m_nameEntity = nameEntity;
}