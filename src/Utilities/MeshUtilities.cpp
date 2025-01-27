#include <Utilities/MeshUtilities.h>
#include <Engine/AssetsManager.h>

Mesh* MeshUtilities::CreateCube(const std::string& assetName, float size)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    float halfSize = size / 2.0f;
    std::vector<Vector3> vertices;

    vertices.push_back(Vector3(-halfSize, -halfSize, -halfSize));
    vertices.push_back(Vector3(halfSize, -halfSize, -halfSize));
    vertices.push_back(Vector3(halfSize, halfSize, -halfSize));
    vertices.push_back(Vector3(-halfSize, halfSize, -halfSize));

    vertices.push_back(Vector3(halfSize, -halfSize, -halfSize));
    vertices.push_back(Vector3(halfSize, -halfSize, halfSize));
    vertices.push_back(Vector3(halfSize, halfSize, halfSize));
    vertices.push_back(Vector3(halfSize, halfSize, -halfSize));

    vertices.push_back(Vector3(halfSize, -halfSize, halfSize));
    vertices.push_back(Vector3(-halfSize, -halfSize, halfSize));
    vertices.push_back(Vector3(-halfSize, halfSize, halfSize));
    vertices.push_back(Vector3(halfSize, halfSize, halfSize));

    vertices.push_back(Vector3(-halfSize, -halfSize, halfSize));
    vertices.push_back(Vector3(-halfSize, -halfSize, -halfSize));
    vertices.push_back(Vector3(-halfSize, halfSize, -halfSize));
    vertices.push_back(Vector3(-halfSize, halfSize, halfSize));

    vertices.push_back(Vector3(-halfSize, halfSize, -halfSize));
    vertices.push_back(Vector3(halfSize, halfSize, -halfSize));
    vertices.push_back(Vector3(halfSize, halfSize, halfSize));
    vertices.push_back(Vector3(-halfSize, halfSize, halfSize));

    vertices.push_back(Vector3(-halfSize, -halfSize, -halfSize));
    vertices.push_back(Vector3(-halfSize, -halfSize, halfSize));
    vertices.push_back(Vector3(halfSize, -halfSize, halfSize));
    vertices.push_back(Vector3(halfSize, -halfSize, -halfSize));

    std::vector<Vector2> uvs;

    for (int i = 0; i < 6; i++)
    {
        uvs.push_back({ 0, 0 }); // 0 left bottom
        uvs.push_back({ 1, 0 }); // 1 right bottom
        uvs.push_back({ 1, 1 }); // 2 right top
        uvs.push_back({ 0, 1 }); // 3 left top
    }

    std::vector<unsigned int> indices;

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(7);

    indices.push_back(8);
    indices.push_back(9);
    indices.push_back(10);
    indices.push_back(8);
    indices.push_back(10);
    indices.push_back(11);

    indices.push_back(12);
    indices.push_back(13);
    indices.push_back(14);
    indices.push_back(12);
    indices.push_back(14);
    indices.push_back(15);

    indices.push_back(16);
    indices.push_back(17);
    indices.push_back(18);
    indices.push_back(16);
    indices.push_back(18);
    indices.push_back(19);

    indices.push_back(20);
    indices.push_back(21);
    indices.push_back(22);
    indices.push_back(20);
    indices.push_back(22);
    indices.push_back(23);

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->SetUVs(uvs);

    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreateCustomCuveUV(const std::string& assetName, float size, CubeUVInfo cubeUVInfo)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);

    std::vector<Vector2> uvs;
    float halfFaceUVSize = cubeUVInfo.uvFaceSize / 2.0f;

    // Front face
    Vector2 facePosition = cubeUVInfo.frontFacePos;
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, halfFaceUVSize));

    // Right face
    facePosition = cubeUVInfo.rightFacePos;
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, halfFaceUVSize));

    // Back face
    facePosition = cubeUVInfo.backFacePos;
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, halfFaceUVSize));

    // Left face
    facePosition = cubeUVInfo.leftFacePos;
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, halfFaceUVSize));

    // Top face
    facePosition = cubeUVInfo.topFacePos;
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, halfFaceUVSize));

    // Bottom face
    facePosition = cubeUVInfo.bottomFacePos;
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(-halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, -halfFaceUVSize));
    uvs.push_back(facePosition + Vector2(halfFaceUVSize, halfFaceUVSize));

    mesh->SetUVs(uvs);

    mesh->ComputeNormals();
    return mesh;
}

Mesh* MeshUtilities::CreateRectangle(const std::string& assetName, float width, float height)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    std::vector<Vector3> vertices =
    {
        { -halfWidth, -halfHeight, 0 },
        { halfWidth, -halfHeight, 0 },
        { halfWidth, halfHeight, 0 },
        { -halfWidth, halfHeight, 0 }
    };

    std::vector<unsigned int> indices =
    {
        0, 2, 1,
        0, 3, 2
    };

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->ComputeNormals();
    return mesh;
}

