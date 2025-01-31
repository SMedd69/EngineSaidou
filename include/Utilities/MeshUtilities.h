#ifndef __MESH_UTILITIES_H__
    #define __MESH_UTILITIES_H__

    #include <Engine/Mesh.h>
    #include <Utilities/TimeEngine.h>
    #include <map>

    class MeshUtilities
    {
    public:
        struct CubeUVInfo
        {
        public:
            Vector2 leftFacePos = Vector2(0.125f, 0.375f);
            Vector2 rightFacePos = Vector2(0.625, 0.375f);
            Vector2 backFacePos = Vector2(0.875f, 0.375f);
            Vector2 frontFacePos = Vector2(0.375f, 0.375f);
            Vector2 bottomFacePos = Vector2(0.375f, 0.125f);
            Vector2 topFacePos = Vector2(0.375f, 0.625f);

            float uvFaceSize = 0.25f;
        };

        static Mesh* CreateCube(const std::string& assetName, float size);
        static Mesh* CreatePlane(const std::string& assetName, float size);
        static Mesh* CreateUVSphere(const std::string& assetName, float radius, int segments, int rings);
        static Mesh* CreateCylinder(const std::string& assetName, float radius, int segments, float height);
        static Mesh* CreateCone(const std::string& assetName, float radius, float radius2, int segments, float height);
        static Mesh* CreateTorus(const std::string& assetName, float radius, float radius2, int segments, int rings);
        static Mesh* CreateCapsule(const std::string& assetName, float radius, float height, int segments, int rings);
        static Mesh* CreatePrism(const std::string& assetName, float size, int sides);
        static Mesh* CreatePyramid(const std::string& assetName, float size);
        static Mesh* CreateStaircase(const std::string& assetName, float width, float stepHeight, float stepDepth, int stepCount);

        static Mesh* CreateRoundedCube(const std::string& assetName, float size, float radius, int subdivisions, float subdivisionStart);
        static Mesh* CreateGeodesicSphere(const std::string& assetName, float radius, int subdivisions);

        static Mesh* CreateCustomCuveUV(const std::string& assetName, float size, CubeUVInfo cubeUVInfo);
        static Mesh* CreateCustomCylinderUV(const std::string& assetName, float radius, int segments, float height, Vector2 bodyUVPosition, Vector2 bodyUVSize, Vector2 circle1UVPosition, Vector2 circle2UVPosition, float circleUVSize);

        static Mesh* CreateRectangle(const std::string& assetName, float width, float height);
        static Mesh* CreateRegularConvexPolygon(const std::string& assetName, int sideCount, float radius);
        static Mesh* CreateCircle(const std::string& assetName, float radius);
        static Mesh* CreateGrid(const std::string& assetName, int widthTileCount, int heightTileCount);

        static Mesh* CreateWaterMesh(const std::string& assetName, int width, int height, float tileSize, float waveHeight, float waveLength, float waveSpeed, float waveSteepness, float time);
        static Mesh* CreateTerrainMesh(const std::string& assetName, int width, int height, float tileSize, float maxHeight, float noiseScale, float noiseStrength);
        static Mesh* CreateProceduralTerrain(const std::string& assetName, int width, int height, float tileSize, float maxHeight, float noiseScale, float noiseStrength);

        static int GetMiddlePoint(int i0, int i1, std::vector<Vector3>& vertices, std::map<std::pair<int, int>, int>& middleCache, float radius);
    };

#endif // !__MESH_UTILITIES_H__