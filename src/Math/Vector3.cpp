#include <Math/Vector3.h>
#include <math.h>
#include <Math/Mathf.h>
#include <Math/Quaternion.h>

const Vector3 Vector3::Right = Vector3(1,0,0);
const Vector3 Vector3::Up = Vector3(0, 1, 0);
const Vector3 Vector3::Forward = Vector3(0, 0, 1);

Vector3::Vector3()
{
    m_x = 0.0f;
    m_y = 0.0f;
    m_z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
    : m_x(x), m_y(y), m_z(z)
{

}
Vector3::Vector3(const Vector3& value)
    : m_x(value.m_x), m_y(value.m_y), m_z(value.m_z)
{

}

#pragma region MATHS

Vector3 Vector3::One()
{
    return Vector3(1.0f, 1.0f, 1.0f);
}

float Vector3::Magnitude() const
{
    return m_x * m_x + m_y * m_y + m_z * m_z;
}

float Vector3::MagnitudeSqrt() const
{
    return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
}

void Vector3::Normalize()
{
    float magnitude = 1.0f / MagnitudeSqrt();
    m_x *= magnitude;
    m_y *= magnitude;
    m_z *= magnitude;
}

Vector3 Vector3::Normalized() const
{
    return (*this) / MagnitudeSqrt();
}

Vector3 Vector3::Orthogonal(const Vector3& v)
{
	Vector3 orthogonal;

	if (abs(v.m_x) < abs(v.m_y) && abs(v.m_x) < abs(v.m_z))
	{
		orthogonal = Vector3(0, -v.m_z, v.m_y);
	}
	else if (abs(v.m_y) < abs(v.m_z))
	{
		orthogonal = Vector3(-v.m_z, 0, v.m_x);
	}
	else
	{
		orthogonal = Vector3(-v.m_y, v.m_x, 0);
	}

	// Normaliser le vecteur orthogonal
	orthogonal = orthogonal.Normalized();
	return orthogonal;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
    return Vector3(
        m_y * other.m_z - m_z * other.m_y,
        m_z * other.m_x - m_x * other.m_z,
        m_x * other.m_y - m_y * other.m_x
    );
}

Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)
{
    return Vector3(a.m_y * b.m_z - b.m_y * a.m_z, a.m_z * b.m_x - b.m_z * a.m_x, a.m_x * b.m_y - b.m_x * a.m_y);
}

float Vector3::DotProduct(const Vector3& a, const Vector3& b)
{
    return a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z;
}

Vector3 Vector3::Lerp(const Vector3& v, const Vector3& v2, float t)
{
	return v + (v2 - v) * t;
}

Vector3 Vector3::Slerp(const Vector3& v, const Vector3& v2, float t, bool longPath)
{
	float vMagnitudeSquared = v.MagnitudeSqrt();
	float v2MagnitudeSquared = v2.MagnitudeSqrt();
	float magnitudeSquared = vMagnitudeSquared + (v2MagnitudeSquared - vMagnitudeSquared) * t;

	Vector3 vNorm = v.Normalized();
	Quaternion q = Quaternion::SetGoToRotation(vNorm, v2.Normalized());
	Vector3 Axis = q.GetAxis();
	float angle = q.GetAngle();
	angle = longPath ? -360 + angle : angle;

	Vector3 slerpDirection = vNorm * sqrt(magnitudeSquared);
	Quaternion rotateQuat = Quaternion::AxisAngle(Axis, angle * t);
	
	return rotateQuat * slerpDirection;
}

#pragma endregion

#pragma region OPERATOR

Vector3 Vector3::operator+(const Vector3& value) const
{
    return Vector3(m_x + value.m_x, m_y + value.m_y, m_z + value.m_z);
}

Vector3 Vector3::operator-(const Vector3& value) const
{
    return Vector3(m_x - value.m_x, m_y - value.m_y, m_z - value.m_z);
}

Vector3 Vector3::operator*(const float& value) const
{
    return Vector3(m_x * value, m_y * value, m_z * value);
}

Vector3 Vector3::operator/(const float& value) const
{
    float v = 1.0f / value;
    return Vector3(m_x * v, m_y * v, m_z * v);
}

Vector3& Vector3::operator+=(const Vector3& value)
{
    m_x += value.m_x;
    m_y += value.m_y;
    m_z += value.m_z;

    return (*this);
}

Vector3& Vector3::operator-=(const Vector3& value)
{
    m_x -= value.m_x;
    m_y -= value.m_y;
    m_z -= value.m_z;

    return (*this);
}
Vector3& Vector3::operator*=(float value)
{
    m_x *= value;
    m_y *= value;
    m_z *= value;

    return (*this);
}
Vector3& Vector3::operator/=(float value)
{
    m_x /= value;
    m_y /= value;
    m_z /= value;

    return (*this);
}

bool Vector3::operator==(const Vector3& value)const
{
    const float epsilon = 1e-5;
    return (abs(m_x - value.m_x) < epsilon && abs(m_y - value.m_y) < epsilon && abs(m_z - value.m_z) < epsilon);

    return (m_x == value.m_x && m_y == value.m_y && m_z == value.m_z);
}

bool Vector3::operator!=(const Vector3& value)const
{
    const float epsilon = 1e-5; // ajustez selon vos besoins
	return (abs(m_x - value.m_x) > epsilon || abs(m_y - value.m_y) > epsilon || abs(m_z - value.m_z) > epsilon);
}

std::ostream& operator<<(std::ostream& os, const Vector3& value)
{
    os << "(X: " << value.m_x << ", Y: " << value.m_y << ", Z: " << value.m_z << ")" << std::endl;
    return os;
}

#pragma endregion

std::string Vector3::ToString()const
{
    return "(X: " + std::to_string(m_x) + ", Y: " + std::to_string(m_y) + ", Z: " + std::to_string(m_z) + ")";
}