Mesh* MeshUtilities::CreateRegularConvexPolygon(const std::string& assetName, int sideCount, float radius)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    float angle = 2.0f * M_PI / sideCount;

    for (int i = 0; i < sideCount; i++)
    {
        float x = cos(i * angle) * radius;
        float y = sin(i * angle) * radius;
        vertices.push_back({ x, y, 0 });
    }

    std::vector<unsigned int> indices;
    for (int i = 1; i < sideCount - 1; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->ComputeNormals();
    return mesh;
}

Mesh* MeshUtilities::CreateCircle(const std::string& assetName, float radius)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    float angle = 0.0f;
    float angleStep = 2.0f * M_PI / 360.0f;

    for (int i = 0; i < 360; i++)
    {
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        vertices.push_back({ x, y, 0 });
        angle += angleStep;
    }

    for (int i = 1; i < 359; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indices.push_back(0);
    indices.push_back(359);
    indices.push_back(1);

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);

    mesh->ComputeNormals();
    return mesh;
}

Mesh* MeshUtilities::CreateGrid(const std::string& assetName, int widthTileCount, int heightTileCount)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    float halfWidth = widthTileCount / 2.0f;
    float halfHeight = heightTileCount / 2.0f;

    for (int i = 0; i < widthTileCount + 1; i++)
    {
        float x = i - halfWidth;
        vertices.push_back({ x, -halfHeight, 0 });
        vertices.push_back({ x, halfHeight, 0 });
    }

    for (int i = 0; i < heightTileCount + 1; i++)
    {
        float y = i - halfHeight;
        vertices.push_back({ -halfWidth, y, 0 });
        vertices.push_back({ halfWidth, y, 0 });
    }

    for (int i = 0; i < vertices.size(); i += 2)
    {
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);

    mesh->ComputeNormals();
    return mesh;
}

