#include <Engine/MeshRenderer.h>
#include <Engine/DirectionalLight.h>
#include <Engine/PointLight.h>
#include <Engine/SpotLight.h>
#include <Engine/LightingSettings.h>
#include <Engine/Shader.h>
#include <iostream>
#include <sstream>

void MeshRenderer::Draw(Camera* camera, std::set<Light*> lights, Window* window)const
{
	if(m_mesh == nullptr || m_shader == nullptr || m_material == nullptr)
		return;

	glPolygonMode(GL_FRONT_AND_BACK, (int)m_polygonMode);

	m_shader->UseShader();

	Matrix4x4 modelMatrix = m_transform != nullptr ? m_transform->TransformMatrix() : Matrix4x4::Identity();
	m_shader->SetUniformMatrix4x4("model", modelMatrix);
	m_shader->SetUniformMatrix4x4("view", camera->ViewMatrix());
	m_shader->SetUniformMatrix4x4("projection", camera->ProjectionMatrix(window->GetWidth(), window->GetHeight()));

	Matrix3x3 normalMatrix = (Matrix3x3)(modelMatrix).Inverse().Transpose();
	m_shader->SetUniformMatrix3x3("normalMatrix", normalMatrix);
	m_shader->SetUniformVector3D("uViewPos", camera->GetPosition());

	m_shader->SetUniformColor("material.ambientColor", m_material->m_ambientColor);
	m_shader->SetUniformColor("material.diffuseColor", m_material->m_diffuseColor);
	m_shader->SetUniformColor("material.specularColor", m_material->m_specularColor);
	m_shader->SetUniformFloat("material.shininess", m_material->m_shininess);

	m_shader->SetUniformInt("material.ambientTexture", 0);
	m_shader->SetUniformInt("material.diffuseTexture", 1);
	m_shader->SetUniformInt("material.specularTexture", 2);


	if (m_material->m_ambientTexture)
		m_material->m_ambientTexture->Bind(0);

	if (m_material->m_diffuseTexture)
		m_material->m_diffuseTexture->Bind(1);
	
	if(m_material->m_specularTexture)
		m_material->m_specularTexture->Bind(2);


	m_shader->SetUniformVector4D("material.diffuseTextureST", Vector4(0,0,1,1));
	m_shader->SetUniformVector4D("material.ambientTextureST", Vector4(0,0,1,1));
	m_shader->SetUniformVector4D("material.specularTextureST", Vector4(0,0,1,1));


	int directionalLightCounter = 0;
	int spotLightCounter = 0;
	int pointLightCounter = 0;
	for (auto it = lights.begin(); it != lights.end(); ++it)
	{
		Light* light = *it;
		if (light->m_lightType == Light::LightType::Directional)
		{
			DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(light);
			m_shader->SetUniformColor("directionalLight.ambientColor", directionalLight->m_ambiantColor);
			m_shader->SetUniformColor("directionalLight.diffuseColor", directionalLight->m_diffuseColor);
			m_shader->SetUniformColor("directionalLight.specularColor", directionalLight->m_specularColor);
			m_shader->SetUniformVector3D("directionalLight.direction", directionalLight->m_direction);
			m_shader->SetUniformFloat("directionalLight.intensity", directionalLight->m_intensity);
			directionalLightCounter++;
		}
		else if (light->m_lightType == Light::LightType::Point)
		{
			PointLight* pointLight = dynamic_cast<PointLight*>(light);
			std::string ambiant = (std::ostringstream() << "pointLights[" << pointLightCounter << "].ambientColor").str();
			std::string diffuse = (std::ostringstream() << "pointLights[" << pointLightCounter << "].diffuseColor").str();
			std::string specular = (std::ostringstream() << "pointLights[" << pointLightCounter << "].specularColor").str();
			std::string position = (std::ostringstream() << "pointLights[" << pointLightCounter << "].position").str();

			std::string constant = (std::ostringstream() << "pointLights[" << pointLightCounter << "].constant").str();
			std::string linear = (std::ostringstream() << "pointLights[" << pointLightCounter << "].linear").str();
			std::string quadratic = (std::ostringstream() << "pointLights[" << pointLightCounter << "].quadratic").str();

			std::string intensity = (std::ostringstream() << "pointLights[" << pointLightCounter << "].intensity").str();

			m_shader->SetUniformColor(ambiant, pointLight->m_ambiantColor);
			m_shader->SetUniformColor(diffuse, pointLight->m_diffuseColor);
			m_shader->SetUniformColor(specular, pointLight->m_specularColor);
			m_shader->SetUniformVector3D(position, pointLight->m_position);
			m_shader->SetUniformColor(ambiant, pointLight->m_ambiantColor);
			m_shader->SetUniformFloat(constant, pointLight->m_constantValue);
			m_shader->SetUniformFloat(linear, pointLight->m_linearValue);
			m_shader->SetUniformFloat(quadratic, pointLight->m_quadraticValue);
			m_shader->SetUniformFloat(intensity, pointLight->m_intensity);
			pointLightCounter++;
		}
		else if (light->m_lightType == Light::LightType::Spot)
		{
			SpotLight* spotLight = dynamic_cast<SpotLight*>(light);
			std::string ambiant = (std::ostringstream() << "spotLights[" << spotLightCounter << "].ambientColor").str();
			std::string diffuse = (std::ostringstream() << "spotLights[" << spotLightCounter << "].diffuseColor").str();
			std::string specular = (std::ostringstream() << "spotLights[" << spotLightCounter << "].specularColor").str();
			std::string position = (std::ostringstream() << "spotLights[" << spotLightCounter << "].position").str();
			std::string direction = (std::ostringstream() << "spotLights[" << spotLightCounter << "].direction").str();
			
			std::string spotCosAngleName = (std::ostringstream() << "spotLights[" << spotLightCounter << "].spotCosAngle").str();
			std::string spotCosSmoothAngleName = (std::ostringstream() << "spotLights[" << spotLightCounter << "].spotCosSmoothAngle").str();

			std::string constant = (std::ostringstream() << "spotLights[" << spotLightCounter << "].constant").str();
			std::string linear = (std::ostringstream() << "spotLights[" << spotLightCounter << "].linear").str();
			std::string quadratic = (std::ostringstream() << "spotLights[" << spotLightCounter << "].quadratic").str();
			std::string intensity = (std::ostringstream() << "spotLights[" << spotLightCounter << "].intensity").str();

			m_shader->SetUniformColor(ambiant, spotLight->m_ambiantColor);
			m_shader->SetUniformColor(diffuse, spotLight->m_diffuseColor);
			m_shader->SetUniformColor(specular, spotLight->m_specularColor);
			m_shader->SetUniformVector3D(position, spotLight->m_position);
			m_shader->SetUniformVector3D(direction, spotLight->m_direction);

			float spotCosAngle = cosf(spotLight->m_spotAngle * M_PI/180.0f);
			float spotCosSmoothValue = cosf((spotLight->m_spotAngle - spotLight->m_spotAngle * spotLight->m_spotSmoothValue) * M_PI/180.0f);
			m_shader->SetUniformFloat(spotCosAngleName, spotCosAngle);
			m_shader->SetUniformFloat(spotCosSmoothAngleName, spotCosSmoothValue);	

			m_shader->SetUniformFloat(constant, spotLight->m_constantValue);
			m_shader->SetUniformFloat(linear, spotLight->m_linearValue);
			m_shader->SetUniformFloat(quadratic, spotLight->m_quadraticValue);
			m_shader->SetUniformFloat(intensity, spotLight->m_intensity);

			spotLightCounter++;
		}
	}
	m_shader->SetUniformInt("pointLightCount", pointLightCounter);
	m_shader->SetUniformInt("spotLightCount", spotLightCounter);
	m_shader->SetUniformColor("globalAmbientColor", LightingSettings::m_globalAmbiantColor);

	m_mesh->UseMesh();

	if(m_drawPartialMesh)
		glDrawElements((int)m_mesh->m_shapeType, m_partialMeshElementCount, GL_UNSIGNED_INT, (void*)(m_partialMeshStartIndex * sizeof(unsigned int)));
	else
	{
		glDrawElements((int)m_mesh->m_shapeType, m_mesh->GetIndices().size(), GL_UNSIGNED_INT, 0);
	}
}

