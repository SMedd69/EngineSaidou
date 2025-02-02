#include <Engine/Camera.h>
#include <iostream>

Camera::Camera(Vector3 position, Vector3 angle, float size, bool isPerspective, bool isHorizontal)
    : m_position(position), m_angle(angle), m_size(size), m_isPerspective(isPerspective), m_isHorizontal(isHorizontal)
{

}

void Camera::SetProjectionMode(EProjectionMode _projectionMode)
{
    if(_projectionMode == EProjectionMode::PERSPECTIVE)
    {
        m_isPerspective = true;
    }
    else
    {
        m_isPerspective = false;
    }
}

Vector2 Camera::GetVerticalAndHorizontalSize(float width, float height)const
{
    if(m_isHorizontal)
    {
        return Vector2(m_size, m_size * height / width);
    }
    else
    {
        return Vector2(m_size * width / height, m_size);
    }
}

void Camera::SetPosition(const Vector3& position)
{
    m_position = position;
}

Vector3 Camera::GetPosition() const
{
    return m_position;
}

void Camera::SetSize(float size)
{
    m_size = size;
}

void Camera::SetAngle(const Vector3& angle)
{
    m_angle = angle;
}

void Camera::SetNear(float _near)
{
	m_near = _near;
}

void Camera::SetFar(float far)
{
	m_far = far;
    ApplyFov();
}


void Camera::SetFov(float fov)
{
	m_fov = fov;
}

void Camera::ApplyFov()
{
	float fovInRadian = m_fov * M_PI / 180.0f;

	m_size = 2.0f * m_near * tan(fovInRadian / 2.0f);
}

float Camera::GetSize() const
{
    return m_size;
}

Vector3 Camera::GetAngle()const
{
	return m_angle;
}

float Camera::GetNear()const
{
	return m_near;
}

float Camera::GetFar()const
{
	return m_far;
}

float Camera::GetFov()const
{
	return m_fov;
}

void Camera::SetSizeType(bool isHorizontal)
{
    m_isHorizontal = isHorizontal;
}

bool Camera::GetSizeType() const
{
    return m_isHorizontal;
}

Matrix4x4 Camera::ViewMatrix()const
{
    return Matrix4x4::ScaleXYZ(Vector3(1.0f, 1.0f,-1.0f)) * Matrix4x4::Rotate(m_angle).Inverse() * Matrix4x4::Translate(m_position).Inverse();
}

Matrix4x4 Camera::ProjectionMatrix(float windowWidth, float windowHeight)const
{
    Vector2 size = GetVerticalAndHorizontalSize(windowWidth, windowHeight);

    if (m_isPerspective)
		return Matrix4x4::Perspective(-size.m_x / 2.0f, size.m_x / 2.0f, -size.m_y / 2.0f, size.m_y / 2.0f, m_near, m_far);
	else
		return Matrix4x4::Orthographic(-size.m_x / 2.0f, size.m_x / 2.0f, -size.m_y / 2.0f, size.m_y / 2.0f, m_near, m_far);
}

std::string Camera::ToString()const
{
    return "Camera Position: " + m_position.ToString() + " Camera Angle: " + m_angle.ToString() + " Camera Size: " + std::to_string(m_size);
}