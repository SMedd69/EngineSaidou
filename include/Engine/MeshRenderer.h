#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include <Engine/Camera.h>
#include <Engine/Window.h>
#include <Engine/Transform.h>
#include <Engine/Shader.h>
#include <Engine/Mesh.h>
#include <Engine/Light.h>
#include <Engine/Material.h>

#include <Utilities/Texture.h>

enum class PolygonMode
{
	Fill = GL_FILL,
	Line = GL_LINE,
	Point = GL_POINT,
};

class MeshRenderer
{
private:

	PolygonMode m_polygonMode = PolygonMode::Fill;
	Shader* m_shader;
	Transform m_transform;
	Mesh* m_mesh;
	Texture* m_texture;
	bool m_drawPartialMesh = false;
	int m_partialMeshElementCount = 0;
	int m_partialMeshStartIndex = 0;
	Vector2 m_textureTilling = Vector2(1, 1);
	Vector2 m_textureOffset = Vector2(0, 0);
	Material* m_material;
public:
	MeshRenderer(Mesh* mesh, Transform transform, Shader* shader, Material* material, Texture* texture, Vector2 textureTilling = Vector2(0, 0), Vector2 textureOffset = Vector2(1,1));
	void Draw(Camera* camera, std::vector<Light*> lights, Window* window)const;
	void SetDrawPartialMesh(bool drawPartialMesh);
	void SetPartialMeshElementCount(int partialMeshElementCount);
	void SetPartialMeshStartIndex(int partialMeshStartIndex);
	void SetMesh(Mesh* mesh);
	void SetShader(Shader* shader);
	void SetPolygonMode(PolygonMode polygonMode);
	void SetTransform(Transform transform);
	void SetTilling(Vector2 tilling);
	void SetOffset(Vector2 offset);

	bool GetDrawPartialMesh()const;
	int GetPartialMeshElementCount()const;
	int GetPartialMeshStartIndex()const;
	const Mesh* GetMesh()const;
	const Shader* GetShader()const;
	PolygonMode GetPolygonMode()const;
	Transform GetTransform()const;
};

#endif // !_MESH_RENDERER_H_
