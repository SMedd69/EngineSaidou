#include <Engine/Shader.h>

Shader::Shader(const char* vertexShaderSource,const  char* fragmentShaderSource)
{
    int vertexShaderIndex = ConfigureVertexShader(vertexShaderSource);
    int fragmentShaderIndex = ConfigureFragmentShader(fragmentShaderSource);
    ConfigureShaderProgram(vertexShaderIndex, fragmentShaderIndex);
}

void Shader::UseShader()
{
    glUseProgram(m_shaderProgram);
}

#pragma region CONFIGURE_SHADER

int Shader::ConfigureVertexShader(const char* vertexShaderSource)
{
    // Vertex Shader Config
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    int success = 0;
    char infoLog[512];

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

        Logger::getInstance().log("Vertex Shader Compilation Failed: ", Logger::LogLevel::ERR, __FILE__, __LINE__);
        std::cerr << infoLog << std::endl;
    }
    else if(success)
    {
        Logger::getInstance().log("Vertex Shader is Compiled.", Logger::LogLevel::SUCCESS, __FILE__, __LINE__);
    }

    return vertexShader;
}

int Shader::ConfigureFragmentShader(const char* fragmentShaderSource)
{
    // Fragment Shader Comfig
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    int success = 0;
    char infoLog[512];

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        
        Logger::getInstance().log("Fragment Shader Compilation Failed", Logger::LogLevel::ERR, __FILE__, __LINE__);
        std::cerr << infoLog << std::endl;
    } else if(success)
    {
        Logger::getInstance().log("Fragment Shader is Compiled.", Logger::LogLevel::SUCCESS, __FILE__, __LINE__);
    }

    return fragmentShader;
}

void Shader::ConfigureShaderProgram(int vertexShaderIndex, int fragmentShaderIndex)
{
    // Shader Program Config
    m_shaderProgram = glCreateProgram();


    glAttachShader(m_shaderProgram, vertexShaderIndex);
    glAttachShader(m_shaderProgram, fragmentShaderIndex);

    glLinkProgram(m_shaderProgram);

    int success = 0;
    char infoLog[512];

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);

        Logger::getInstance().log("Shader Program Link Compilation Failed.", Logger::LogLevel::ERR, __FILE__, __LINE__);
        std::cerr << infoLog << std::endl;
    }
    else if(success)
    {
        Logger::getInstance().log("Shader Program is Compiled.", Logger::LogLevel::SUCCESS, __FILE__, __LINE__);
    }

    glDeleteShader(vertexShaderIndex);
    glDeleteShader(fragmentShaderIndex);
}

#pragma endregion

#pragma region SET_UNIFORMS

void Shader::SetUniformVector4D(std::string name, float v0, float v1, float v2, float v3)
{
    UseShader();
    int location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::SetUniformVector4D(std::string name, Vector4 value)
{
    UseShader();
    int location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniform4f(location, value.m_x, value.m_y, value.m_z, value.m_w);
}

void Shader::SetUniformVector2D(std::string name, Vector2 value)
{
    int location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniform2f(location, value.m_x, value.m_y);
}

void Shader::SetUniformFloat(std::string name, float value)
{
    int location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniform1f(location, value);
}

void Shader::setUniformMatrix3x3(std::string name, Matrix3x3 value)
{
    int location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, value.GetAsArray().data());
}

void Shader::SetUniformMatrix4x4(std::string name, Matrix4x4 value)
{
    int location = glGetUniformLocation(m_shaderProgram, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, value.GetAsArray().data());
}
#pragma endregion