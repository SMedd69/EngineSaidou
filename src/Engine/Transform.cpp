#include <Engine/Transform.h>

Transform::Transform()
{
    m_position = Vector3(0.0f,0.0f,0.0f);
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_rotation = Quaternion::Identity();
}

Transform::Transform(Vector3 position, Vector3 scale, Quaternion rotation)
    : m_position(position), m_scale(scale), m_rotation(rotation)
{

}

void Transform::SetPosition(const Vector3& position)
{
    m_position = position;
}

void Transform::SetScale(const Vector3& scale)
{
    m_scale = scale;
}

void Transform::SetEulerAngles(const Vector3& eulerAngles)
{
    m_rotation = Quaternion::FromEulerAngle(eulerAngles);
}

void Transform::SetRotation(const Quaternion& rotation)
{
    m_rotation = rotation;
}

Vector3 Transform::GetPosition()
{
    return m_position;
}

Vector3 Transform::GetScale()
{
    return m_scale;
}

Vector3 Transform::GetEulerAngles()
{
    return m_rotation.GetAxis();
}

Quaternion Transform::GetRotation()
{
    return m_rotation;
}

Matrix4x4 Transform::TransformMatrix()const
{
    return Matrix4x4::TRS(m_position, m_rotation, m_scale);
}