void MeshRenderer::SetDrawPartialMesh(bool drawPartialMesh)
{
	m_drawPartialMesh = drawPartialMesh;
}
void MeshRenderer::SetPartialMeshElementCount(int partialMeshElementCount)
{
	m_partialMeshElementCount = partialMeshElementCount;
}

void MeshRenderer::SetPartialMeshStartIndex(int partialMeshStartIndex)
{
	m_partialMeshStartIndex = partialMeshStartIndex;
}

void MeshRenderer::SetMesh(Mesh* mesh)
{
	m_mesh = mesh;
}

void MeshRenderer::SetShader(Shader* shader)
{
	m_shader = shader;
}

void MeshRenderer::SetMaterial(Material* material)
{
	m_material = material;
}

void MeshRenderer::SetPolygonMode(PolygonMode polygonMode)
{
	m_polygonMode = polygonMode;
}

void MeshRenderer::SetTransform(Transform* transform)
{
	m_transform = transform;
}


bool MeshRenderer::GetDrawPartialMesh()const
{
	return m_drawPartialMesh;
}

int MeshRenderer::GetPartialMeshElementCount()const
{
	return m_partialMeshElementCount;
}

int MeshRenderer::GetPartialMeshStartIndex()const
{
	return m_partialMeshStartIndex;
}

const Mesh* MeshRenderer::GetMesh()const
{
	return m_mesh;
}

const Shader* MeshRenderer::GetShader()const
{
	return m_shader;
}

PolygonMode MeshRenderer::GetPolygonMode()const
{
	return m_polygonMode;
}

Transform* MeshRenderer::GetTransform()const 
{
	return m_transform;
}

const Material* MeshRenderer::GetMaterial()const 
{
	return m_material;
}