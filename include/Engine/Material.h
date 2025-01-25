#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include <Utilities/Texture.h>
#include <Engine/Color.h>

class Material
{
    public:
        Material();
        Material(Texture* ambientTexture, Texture* diffuseTexture, Texture* specularTexture, Color ambientColor, Color diffuseColor, Color specularColor, float shininess = 32.0f);

        void SetAmbientColor(const Color& color);
        void SetDiffuseColor(const Color& color);
        void SetSpecularColor(const Color& color);

        Color m_ambientColor;
        Color m_diffuseColor;
        Color m_specularColor;

        Texture* m_ambientTexture;
        Texture* m_diffuseTexture;
        Texture* m_specularTexture;

        float m_shininess = 32.0f;
};

#endif