#ifndef __SHADER_H__
    #define __SHADER_H__

    #include <iostream>
    #include <Utilities/Logger.h>
    #include <glad/glad.h>
    #include <Math/Vector2.h>
    #include <Math/Matrix3x3.h>
    #include <Math/Matrix4x4.h>
    #include <Engine/Color.h>
    #include <string>
    #include <Engine/Shader.h>
    #include <Engine/Assets.h>
    #include <Utilities/FileSystem.h>

    class Shader : public Assets
    {
        public:
        Shader(std::string vertexShaderFilePath,std::string fragmentShaderFilePath);
        void UseShader();
        void SetUniformVector2D(std::string name, Vector2 value);
        void SetUniformVector3D(std::string name, Vector3 value);
        void SetUniformVector4D(std::string name, float v0, float v1, float v2, float v3);
        void SetUniformVector4D(std::string name, Vector4 value);
        void SetUniformFloat(std::string name, float value);
        void SetUniformMatrix3x3(std::string name, Matrix3x3 value);
        void SetUniformMatrix4x4(std::string name, Matrix4x4 value);
        void SetUniformColor(std::string name, Color value);
	    void SetUniformInt(std::string name, int value);

        private:
        int m_shaderProgram;

        int ConfigureVertexShader(const char* vertexShaderSource);
        int ConfigureFragmentShader(const char* fragmentShaderSource);
        void ConfigureShaderProgram(int vertexShaderIndex, int fragmentShaderIndex);
    };
#endif