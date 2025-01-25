#ifndef __TEXTURE_H__
    #define __TEXTURE_H__

    #include <string>
    #include <glad/glad.h>

    #include <Utilities/Logger.h>
    #include <Utilities/stb_image.h>

    enum class Wrap
    {
        REPEAT = GL_REPEAT,
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
    };
    enum class MinificationFilter
    {
        Point = GL_NEAREST,
        Bilinear = GL_LINEAR,
        PointMipMapPoint = GL_NEAREST_MIPMAP_NEAREST,
        PointMipMapBilinear = GL_NEAREST_MIPMAP_LINEAR,
        BilinearMipMapPoint = GL_LINEAR_MIPMAP_NEAREST,
        Trilinear = GL_LINEAR_MIPMAP_LINEAR
    };
    
    enum class MagnificationFilter
    {
        Point = GL_NEAREST,
        Bilinear = GL_LINEAR
    };
    class Texture {
        public:

            Texture(std::string filePath);
            ~Texture();

            void UseTexture();
            void SetWrapHorizontal(Wrap wrap);
            void SetWrapVertical(Wrap wrap);
            Wrap GetWrapHorizontal()const;
            Wrap GetWrapVertical()const;

            void SetMinificationFilter(MinificationFilter filterMin);
            void SetMagnificationFilter(MagnificationFilter filterMag);
            void SetMipMapTexture(int level, std::string filePath);

            MinificationFilter GetMinificationFilter()const;
            MagnificationFilter GetMagnificationFilter()const;

            void SetMipMapBaseLevel(int baseLevel);
            void SetMipMapMaxLevel(int maxLevel);
            void SetMipMapMinLod(int minLod);
            void SetMipMapMaxLod(int maxLod);
            void SetMipMapLodBias(int lodBias);

            int GetMipMapBaseLevel()const;
            int GetMipMapMaxLevel()const;
            int GetMipMapMinLod()const;
            int GetMipMapMaxLod()const;
            int GetMipMapLodBias()const;

            void SetAnisotropy(float anisotropyValue);
            float GetAnisotropy()const;
            float GetMaxGPUAnisotropy()const;

        private:
            const unsigned char* LoadTexture(std::string filePath);
            void GenerateTextureID();
            void UpdateTextureData(const unsigned char* data);

            GLuint m_textureID;
            float m_anisotropyValue = 16;

            Wrap m_wrapHorizontal = Wrap::REPEAT;
            Wrap m_wrapVertical = Wrap::REPEAT;

            MinificationFilter m_minificationFilter = MinificationFilter::Trilinear;
            MagnificationFilter m_magnificationFilter = MagnificationFilter::Bilinear;

            int m_width = 0;
            int m_height = 0;

            int m_mipMapbaseLevel = 0;
            int m_mipMapMaxLevel = 1000;
            int m_mipMapMinLod = -1000;
            int m_mipMapMaxLod = 1000;
            int m_mipMapLodBias = 0;
    };

#endif // !__TEXTURE_H__