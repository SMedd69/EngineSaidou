#ifndef _MESH_H_
#define _MESH_H_
#include <vector>
#include <Math/Vector2.h>
#include <Math/Vector3.h>

#include <glad/glad.h>
#include <iostream>

#include <Engine/Assets.h>

enum class GLDrawType
{
	GLSTREAM_DRAW = 0x88E0,
	GLSTATIC_DRAW = 0x88E4,
	GLDYNAMIC_DRAW = 0x88E8
};

enum class ShapeType
{
	TRIANGLE = 0x0004,
	Line = 0x0001
};

struct VertexAttribute
{
public:
	Vector3 m_position;
	Vector2 m_uv;
	Vector3 m_normal;
};

class Mesh : public Assets
{
public:

	GLDrawType m_glDrawType = GLDrawType::GLDYNAMIC_DRAW;
	ShapeType m_shapeType = ShapeType::TRIANGLE;
	
	// Constructors
	Mesh(bool useOneVBO = true);

	// Destructor
	~Mesh();

	// Setters
	void SetVertices(std::vector<Vector3> vertices);
	void SetIndices(std::vector<unsigned int> indices);
	void SetUVs(std::vector<Vector2> uvs);
	void SetNormals(std::vector<Vector3> normals);

	// Getters
	std::vector<Vector3> GetVertices()const;
	std::vector<Vector2> GetUVs()const;
	std::vector<Vector3> GetNormals()const;
	std::vector<unsigned int> GetIndices()const;
	void UseMesh();
	void ComputeNormals();

private:
	std::vector<Vector3> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Vector2> m_uvs;
	std::vector<Vector3> m_normals;

	GLuint m_vao;
	void GenerateVAO();

	bool m_useOneVBO;
	std::vector<GLuint> m_vbos;
	GLuint GenerateVBO();
	void GenerateVBOs(int vboCount);

	void ConfigureVerticesBuffer();
	void ConfigureUVsBuffer();
	void ConfigureVertexAttributesBuffer();

	GLuint m_ebo;
	void GenerateEBO();
	void ConfigureEBO();

	void ConfigureNormalsBuffer();
	
	void SetupVertexAttribs(GLuint index, int vboIndex, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

	std::vector<VertexAttribute> CombineVertexBuffer();
};

#endif // !_MESH_H_