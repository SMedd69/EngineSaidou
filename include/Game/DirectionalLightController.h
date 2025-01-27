#ifndef _DIRECTIONAL_LIGHT_CONTROLLER_H_
#define _DIRECTIONALLIGHTCONTROLLER_H_
#include <Engine/Component.h>
#include <Engine/DirectionalLight.h>

class DirectionalLightControllerComponent : public Component
{
private :
	DirectionalLight* m_directionalLightComponent;

protected:
	void Update() override;
	void Start() override;

public:

	DirectionalLightControllerComponent();
	void SetDirectionalLightComponent(DirectionalLight* directionalLightComponent);
};
#endif
