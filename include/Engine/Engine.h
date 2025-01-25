#ifndef __ENGINE_H__
    #define __ENGINE_H__

    #include <Engine/Window.h>
    #include <Engine/Shader.h>
    #include <Engine/Mesh.h>
    #include <Engine/MeshRenderer.h>
    #include <Engine/Transform.h>
    #include <Engine/Light.h>
    #include <Engine/DirectionalLight.h>
    #include <Engine/LightingSettings.h>
    #include <Engine/Color.h>

    #include <Utilities/TransformationUtilities.h>
    #include <Utilities/MeshUtilities.h>
    #include <Utilities/Texture.h>
    #include <Utilities/FileSystem.h>
    #include <Utilities/ColorEngine.h>
    #include <Utilities/ImGUI_Test.h>

    #include <Math/Vector2.h>
    #include <Math/Vector3.h>
    #include <Math/Vector4.h>
    #include <Math/Matrix2x2.h>
    #include <Math/Matrix4x4.h>
    #include <Math/Quaternion.h>


    #include <cmath>
    #include <sstream>

    class Engine
    {
        public:
            Engine(bool running);
            void Run(bool running);

            void ShowMeshes();
            static float zoomDelta;

            int CreateCube(Vector3 position, Quaternion rotation, Vector3 scale, Mesh* mesh, Shader* shader, Material* material, Texture* texture, std::vector<Transform>& transforms, std::vector<MeshRenderer*>& meshRenderers);
            void SetRotation(int index, Quaternion rotation, std::vector<MeshRenderer*> meshRenderers);
            void SetPosition(int index, Vector3 position, std::vector<MeshRenderer*> meshRenderers);

            Vector3 GetPosition(int index, std::vector<MeshRenderer*> meshRenderers);
            Quaternion GetRotation(int index, std::vector<MeshRenderer*> meshRenderers);
        private:
            bool m_Running;

            Logger& InitLogger();
            void PrintStartBanner();
            void PrintStopBanner();

    };

#endif