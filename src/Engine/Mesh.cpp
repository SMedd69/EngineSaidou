#include <Engine/Mesh.h>

Mesh::Mesh(bool useOneVBO)
	: m_useOneVBO(useOneVBO)
{
	GenerateVAO();

	GenerateVBOs(m_useOneVBO == true ? 1 : 2);
	GenerateEBO();
	if(m_useOneVBO == true)
	{
		ConfigureVertexAttributesBuffer();
	}
	else
	{
		ConfigureVerticesBuffer();
		ConfigureUVsBuffer();
	}
}

Mesh::~Mesh()
{
	m_vertices.clear();
	m_indices.clear();
	m_uvs.clear();
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