Mesh* MeshUtilities::CreateRoundedCube(const std::string& assetName, float size, float radius, int subdivisions, float subdivisionStart)
{
    if (radius > size / 2.0f) {
        radius = size / 2.0f; // Le rayon ne peut pas dépasser la moitié de la taille
    }

    Mesh* mesh = AssetsManager::CreateMesh(assetName, false);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;

    float halfSize = size / 2.0f;
    float cornerSize = radius;
    float innerSize = halfSize - cornerSize;

    // Vérification du paramètre subdivisionStart pour s'assurer qu'il est entre 0 et 1
    if (subdivisionStart < 0.0f) subdivisionStart = 0.0f;
    if (subdivisionStart > 1.0f) subdivisionStart = 1.0f;

    // Générer les sommets pour chaque face (6 faces)
    for (int face = 0; face < 6; ++face) {
        // Directions pour chaque face
        Vector3 normal;
        Vector3 tangent, bitangent;

        switch (face) {
        case 0: // Face avant
            normal = Vector3(0, 0, 1);
            tangent = Vector3(1, 0, 0);
            bitangent = Vector3(0, 1, 0);
            break;
        case 1: // Face arrière
            normal = Vector3(0, 0, -1);
            tangent = Vector3(-1, 0, 0);
            bitangent = Vector3(0, 1, 0);
            break;
        case 2: // Face gauche
            normal = Vector3(-1, 0, 0);
            tangent = Vector3(0, 0, 1);
            bitangent = Vector3(0, 1, 0);
            break;
        case 3: // Face droite
            normal = Vector3(1, 0, 0);
            tangent = Vector3(0, 0, -1);
            bitangent = Vector3(0, 1, 0);
            break;
        case 4: // Face dessus
            normal = Vector3(0, 1, 0);
            tangent = Vector3(1, 0, 0);
            bitangent = Vector3(0, 0, -1);
            break;
        case 5: // Face dessous
            normal = Vector3(0, -1, 0);
            tangent = Vector3(1, 0, 0);
            bitangent = Vector3(0, 0, 1);
            break;
        }

        // Ajouter le sommet central de la face
        int start = vertices.size(); // Indice de départ pour cette face
        vertices.push_back(normal * halfSize);  // Ajout du sommet central

        // Subdivisions
        for (int u = 0; u <= subdivisions; ++u) {
            for (int v = 0; v <= subdivisions; ++v) {
                // Interpoler entre les bords de la face
                float du = (float)u / subdivisions;
                float dv = (float)v / subdivisions;

                // Calculer la position locale en fonction de `subdivisionStart`
                float distanceFromCenter = sqrt(du * du + dv * dv);
                float factor = std::min(subdivisionStart + (1.0f - subdivisionStart) * distanceFromCenter, 1.0f);

                Vector3 point = (tangent * (du - 0.5f) * innerSize * 2) +
                                (bitangent * (dv - 0.5f) * innerSize * 2) +
                                normal * halfSize;

                // Arrondir les coins en fonction de la distance
                if (point.MagnitudeSqrt() > innerSize) {
                    Vector3 offset = point.Normalized() * radius * factor;
                    point += offset;
                }

                vertices.push_back(point);
            }
        }

        // Générer les indices pour les triangles
        for (int u = 0; u < subdivisions; ++u) {
            for (int v = 0; v < subdivisions; ++v) {
                // Calculer les indices des sommets
                int topLeft = start + 1 + u * (subdivisions + 1) + v;
                int topRight = topLeft + 1;
                int bottomLeft = topLeft + (subdivisions + 1);
                int bottomRight = bottomLeft + 1;

                // Triangle 1
                indices.push_back(start);  // Centre
                indices.push_back(bottomLeft);
                indices.push_back(topLeft);

                // Triangle 2
                indices.push_back(start);  // Centre
                indices.push_back(topLeft);
                indices.push_back(topRight);

                // Triangle 3
                indices.push_back(start);  // Centre
                indices.push_back(topRight);
                indices.push_back(bottomRight);

                // Triangle 4
                indices.push_back(start);  // Centre
                indices.push_back(bottomRight);
                indices.push_back(bottomLeft);
            }
        }
    }

    // Créer et remplir le mesh
    std::vector<Vector2> uvs;
    for (size_t i = 0; i < vertices.size(); ++i) {
        Vector3 v3 = vertices[i].Normalized();
        float u = 0.5f + atan2(v3.m_z, v3.m_x) / (2.0f * M_PI);
        float v = 0.5f - asin(v3.m_y) / M_PI;
        uvs.push_back({ u, v });
    }

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->SetUVs(uvs);

    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreateGeodesicSphere(const std::string& assetName, float radius, int subdivisions)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    // Vérification des subdivisions
    if (subdivisions < 0) subdivisions = 0;

    // Création de l'icosaèdre de base
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;

    // Constantes pour l'icosaèdre
    const float t = (1.0f + sqrt(5.0f)) / 2.0f; // Nombre d'or

    // Sommets de l'icosaèdre (normalisés pour former une sphère)
    vertices.push_back(Vector3(-1,  t, 0).Normalized() * radius);
    vertices.push_back(Vector3( 1,  t, 0).Normalized() * radius);
    vertices.push_back(Vector3(-1, -t, 0).Normalized() * radius);
    vertices.push_back(Vector3( 1, -t, 0).Normalized() * radius);

    vertices.push_back(Vector3( 0, -1,  t).Normalized() * radius);
    vertices.push_back(Vector3( 0,  1,  t).Normalized() * radius);
    vertices.push_back(Vector3( 0, -1, -t).Normalized() * radius);
    vertices.push_back(Vector3( 0,  1, -t).Normalized() * radius);

    vertices.push_back(Vector3( t,  0, -1).Normalized() * radius);
    vertices.push_back(Vector3( t,  0,  1).Normalized() * radius);
    vertices.push_back(Vector3(-t,  0, -1).Normalized() * radius);
    vertices.push_back(Vector3(-t,  0,  1).Normalized() * radius);

    // Indices des triangles formant les faces de l'icosaèdre
    indices = {
        0, 11, 5,
        0, 5, 1,
        0, 1, 7,
        0, 7, 10,
        0, 10, 11,

        1, 5, 9,
        5, 11, 4,
        11, 10, 2,
        10, 7, 6,
        7, 1, 8,

        3, 9, 4,
        3, 4, 2,
        3, 2, 6,
        3, 6, 8,
        3, 8, 9,

        4, 9, 5,
        2, 4, 11,
        6, 2, 10,
        8, 6, 7,
        9, 8, 1
    };

    // Subdivisions
    for (int s = 0; s < subdivisions; ++s)
    {
        std::vector<unsigned int> newIndices;
        std::map<std::pair<int, int>, int> middleCache;

        for (size_t i = 0; i < indices.size(); i += 3)
        {
            // Indices des sommets d'un triangle
            int i0 = indices[i];
            int i1 = indices[i + 1];
            int i2 = indices[i + 2];

            // Trouver les points intermédiaires
            int mid01 = GetMiddlePoint(i0, i1, vertices, middleCache, radius);
            int mid12 = GetMiddlePoint(i1, i2, vertices, middleCache, radius);
            int mid20 = GetMiddlePoint(i2, i0, vertices, middleCache, radius);

            // Ajouter les nouveaux triangles
            newIndices.push_back(i0);
            newIndices.push_back(mid01);
            newIndices.push_back(mid20);

            newIndices.push_back(i1);
            newIndices.push_back(mid12);
            newIndices.push_back(mid01);

            newIndices.push_back(i2);
            newIndices.push_back(mid20);
            newIndices.push_back(mid12);

            newIndices.push_back(mid01);
            newIndices.push_back(mid12);
            newIndices.push_back(mid20);
        }

        indices = newIndices;
    }

    std::vector<Vector2> uvs;

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        Vector3 v3 = vertices[i].Normalized();
        float u = 0.5f + atan2(v3.m_z, v3.m_x) / (2.0f * M_PI);
        float v = 0.5f - asin(v3.m_y) / M_PI;
        uvs.push_back({ u, v });
    }

    // Créer et remplir le mesh
    
    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);

    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreateUVSphere(const std::string& assetName, float radius, int segments, int rings)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    std::vector<Vector2> uvs;

    // Créer les sommets
    for (int y = 0; y <= rings; y++)
    {
        for (int x = 0; x <= segments; x++)
        {
            float xSegment = (float)x / (float)segments;
            float ySegment = (float)y / (float)rings;

            float xPos = cosf(xSegment * 2.0f * M_PI) * sinf(ySegment * M_PI);
            float yPos = cosf(ySegment * M_PI);
            float zPos = sinf(xSegment * 2.0f * M_PI) * sinf(ySegment * M_PI);

            float u = xSegment;
            float v = ySegment;

            uvs.push_back({ Vector2(u, v)});
            vertices.push_back({Vector3(xPos, yPos, zPos) * radius});
        }
    }

    // Créer les indices
    for (int y = 0; y < rings; y++)
    {
        for (int x = 0; x < segments; x++)
        {
            int current = y * (segments + 1) + x;
            int next = y * (segments + 1) + x + 1;

            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(current + segments + 1);

            indices.push_back(current + segments + 1);
            indices.push_back(next);
            indices.push_back(next + segments + 1);
        }
    }

    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);

    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreateCylinder(const std::string& assetName, float radius, int segments, float height)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    std::vector<Vector2> uvs;

    Vector2 circleUVPosition = Vector2(0.5f, 0.5f);
    float circleUVRadius = 0.5f;

    // Créer les sommets
    for (int i = 0; i < 2; i++)
    {
        float yPos = i == 0 ? -height / 2.0f : height / 2.0f;

        vertices.push_back(Vector3(0, yPos, 0));
        uvs.push_back(circleUVPosition);

        for (int j = 0; j <= segments; j++)
        {
            float angle = (float)j / (float)segments * 2.0f * M_PI;
            float xPos = cos(angle) * radius;
            float zPos = sin(angle) * radius;

            vertices.push_back(Vector3(xPos, yPos, zPos));

            float u = circleUVPosition.m_x + circleUVRadius * cos(angle);
            float v = circleUVPosition.m_y + circleUVRadius * sin(angle);

            uvs.push_back(Vector2(u, v));
        }
    }

    float circleUVHeight = 1.0f;

    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / (float)segments * 2.0f * M_PI;
        float xPos = cos(angle) * radius;
        float zPos = sin(angle) * radius;

        vertices.push_back(Vector3(xPos, -height / 2.0f, zPos));
        
        float u = (float)i / (float)segments;
        float v = 0.0f;

        uvs.push_back(Vector2(u, v));

        vertices.push_back(Vector3(xPos, height / 2.0f, zPos));

        v = circleUVHeight;
        uvs.push_back(Vector2(u, v));
    }

    for (int i = 0; i < 2; i++)
    {
        int offset = i * (segments + 2);

        for (int j = 0; j < segments; j++)
        {
            indices.push_back(offset);
            indices.push_back(j + 1 + offset);
            indices.push_back(j + 2 + offset);
        }
    }

    int bodyStartIndex = 2 * (segments + 2);
    for (int i = 0; i < segments; i++)
    {
        int current = bodyStartIndex + i * 2;
        int next = current + 2;

        indices.push_back(current);
        indices.push_back(current + 1);
        indices.push_back(next);

        indices.push_back(next);
        indices.push_back(current + 1);
        indices.push_back(next + 1);
    }
    

    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);

    mesh->ComputeNormals();
    return mesh;
}

