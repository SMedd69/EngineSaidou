#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <Engine/Color.h>
#include <Math/Vector3.h>

class Light
{
public:
    virtual ~Light() = default;

    enum class LightType
    {
        Directional,
        Point,
        Spot
    };

    LightType m_lightType;
    Color m_ambiantColor;
    Color m_diffuseColor;
    Color m_specularColor;

    float m_intensity = 1.0f;

protected:

    Light();

};

#endif