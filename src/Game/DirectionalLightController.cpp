#include <Game/DirectionalLightController.h>
#include <Math/Quaternion.h>
#include <Engine/Entity.h>
#include <iostream>
DirectionalLightControllerComponent::DirectionalLightControllerComponent() : Component()
{
	m_directionalLightComponent = nullptr;

}

void DirectionalLightControllerComponent::Start()
{
	Component::Start();

	Entity* entity = GetOwnEntity();
	m_directionalLightComponent = entity->GetComponent<DirectionalLight>();
}

void DirectionalLightControllerComponent::Update()
{
	Component::Update();
	if(m_directionalLightComponent != nullptr)
		m_directionalLightComponent->m_direction = Quaternion::AxisAngle(Vector3(0, 1, 0).Normalized(), 1.0f) * m_directionalLightComponent->m_direction;

}

void DirectionalLightControllerComponent::SetDirectionalLightComponent(DirectionalLight* directionalLightComponent)
{
	m_directionalLightComponent = directionalLightComponent;
}