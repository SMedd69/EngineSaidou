#include <Engine/Light.h>

Light::Light()
{
    m_ambiantColor = Color(0.1f, 0.1f, 0.1f, 1.0f);
    m_diffuseColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
    m_specularColor = Color(1.0f, 1.0f, 1.0f, 1.0f);
    m_intensity = 1.0f;
    m_lightType = LightType::Directional;
}

void Light::SetIntensity(const float& intensity)
{
    m_intensity = intensity;
}

void Light::SetTypeLight(const LightType& lightType)
{
    m_lightType = lightType;
}