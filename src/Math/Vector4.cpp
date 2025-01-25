#include <Math/Vector4.h>

Vector4::Vector4()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
	m_w = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}

Vector4::Vector4(const Vector4& value)
{
	m_x = value.m_x;
	m_y = value.m_y;
	m_z = value.m_z;
	m_w = value.m_w;
}

Vector4 Vector4::operator+(const Vector4& value) const
{
	return Vector4(m_x + value.m_x, m_y + value.m_y, m_z + value.m_z, m_w + value.m_w);
}

Vector4 Vector4::operator*(const float& value) const
{
	return Vector4(m_x * value, m_y * value, m_z * value, m_w * value);
}

Vector4 Vector4::operator*(const Vector4& value) const
{
	return Vector4(m_x * value.m_x, m_y * value.m_y, m_z * value.m_z, m_w * value.m_w);
}

Vector4 Vector4::operator-(const Vector4& value) const
{
	return Vector4(m_x - value.m_x, m_y - value.m_y, m_z - value.m_z, m_w - value.m_w);
}

Vector4 Vector4::operator/(const float& value) const
{
	float v = 1.0f / value;
	return Vector4(m_x * v, m_y * v, m_z * v, m_w * v);
}

float Vector4::Magnitude() const
{
	return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
}

void Vector4::Normalize()
{
	float magnitude = Magnitude();
	m_x /= magnitude;
	m_y /= magnitude;
	m_z /= magnitude;
	m_w /= magnitude;
}

Vector4& Vector4::operator+=(const Vector4& value)
{
	m_x += value.m_x;
	m_y += value.m_y;
	m_z += value.m_z;
	m_w += value.m_w;

	return (*this);
}

Vector4& Vector4::operator*=(const float& value)
{
	m_x *= value;
	m_y *= value;
	m_z *= value;
	m_w *= value;

	return (*this);
}

Vector4& Vector4::operator*=(const Vector4& value)
{
	m_x *= value.m_x;
	m_y *= value.m_y;
	m_z *= value.m_z;
	m_w *= value.m_w;

	return (*this);
}

Vector4& Vector4::operator-=(const Vector4& value)
{
	m_x -= value.m_x;
	m_y -= value.m_y;
	m_z -= value.m_z;
	m_w -= value.m_w;

	return (*this);
}

Vector4& Vector4::operator/=(const float& value)
{
	m_x /= value;
	m_y /= value;
	m_z /= value;
	m_w /= value;

	return (*this);
}

bool Vector4::operator==(const Vector4& value) const
{
	return (abs(m_x - value.m_x) < FLT_EPSILON && abs(m_y - value.m_y) < FLT_EPSILON && abs(m_z - value.m_z) < FLT_EPSILON && abs(m_w - value.m_w) < FLT_EPSILON);
}

bool Vector4::operator!=(const Vector4& value) const
{
	return (abs(m_x - value.m_x) > FLT_EPSILON || abs(m_y - value.m_y) > FLT_EPSILON || abs(m_z - value.m_z) > FLT_EPSILON || abs(m_w - value.m_w) > FLT_EPSILON);
}


Vector4 Vector4::Normalized() const
{
	return (*this) / Magnitude();
}

Vector4 Vector4::GetSafeInvertedVector()const
{
	Vector4 safeInvertedVector = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	const float epsilon = Mathf::Epsilon8;

	if (abs(m_x) > epsilon)
		safeInvertedVector.m_x = 1.0f / m_x;

	if (abs(m_y) > epsilon)
		safeInvertedVector.m_y = 1.0f / m_y;

	if (abs(m_z) > epsilon)
		safeInvertedVector.m_z = 1.0f / m_z;

	if (abs(m_w) > epsilon)
		safeInvertedVector.m_w = 1.0f / m_w;

	return safeInvertedVector;
}

float Vector4::DotProduct(const Vector4& a, const Vector4& b)
{
	return a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z + a.m_w * b.m_w;
}


std::ostream& operator<<(std::ostream& os, const Vector4& value)
{
	os << "(X : " << value.m_x << ", Y : " << value.m_y << ", Z : " << value.m_z << ", W : " << value.m_w << ")" << std::endl;
	return os;
}