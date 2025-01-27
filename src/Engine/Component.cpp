#include <Engine/Component.h>
#include <Engine/Entity.h>

Component::Component()
{
	m_ownEntity = nullptr;
}

Component::~Component() 
{

};

void Component::SetOwnEntity(Entity* ownEntity)
{
	m_ownEntity = ownEntity;
}

Entity* Component::GetOwnEntity()
{
	return m_ownEntity;
}