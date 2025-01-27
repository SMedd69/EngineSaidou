#include <Engine/Mesh.h>
#include <Math/Vector4.h>

Mesh::Mesh(bool useOneVBO)
	: m_useOneVBO(useOneVBO)
{
	GenerateVAO();

	GenerateVBOs(m_useOneVBO == true ? 1 : 3);
	GenerateEBO();
	if(m_useOneVBO == true)
	{
		ConfigureVertexAttributesBuffer();
	}
	else
	{
		ConfigureVerticesBuffer();
		ConfigureUVsBuffer();
		ConfigureNormalsBuffer();
	}
}

Mesh::~Mesh()
{
	m_vertices.clear();
	m_indices.clear();
	m_uvs.clear();
	m_normals.clear();
}

void Mesh::SetVertices(std::vector<Vector3> vertices)
{
	m_vertices = vertices;
	if(m_useOneVBO == true)
	{
		ConfigureVertexAttributesBuffer();
	}
	else
	{
		ConfigureVerticesBuffer();
	}
}

void Mesh::SetUVs(std::vector<Vector2> uvs)
{
	m_uvs = uvs;

	if(m_useOneVBO == true)
	{
		ConfigureVertexAttributesBuffer();
	}
	else
	{
		ConfigureUVsBuffer();
	}
}

void Mesh::SetIndices(std::vector<unsigned int> indices)
{
	m_indices = indices;
	ConfigureEBO();
}

void Mesh::SetNormals(std::vector<Vector3> normals)
{
	m_normals = normals;
	if(m_useOneVBO)
	{
		ConfigureVertexAttributesBuffer();
	}
	else
	{
		ConfigureNormalsBuffer();
	}
}

std::vector<Vector3> Mesh::GetNormals()const
{
	return m_normals;
}

void Mesh::ConfigureNormalsBuffer()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_normals.size(), m_normals.data(), (int)m_glDrawType);

	SetupVertexAttribs(2, 2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

std::vector<Vector3> Mesh::GetVertices()const
{
	return m_vertices;
}

std::vector<Vector2> Mesh::GetUVs()const
{
	return m_uvs;
}

std::vector<unsigned int> Mesh::GetIndices()const
{
	return m_indices;
}

void Mesh::GenerateVAO()
{
	glGenVertexArrays(1, &m_vao);
}

GLuint Mesh::GenerateVBO()
{
	GLuint vbo = 0;

	glGenBuffers(1, &vbo);
	return vbo;
}
void Mesh::GenerateVBOs(int vboCount)
{
	for (int i = 0; i < vboCount; i++)
	{
		m_vbos.push_back(GenerateVBO());
	}
}
void Mesh::ConfigureVerticesBuffer()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_vertices.size(), m_vertices.data(), (int)m_glDrawType);

	SetupVertexAttribs(0, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}
std::vector<VertexAttribute> Mesh::CombineVertexBuffer()
{
	std::vector<VertexAttribute> vertexAttributes;

	for (int i = 0; i < m_vertices.size(); i++)
	{
		VertexAttribute vertexAttribute = VertexAttribute();

		vertexAttribute.m_position = m_vertices[i];
		if(i < m_uvs.size())
		{
			vertexAttribute.m_uv = m_uvs[i];
		}
		else
		{
			vertexAttribute.m_uv = Vector2(0, 0);
		}
		vertexAttributes.push_back(vertexAttribute);
	}

	return vertexAttributes;
}

void Mesh::GenerateEBO()
{
	glGenBuffers(1, &m_ebo);
}
void Mesh::ConfigureEBO()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indices.size(), m_indices.data(), (int)m_glDrawType);
}
void Mesh::ConfigureUVsBuffer()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * m_uvs.size(), m_uvs.data(), (int)m_glDrawType);

	SetupVertexAttribs(1, 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
}

void Mesh::ConfigureVertexAttributesBuffer()
{
	std::vector<VertexAttribute> verticesAttributeBuffer = CombineVertexBuffer();

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * verticesAttributeBuffer.size(), verticesAttributeBuffer.data(), (int)m_glDrawType);

	SetupVertexAttribs(0, 0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)0);

	size_t uvOffset = reinterpret_cast<size_t>(&(reinterpret_cast<VertexAttribute*>(0)->m_uv));
	SetupVertexAttribs(1, 0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)uvOffset);
}

void Mesh::SetupVertexAttribs(GLuint index, int vboIndex, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbos[vboIndex]);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void Mesh::UseMesh()
{
	glBindVertexArray(m_vao);
}

void Mesh::ComputeNormals()
{
	if(m_shapeType == ShapeType::TRIANGLE)
	{
		m_normals = std::vector<Vector3>(m_vertices.size());
		for (int i = 0; i < m_indices.size(); i+=3)
		{
			int indice0 = i;
			int indice1 = i+1;
			int indice2 = i+2;

			if(indice2 < m_indices.size())
			{
				int vertexIndice0 = m_indices[indice0];
				int vertexIndice1 = m_indices[indice1];
				int vertexIndice2 = m_indices[indice2];

				Vector3 vertex0 = m_vertices[vertexIndice0];
				Vector3 vertex1 = m_vertices[vertexIndice1];
				Vector3 vertex2 = m_vertices[vertexIndice2];

				Vector3 v0v1 = (vertex1 - vertex0).Normalized();
				Vector3 v1v2 = (vertex2 - vertex1).Normalized();

				Vector3 normal = Vector3::CrossProduct(v0v1, v1v2).Normalized() * -1;

				m_normals[vertexIndice0] = normal;
				m_normals[vertexIndice1] = normal;
				m_normals[vertexIndice2] = normal;

				std::cout << "Normal : " << normal << std::endl;
			}
		}

		SetNormals(m_normals);
	}
}