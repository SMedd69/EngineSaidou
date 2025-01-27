#ifndef _DIRECTIONAL_LIGHT_ENTITY_H_
#define _DIRECTIONAL_LIGHT_ENTITY_H_
#include <Engine/Entity.h>
#include <Engine/DirectionalLight.h>


class DirectionalLightEntity : public Entity
{

private :
	DirectionalLight* m_directionalLightComponent;

protected:
	friend class World;
	void Start()override;
	void Update()override;

public:
	DirectionalLightEntity();
	void SetDirectionalLightComponent(DirectionalLight* directionalLightComponent);
};
#endif
