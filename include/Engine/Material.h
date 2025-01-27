#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include <Utilities/Texture.h>
#include <Engine/Color.h>
#include <Engine/Assets.h>

class Material : public Assets
{
    public:
        Material();
        Material(Texture* ambientTexture, Texture* diffuseTexture, Texture* specularTexture, Color ambientColor, Color diffuseColor, Color specularColor, float shininess = 32.0f);

        Color m_ambientColor;
        Color m_diffuseColor;
        Color m_specularColor;

        Texture* m_ambientTexture;
        Texture* m_diffuseTexture;
        Texture* m_specularTexture;

        float m_shininess = 32.0f;
};

#endif