#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include <Engine/Light.h>

class PointLight : public Light
{
public:
    Vector3 m_position;
    float m_constantValue;
    float m_linearValue;
    float m_quadraticValue;

    PointLight();
};

#endif