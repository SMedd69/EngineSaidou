#ifndef _MESH_RENDERER_H_
#define _MESH_RENDERER_H_

#include <Engine/Camera.h>
#include <Engine/Light.h>
#include <Engine/Window.h>
#include <Engine/Transform.h>
#include <Engine/Shader.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>
#include <Engine/Component.h>
#include <set>

enum class PolygonMode
{
	Fill = GL_FILL,
	Line = GL_LINE,
	Point = GL_POINT,
};

class MeshRenderer : public Component
{
private:

	PolygonMode m_polygonMode = PolygonMode::Fill;
	Shader* m_shader = nullptr;
	Transform* m_transform = nullptr;
	Mesh* m_mesh = nullptr;
	bool m_drawPartialMesh = false;
	int m_partialMeshElementCount = 0;
	int m_partialMeshStartIndex = 0;
	Material* m_material = nullptr;
public:
	MeshRenderer() = default;

	void Draw(Camera* camera, std::set<Light*> lights, Window* window)const;
	void SetDrawPartialMesh(bool drawPartialMesh);
	void SetPartialMeshElementCount(int partialMeshElementCount);
	void SetPartialMeshStartIndex(int partialMeshStartIndex);
	void SetMesh(Mesh* mesh);
	void SetShader(Shader* shader);
	void SetMaterial(Material* material);
	void SetPolygonMode(PolygonMode polygonMode);
	void SetTransform(Transform* transform);

	bool GetDrawPartialMesh()const;
	int GetPartialMeshElementCount()const;
	int GetPartialMeshStartIndex()const;
	const Mesh* GetMesh()const;
	const Shader* GetShader()const;
	const Material* GetMaterial()const;

	PolygonMode GetPolygonMode()const;
	Transform* GetTransform()const;
};

#endif // !_MESH_RENDERER_H_