Mesh* MeshUtilities::CreateCustomCylinderUV(const std::string& assetName, float radius, int segments, float height, Vector2 bodyUVPosition, Vector2 bodyUVSize, Vector2 circle1UVPosition, Vector2 circle2UVPosition, float circleUVSize)
{
    Mesh* mesh = CreateCylinder(assetName, radius, segments, height);
    std::vector<Vector2> uvs;

    for (int i = 0; i < 2; i++)
    {
        Vector2 uvPosition = i == 0 ? circle1UVPosition : circle2UVPosition;

        uvs.push_back(uvPosition);

        for (int j = 0; j <= segments; j++)
        {
            float angle = (float)j / (float)segments * 2.0f * M_PI;

            float u = uvPosition.m_x + circleUVSize * cos(angle);
            float v = uvPosition.m_y + circleUVSize * sin(angle);

            uvs.push_back(Vector2(u, v));
        }
    }

    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / (float)segments * 2.0f * M_PI;

        float u = bodyUVPosition.m_x - bodyUVSize.m_x / 2.0f + ((float)i / (float)segments) * (bodyUVSize.m_x);
        float v = bodyUVPosition.m_y - bodyUVSize.m_y / 2.0f;

        uvs.push_back(Vector2(u, v));

        v = bodyUVPosition.m_y - bodyUVSize.m_y / 2.0f + bodyUVSize.m_y;
        uvs.push_back(Vector2(u, v));
    }

    mesh->SetUVs(uvs);
    mesh->ComputeNormals();

    return mesh;    
}

