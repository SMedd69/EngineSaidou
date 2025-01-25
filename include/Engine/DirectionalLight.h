#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#include <Engine/Light.h>

class DirectionalLight : public Light
{
    public:
        Vector3 m_direction;
        DirectionalLight();
};

#endif