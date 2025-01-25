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

        static Mesh* CreateCube(float size);
        static Mesh* CreatePlane(float size);
        static Mesh* CreateUVSphere(float radius, int segments, int rings);
        static Mesh* CreateCylinder(float radius, int segments, float height);
        static Mesh* CreateCone(float radius, float radius2, int segments, float height);
        static Mesh* CreateTorus(float radius, float radius2, int segments, int rings);
        static Mesh* CreateCapsule(float radius, float height, int segments, int rings);
        static Mesh* CreatePrism(float size, int sides);
        static Mesh* CreatePyramid(float size);
        static Mesh* CreateStaircase(float width, float stepHeight, float stepDepth, int stepCount);

        static Mesh* CreateRoundedCube(float size, float radius, int subdivisions, float subdivisionStart);
        static Mesh* CreateGeodesicSphere(float radius, int subdivisions);

        static Mesh* CreateCustomCuveUV(float size, CubeUVInfo cubeUVInfo);
        static Mesh* CreateCustomCylinderUV(float radius, int segments, float height, Vector2 bodyUVPosition, Vector2 bodyUVSize, Vector2 circle1UVPosition, Vector2 circle2UVPosition, float circleUVSize);

        static Mesh* CreateRectangle(float width, float height);
        static Mesh* CreateRegularConvexPolygon(int sideCount, float radius);
        static Mesh* CreateCircle(float radius);
        static Mesh* CreateGrid(int widthTileCount, int heightTileCount);

        static Mesh* CreateWaterMesh(int width, int height, float tileSize, float waveHeight, float waveLength, float waveSpeed, float waveSteepness);
        static Mesh* CreateTerrainMesh(int width, int height, float tileSize, float maxHeight, float noiseScale, float noiseStrength);
        static Mesh* CreateProceduralTerrain(int width, int height, float tileSize, float maxHeight, float noiseScale, float noiseStrength);

        static int GetMiddlePoint(int i0, int i1, std::vector<Vector3>& vertices, std::map<std::pair<int, int>, int>& middleCache, float radius);
    };

#endif // !__MESH_UTILITIES_H__