Mesh* MeshUtilities::CreateCone(const std::string& assetName, float radius1, float radius2, int segments, float height)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    std::vector<Vector2> uvs;

    Vector2 circleUVPosition = Vector2(0.5f, 0.5f);
    float circleUVRadius = 0.5f;

    // Créer les sommets
    for (int i = 0; i < 2; i++)
    {
        float radius = i == 0 ? radius1 : radius2;
        float yPos = i == 0 ? -height / 2.0f : height / 2.0f;

        vertices.push_back(Vector3(0, yPos, 0));
        uvs.push_back(circleUVPosition);

        for (int j = 0; j <= segments; j++)
        {
            float angle = (float)j / (float)segments * 2.0f * M_PI;
            float xPos = cos(angle) * radius;
            float zPos = sin(angle) * radius;

            vertices.push_back(Vector3(xPos, yPos, zPos));

            float u = circleUVPosition.m_x + circleUVRadius * cos(angle);
            float v = circleUVPosition.m_y + circleUVRadius * sin(angle);

            uvs.push_back(Vector2(u, v));
        }
    }

    float circleUVHeight = 1.0f;

    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / (float)segments * 2.0f * M_PI;
        float xPosBottom = cos(angle) * radius1;
        float zPosBottom = sin(angle) * radius1;
        float xPosTop = cos(angle) * radius2;
        float zPosTop = sin(angle) * radius2;

        vertices.push_back(Vector3(xPosBottom, -height / 2.0f, zPosBottom));

        float u = (float)i / (float)segments;
        float v = 0.0f;
        uvs.push_back(Vector2(u, v));

        vertices.push_back(Vector3(xPosTop, height / 2.0f, zPosTop));
        v = circleUVHeight;
        uvs.push_back(Vector2(u, v));
    }

    for (int i = 0; i < 2; i++)
    {
        int offset = i * (segments + 2);

        for (int j = 0; j < segments; j++)
        {
            indices.push_back(offset);
            indices.push_back(j + 1 + offset);
            indices.push_back(j + 2 + offset);
        }
    }

    int bodyStartIndex = 2 * (segments + 2);
    for (int i = 0; i < segments; i++)
    {
        int current = bodyStartIndex + i * 2;
        int next = current + 2;

        indices.push_back(current);
        indices.push_back(current + 1);
        indices.push_back(next);

        indices.push_back(current + 1);
        indices.push_back(next + 1);
        indices.push_back(next);
    }

    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);

    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreateTorus(const std::string& assetName, float radius, float radius2, int segments, int rings)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    std::vector<Vector2> uvs;

    // Créer les sommets
    for (int i = 0; i <= rings; i++)
    {
        float u = (float)i / rings * 2.0f * M_PI;
        float cu = cos(u);
        float su = sin(u);

        for (int j = 0; j <= segments; j++)
        {
            float v = (float)j / segments * 2.0f * M_PI;
            float cv = cos(v);
            float sv = sin(v);

            float x = (radius + radius2 * cv) * cu;
            float y = radius2 * sv;
            float z = (radius + radius2 * cv) * su;

            vertices.push_back(Vector3(x, y, z));
            uvs.push_back(Vector2((float)i / rings, (float)j / segments));
        }
    }

    // Créer les indices
    for (int i = 0; i < rings; i++)
    {
        for (int j = 0; j < segments; j++)
        {
            int nextRow = i + 1;
            int nextColumn = (j + 1) % segments;

            indices.push_back(i * (segments + 1) + j);
            indices.push_back(nextRow * (segments + 1) + j);
            indices.push_back(nextRow * (segments + 1) + nextColumn);

            indices.push_back(i * (segments + 1) + j);
            indices.push_back(nextRow * (segments + 1) + nextColumn);
            indices.push_back(i * (segments + 1) + nextColumn);
        }
    }

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->SetUVs(uvs);

    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreateCapsule(const std::string& assetName, float radius, float height, int segments, int rings)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    std::vector<Vector2> uvs;

    // Vérifier que la hauteur est suffisante pour contenir le cylindre
    if (height < 2 * radius)
    {
        height = 2 * radius; // Forcer une hauteur minimale
    }

    float cylinderHeight = height - 2 * radius; // Hauteur du cylindre central
    float halfCylinderHeight = cylinderHeight / 2.0f;

    // --- Générer les demi-sphères et le cylindre ---
    // Bas de la demi-sphère
    for (int ring = 0; ring <= rings; ++ring)
    {
        float theta = (float)ring / (float)rings * (M_PI / 2.0f);

        for (int segment = 0; segment <= segments; ++segment)
        {
            float phi = (float)segment / (float)segments * (2.0f * M_PI);

            float xPos = cosf(phi) * sinf(theta) * radius;
            float yPos = -halfCylinderHeight - cosf(theta) * radius;
            float zPos = sinf(phi) * sinf(theta) * radius;

            vertices.push_back(Vector3(xPos, yPos, zPos));

            // UV ajusté pour une distribution plus homogène
            float u = (float)segment / (float)segments;
            float v = 0.5f * (1.0f - cosf(theta)); // UV de 0.0 à 0.5
            uvs.push_back(Vector2(u, v));
        }
    }

    // Générer le cylindre central
    for (int i = 0; i <= 1; ++i) // 0 = bas, 1 = haut
    {
        float yOffset = (i == 0) ? -halfCylinderHeight : halfCylinderHeight;

        for (int segment = 0; segment <= segments; ++segment)
        {
            float angle = (float)segment / (float)segments * (2.0f * M_PI);

            float xPos = cos(angle) * radius;
            float zPos = sin(angle) * radius;

            vertices.push_back(Vector3(xPos, yOffset, zPos));

            // UV ajusté : 0.5 (bas) à 0.75 (haut)
            float u = (float)segment / (float)segments;
            float v = (i == 0) ? 0.5f : 0.75f;
            uvs.push_back(Vector2(u, v));
        }
    }

    // Haut de la demi-sphère
    for (int ring = 0; ring <= rings; ++ring)
    {
        float theta = (float)ring / (float)rings * (M_PI / 2.0f);

        for (int segment = 0; segment <= segments; ++segment)
        {
            float phi = (float)segment / (float)segments * (2.0f * M_PI);

            float xPos = cosf(phi) * sinf(theta) * radius;
            float yPos = halfCylinderHeight + cosf(theta) * radius;
            float zPos = sinf(phi) * sinf(theta) * radius;

            vertices.push_back(Vector3(xPos, yPos, zPos));

            // UV ajusté pour une distribution homogène
            float u = (float)segment / (float)segments;
            float v = 0.75f + 0.25f * sinf(theta); // UV de 0.75 à 1.0
            uvs.push_back(Vector2(u, v));
        }
    }

    // --- Générer les indices ---
    // Indices pour la demi-sphère inférieure
    for (int ring = 0; ring < rings; ++ring)
    {
        for (int segment = 0; segment < segments; ++segment)
        {
            int current = ring * (segments + 1) + segment;
            int next = current + 1;

            indices.push_back(current);
            indices.push_back(current + segments + 1);
            indices.push_back(next);

            indices.push_back(current + segments + 1);
            indices.push_back(next + segments + 1);
            indices.push_back(next);
        }
    }

    // Indices pour le cylindre central
    int cylinderBaseIndex = (rings + 1) * (segments + 1);

    for (int segment = 0; segment < segments; ++segment)
    {
        int current = cylinderBaseIndex + segment;
        int next = current + 1;

        indices.push_back(current);
        indices.push_back(current + segments + 1);
        indices.push_back(next);

        indices.push_back(current + segments + 1);
        indices.push_back(next + segments + 1);
        indices.push_back(next);
    }

    // Indices pour la demi-sphère supérieure
    int sphereTopBaseIndex = cylinderBaseIndex + 2 * (segments + 1);

    for (int ring = 0; ring < rings; ++ring)
    {
        for (int segment = 0; segment < segments; ++segment)
        {
            int current = sphereTopBaseIndex + ring * (segments + 1) + segment;
            int next = current + 1;

            indices.push_back(current);
            indices.push_back(current + segments + 1);
            indices.push_back(next);

            indices.push_back(current + segments + 1);
            indices.push_back(next + segments + 1);
            indices.push_back(next);
        }
    }

    // Appliquer les sommets, UV et indices au maillage
    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);

    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreatePyramid(const std::string& assetName, float size)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;

    float halfSize = size / 2.0f;

    // Créer les sommets
    vertices.push_back(Vector3(-halfSize, -halfSize, -halfSize));
    vertices.push_back(Vector3(halfSize, -halfSize, -halfSize));
    vertices.push_back(Vector3(halfSize, -halfSize, halfSize));
    vertices.push_back(Vector3(-halfSize, -halfSize, halfSize));
    vertices.push_back(Vector3(0, halfSize, 0));

    // Créer les indices
    indices = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    // uvs pour chaque sommet
    std::vector<Vector2> uvs = {
        { 0, 0 },
        { 1, 0 },
        { 1, 1 },
        { 0, 1 },
        { 0.5f, 0.5f }
    };

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->SetUVs(uvs);

    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreatePrism(const std::string& assetName, float size, int sides)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;

    float halfSize = size / 2.0f;
    float angleStep = 2.0f * M_PI / sides;

    // Créer les sommets
    for (int i = 0; i < sides; i++)
    {
        float angle = i * angleStep;
        float x = cos(angle) * halfSize;
        float z = sin(angle) * halfSize;

        vertices.push_back(Vector3(x, -halfSize, z));
        vertices.push_back(Vector3(x, halfSize, z));
    }

    // Créer les indices
    for (int i = 0; i < sides; i++)
    {
        int next = (i + 1) % sides;

        indices.push_back(i * 2);
        indices.push_back(i * 2 + 1);
        indices.push_back(next * 2 + 1);

        indices.push_back(i * 2);
        indices.push_back(next * 2 + 1);
        indices.push_back(next * 2);
    }

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->ComputeNormals();

    return mesh;
}

