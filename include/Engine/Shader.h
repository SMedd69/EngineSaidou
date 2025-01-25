#ifndef __SHADER_H__
    #define __SHADER_H__

    #include <iostream>
    #include <Utilities/Logger.h>
    #include <glad/glad.h>
    #include <Math/Vector2.h>
    #include <Math/Matrix3x3.h>
    #include <Math/Matrix4x4.h>

    class Shader
    {
        public:
        Shader(const char* vertexShaderSource,const char* fragmentShaderSource);
        void UseShader();
        void SetUniformVector4D(std::string name, float v0, float v1, float v2, float v3);
        void SetUniformVector4D(std::string name, Vector4 value);
        void SetUniformVector2D(std::string name, Vector2 value);
        void SetUniformFloat(std::string name, float value);
        void setUniformMatrix3x3(std::string name, Matrix3x3 value);
        void SetUniformMatrix4x4(std::string name, Matrix4x4 value);

        private:
        int m_shaderProgram;

        int ConfigureVertexShader(const char* vertexShaderSource);
        int ConfigureFragmentShader(const char* fragmentShaderSource);
        void ConfigureShaderProgram(int vertexShaderIndex, int fragmentShaderIndex);
    };
#endif