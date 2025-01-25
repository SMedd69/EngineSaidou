#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__

#include <Engine/Light.h>

class SpotLight : public Light
{
    public:

    Vector3 m_position;
    Vector3 m_direction;
    float m_spotAngle;
    float m_spotSmoothValue;

    float m_constantValue;
    float m_linearValue;
    float m_quadraticValue;
    SpotLight();
};

#endif