Mesh* MeshUtilities::CreatePlane(const std::string& assetName, float size)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    float halfSize = size / 2.0f;

    std::vector<Vector3> vertices =
    {
        { -halfSize, 0, -halfSize },
        { halfSize, 0, -halfSize },
        { halfSize, 0, halfSize },
        { -halfSize, 0, halfSize }
    };

    // Uvs pour chaque sommet
    std::vector<Vector2> uvs =
    {
        { 0, 0 },
        { 1, 0 },
        { 1, 1 },
        { 0, 1 }
    };

    std::vector<unsigned int> indices =
    {
        0, 2, 1,
        0, 3, 2
    };


    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);
    mesh->ComputeNormals();
    return mesh;
}

Mesh* MeshUtilities::CreateStaircase(const std::string& assetName, float width, float stepHeight, float stepDepth, int stepCount)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<unsigned int> indices;

    int vertexOffset = 0;

    for (int step = 0; step < stepCount; ++step)
    {
        float stepBottomY = step * stepHeight;
        float stepTopY = (step + 1) * stepHeight;
        float stepFrontZ = step * stepDepth;
        float stepBackZ = (step + 1) * stepDepth;

        // Ajouter les sommets de la marche
        vertices.push_back(Vector3(-width / 2, stepBottomY, stepFrontZ)); // Bas gauche avant
        vertices.push_back(Vector3(width / 2, stepBottomY, stepFrontZ));  // Bas droite avant
        vertices.push_back(Vector3(width / 2, stepBottomY, stepBackZ));   // Bas droite arrière
        vertices.push_back(Vector3(-width / 2, stepBottomY, stepBackZ));  // Bas gauche arrière

        vertices.push_back(Vector3(-width / 2, stepTopY, stepFrontZ));    // Haut gauche avant
        vertices.push_back(Vector3(width / 2, stepTopY, stepFrontZ));     // Haut droite avant
        vertices.push_back(Vector3(width / 2, stepTopY, stepBackZ));      // Haut droite arrière
        vertices.push_back(Vector3(-width / 2, stepTopY, stepBackZ));     // Haut gauche arrière

        // Ajouter les UVs
        // Face avant
        uvs.push_back(Vector2(0.0f, step * stepHeight));                        // Bas gauche
        uvs.push_back(Vector2(1.0f, step * stepHeight));                        // Bas droite
        uvs.push_back(Vector2(1.0f, (step + 1) * stepHeight));                  // Haut droite
        uvs.push_back(Vector2(0.0f, (step + 1) * stepHeight));                  // Haut gauche

        // Face arrière
        uvs.push_back(Vector2(0.0f, step * stepHeight));                        // Bas gauche
        uvs.push_back(Vector2(1.0f, step * stepHeight));                        // Bas droite
        uvs.push_back(Vector2(1.0f, (step + 1) * stepHeight));                  // Haut droite
        uvs.push_back(Vector2(0.0f, (step + 1) * stepHeight));                  // Haut gauche

        // Face gauche
        uvs.push_back(Vector2(stepFrontZ, 0.0f));                               // Bas avant
        uvs.push_back(Vector2(stepBackZ, 0.0f));                                // Bas arrière
        uvs.push_back(Vector2(stepBackZ, stepHeight));                          // Haut arrière
        uvs.push_back(Vector2(stepFrontZ, stepHeight));                         // Haut avant

        // Face droite
        uvs.push_back(Vector2(stepFrontZ, 0.0f));                               // Bas avant
        uvs.push_back(Vector2(stepBackZ, 0.0f));                                // Bas arrière
        uvs.push_back(Vector2(stepBackZ, stepHeight));                          // Haut arrière
        uvs.push_back(Vector2(stepFrontZ, stepHeight));                         // Haut avant

        // Face du dessus
        uvs.push_back(Vector2(0.0f, stepFrontZ));                               // Avant gauche
        uvs.push_back(Vector2(1.0f, stepFrontZ));                               // Avant droite
        uvs.push_back(Vector2(1.0f, stepBackZ));                                // Arrière droite
        uvs.push_back(Vector2(0.0f, stepBackZ));                                // Arrière gauche

        // Ajouter les indices pour chaque face de la marche
        // Face avant
        indices.push_back(vertexOffset + 0);
        indices.push_back(vertexOffset + 1);
        indices.push_back(vertexOffset + 5);
        indices.push_back(vertexOffset + 0);
        indices.push_back(vertexOffset + 5);
        indices.push_back(vertexOffset + 4);

        // Face arrière
        indices.push_back(vertexOffset + 3);
        indices.push_back(vertexOffset + 2);
        indices.push_back(vertexOffset + 6);
        indices.push_back(vertexOffset + 3);
        indices.push_back(vertexOffset + 6);
        indices.push_back(vertexOffset + 7);

        // Face gauche
        indices.push_back(vertexOffset + 0);
        indices.push_back(vertexOffset + 4);
        indices.push_back(vertexOffset + 7);
        indices.push_back(vertexOffset + 0);
        indices.push_back(vertexOffset + 7);
        indices.push_back(vertexOffset + 3);

        // Face droite
        indices.push_back(vertexOffset + 1);
        indices.push_back(vertexOffset + 2);
        indices.push_back(vertexOffset + 6);
        indices.push_back(vertexOffset + 1);
        indices.push_back(vertexOffset + 6);
        indices.push_back(vertexOffset + 5);

        // Face du dessus
        indices.push_back(vertexOffset + 4);
        indices.push_back(vertexOffset + 5);
        indices.push_back(vertexOffset + 6);
        indices.push_back(vertexOffset + 4);
        indices.push_back(vertexOffset + 6);
        indices.push_back(vertexOffset + 7);

        // Mettre à jour l'offset des sommets pour la prochaine marche
        vertexOffset += 8;
    }

    // Appliquer les sommets, UVs et indices au maillage
    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);
    mesh->ComputeNormals();
    return mesh;
}

