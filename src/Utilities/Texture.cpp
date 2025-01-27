#include <Utilities/Texture.h>

Texture::Texture(std::string filePath)
{
    GenerateTextureID();
    unsigned char* data = LoadTexture(filePath);
    UpdateTextureData(data);
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}

unsigned char* Texture::LoadTexture(std::string filePath)
{
    int channel_in_file = 0;
    int desired_channels = 4;

    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &channel_in_file, desired_channels);

    if (data)
    {
        // Do something with the data
        Logger::getInstance().log("Texture: " + filePath + " is loaded.", Logger::LogLevel::SUCCESS, __FILE__, __LINE__);
        return data;
    }
    else
    {
        // Handle error
        Logger::getInstance().log("Failed to load texture: " + filePath, Logger::LogLevel::ERR, __FILE__, __LINE__);
        return nullptr;
    }
}

void Texture::GenerateTextureID()
{
    glGenTextures(1, &m_textureID);
}

void Texture::UpdateTextureData(const unsigned char* data)
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLuint)m_minificationFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLuint)m_magnificationFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLuint)m_wrapHorizontal);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLuint)m_wrapVertical);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, (GLuint)m_mipMapbaseLevel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, (GLuint)m_mipMapMaxLevel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, (GLuint)m_mipMapMinLod);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, (GLuint)m_mipMapMaxLod);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, (GLuint)m_mipMapLodBias);
    glGenerateMipmap(GL_TEXTURE_2D);
    SetAnisotropy(m_anisotropyValue);

    Logger::getInstance().log("Texture data is updated.", Logger::LogLevel::INFO, __FILE__, __LINE__);
}

void Texture::SetMipMapTexture(int level, std::string filePath)
{
    int channel_in_file = 0;
    int desired_channel = 4;

    int width = 0;
    int height = 0;

    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channel_in_file, desired_channel);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

void Texture::Bind(int textureIndex)
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}


void Texture::Unbind(int textureIndex)
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::UseTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::SetWrapHorizontal(Wrap wrap)
{
    m_wrapHorizontal = wrap;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLuint)m_wrapHorizontal);
}

void Texture::SetWrapVertical(Wrap wrap)
{
    m_wrapVertical = wrap;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLuint)m_wrapVertical);
}

Wrap Texture::GetWrapHorizontal()const
{
    return m_wrapHorizontal;
}

Wrap Texture::GetWrapVertical()const
{
    return m_wrapVertical;
}

void Texture::SetMinificationFilter(MinificationFilter filterMin)
{
    m_minificationFilter = filterMin;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLuint)m_minificationFilter);
}

void Texture::SetMagnificationFilter(MagnificationFilter filterMag)
{
    m_magnificationFilter = filterMag;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLuint)m_magnificationFilter);
}

MinificationFilter Texture::GetMinificationFilter()const
{
    return m_minificationFilter;
}

MagnificationFilter Texture::GetMagnificationFilter()const
{
    return m_magnificationFilter;
}

void Texture::SetMipMapBaseLevel(int baseLevel)
{
    m_mipMapbaseLevel = baseLevel;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, (GLuint)m_mipMapbaseLevel);
}

void Texture::SetMipMapMaxLevel(int maxLevel)
{
    m_mipMapMaxLevel = maxLevel;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, (GLuint)m_mipMapMaxLevel);
}

void Texture::SetMipMapMinLod(int minLod)
{
    m_mipMapMinLod = minLod;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, (GLuint)m_mipMapMinLod);
}

void Texture::SetMipMapMaxLod(int maxLod)
{
    m_mipMapMaxLod = maxLod;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, (GLuint)m_mipMapMaxLod);
}

void Texture::SetMipMapLodBias(int lodBias)
{
    m_mipMapLodBias = lodBias;
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, (GLuint)m_mipMapLodBias);
}

int Texture::GetMipMapBaseLevel()const
{
    return m_mipMapbaseLevel;
}

int Texture::GetMipMapMaxLevel()const
{
    return m_mipMapMaxLevel;
}

int Texture::GetMipMapMinLod()const
{
    return m_mipMapMinLod;
}

int Texture::GetMipMapMaxLod()const
{
    return m_mipMapMaxLod;
}

int Texture::GetMipMapLodBias()const
{
    return m_mipMapLodBias;
}

void Texture::SetAnisotropy(float anisotropyValue)
{
    float maxAnisotropy = GetMaxGPUAnisotropy();
    m_anisotropyValue = anisotropyValue > maxAnisotropy ? maxAnisotropy : anisotropyValue;

    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, m_anisotropyValue);
}

float Texture::GetAnisotropy()const
{
    return m_anisotropyValue;
}

float Texture::GetMaxGPUAnisotropy()const
{
    GLfloat maxAnisotropy;

    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAnisotropy);
    return maxAnisotropy;
}