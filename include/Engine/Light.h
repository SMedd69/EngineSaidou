#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <Engine/Color.h>
#include <Math/Vector3.h>
#include <Engine/Component.h>

class Light : public Component
{
protected:
    ~Light() = default;
    Light();
public:
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

    void SetIntensity(const float& intensity);
    void SetTypeLight(const LightType& lightType);
    float m_intensity = 1.0f;
};

#endif