// Creation D'un Mesh pour l'eau et les vagues
Mesh* MeshUtilities::CreateWaterMesh(const std::string& assetName, int width, int height, float tileSize, float waveHeight, float waveLength, float waveSpeed, float waveSteepness)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<unsigned int> indices;

    // Créer les sommets
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            float xPos = x * tileSize;
            float zPos = z * tileSize;

            vertices.push_back(Vector3(xPos, 0, zPos));
            uvs.push_back(Vector2((float)x / width, (float)z / height));
        }
    }

    // Créer les indices
    for (int z = 0; z < height - 1; z++)
    {
        for (int x = 0; x < width - 1; x++)
        {
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);
    mesh->ComputeNormals();

    return mesh;
}

// Création d'un Mesh pour un terrain sans 'erreur Segmentation fault'
Mesh* MeshUtilities::CreateTerrainMesh(const std::string& assetName, int width, int height, float tileSize, float maxHeight, float noiseScale, float noiseStrength)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true);
    std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<unsigned int> indices;

    float halfSize = width * tileSize / 2.0f;

    // Créer les sommets
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            float xPos = x * tileSize - halfSize;
            float zPos = z * tileSize - halfSize;

            float noise = Mathf::PerlinNoise(x * noiseScale, z * noiseScale) * noiseStrength;
            if (std::isnan(noise)) {
                std::cerr << "Erreur : Noise est NaN à x=" << x << ", z=" << z << std::endl;
                noise = 0; // Valeur par défaut
            }
            float yPos = noise * maxHeight;

            vertices.push_back(Vector3(xPos, yPos, zPos));
            uvs.push_back(Vector2((float)x / width, (float)z / height));
        }
    }

    // Créer les indices
    for (int z = 0; z < height - 1; z++)
    {
        for (int x = 0; x < width - 1; x++)
        {
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;

            // Vérifiez les indices avant de les ajouter
            if (topLeft >= vertices.size() || topRight >= vertices.size() ||
                bottomLeft >= vertices.size() || bottomRight >= vertices.size())
            {
                std::cerr << "Erreur : Indices hors limites." << std::endl;
                continue;
            }

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    // Vérifiez la taille des vecteurs avant de les envoyer au mesh
    if (vertices.empty() || uvs.empty() || indices.empty()) {
        std::cerr << "Erreur : Vecteurs vides." << std::endl;
        delete mesh;
        return nullptr;
    }

    mesh->SetVertices(vertices);
    mesh->SetUVs(uvs);
    mesh->SetIndices(indices);
    mesh->ComputeNormals();
    return mesh;
}

Mesh* MeshUtilities::CreateProceduralTerrain(const std::string& assetName, int width, int height, float tileSize, float maxHeight, float noiseScale, float noiseStrength)
{
    Mesh* mesh = AssetsManager::CreateMesh(assetName, true); // Nouveau mesh pour le terrain

    std::vector<Vector3> vertices;
    std::vector<unsigned int> indices;
    std::vector<Vector2> uvs;

    float halfWidth = width * tileSize / 2.0f;
    float halfHeight = height * tileSize / 2.0f;

    // Générer les sommets
    for (int z = 0; z < height; z++)
    {
        for (int x = 0; x < width; x++)
        {
            float xPos = x * tileSize - halfWidth;
            float zPos = z * tileSize - halfHeight;

            // Ajouter du bruit pour les hauteurs
            float noiseValue = Mathf::PerlinNoise(x * noiseScale, z * noiseScale) * noiseStrength;
            float yPos = noiseValue * maxHeight;

            vertices.push_back(Vector3(xPos, yPos, zPos));
            uvs.push_back(Vector2((float)x / (width - 1), (float)z / (height - 1))); // Coordonnées UV
        }
    }

    // Générer les indices pour former des triangles
    for (int z = 0; z < height - 1; z++)
    {
        for (int x = 0; x < width - 1; x++)
        {
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;

            // Premier triangle
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            // Second triangle
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    // Attribuer les données au mesh
    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->SetUVs(uvs);
    mesh->ComputeNormals();
    return mesh; // Retourner le mesh généré
}

// Fonction auxiliaire pour obtenir le point médian
int MeshUtilities::GetMiddlePoint(int i0, int i1, std::vector<Vector3>& vertices, std::map<std::pair<int, int>, int>& middleCache, float radius)
{
    // Assurer un ordre constant pour les clés
    if (i0 > i1) std::swap(i0, i1);
    auto key = std::make_pair(i0, i1);

    // Vérifier si le point médian est déjà calculé
    if (middleCache.find(key) != middleCache.end())
    {
        return middleCache[key];
    }

    // Calculer le point médian
    Vector3 mid = (vertices[i0] + vertices[i1]) / 2.0f;
    mid = mid.Normalized() * radius;

    // Ajouter le point médian aux sommets
    vertices.push_back(mid);
    int midIndex = vertices.size() - 1;

    // Enregistrer dans le cache
    middleCache[key] = midIndex;

    return midIndex;
}