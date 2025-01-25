#include <Math/Vector2.h>

#pragma region CONSTRUCTOR

Vector2::Vector2()
    : m_x(0.0f), m_y(0.0f)
{
}

Vector2::Vector2(float x, float y)
    : m_x(x), m_y(y)
{
}

Vector2::Vector2(const Vector2& value)
    : m_x(value.m_x), m_y(value.m_y)
{
}

#pragma endregion

#pragma region MATHS

Vector2 Vector2::One()
{
    m_x = 1.0f;
    m_y = 1.0f;
    return (*this);
}

float Vector2::Magnitude() const
{
    return m_x * m_x + m_y * m_y;
}

float Vector2::MagnitudeSqrt() const
{
    return sqrtf(m_x * m_x + m_y * m_y);
}

void Vector2::Normalize()
{
    float magnitude = 1.0f / MagnitudeSqrt();
    m_x *= magnitude;
    m_y *= magnitude;
}

Vector2 Vector2::Normalized() const
{
    return (*this) / MagnitudeSqrt();
}

#pragma endregion

#pragma region OPERATOR

Vector2 Vector2::operator+(const Vector2& value) const
{
    return Vector2(m_x + value.m_x, m_y + value.m_y);
}

Vector2 Vector2::operator-(const Vector2& value) const
{
    return Vector2(m_x - value.m_x, m_y - value.m_y);
}

Vector2 Vector2::operator*(const float& value) const
{
    return Vector2(m_x * value, m_y * value);
}

Vector2 Vector2::operator/(const float& value) const
{
    float v = 1.0f / value;
    return Vector2(m_x * v, m_y * v);
}

Vector2& Vector2::operator+=(const Vector2& value)
{
    m_x += value.m_x;
    m_y += value.m_y;

    return (*this);
}

Vector2& Vector2::operator-=(const Vector2& value)
{
    m_x -= value.m_x;
    m_y -= value.m_y;

    return (*this);
}
Vector2& Vector2::operator*=(float value)
{
    m_x *= value;
    m_y *= value;

    return (*this);
}
Vector2& Vector2::operator/=(float value)
{
    float val = 1.0f / value;

    m_x *= value;
    m_y *= value;

    return (*this);
}

bool Vector2::operator==(const Vector2& value)const
{
    return (m_x == value.m_x && m_y == value.m_y);
}

bool Vector2::operator!=(const Vector2& value)const
{
    return (m_x != value.m_x || m_y != value.m_y);
}

std::ostream& operator<<(std::ostream& os, const Vector2& value)
{
    os << "X: " << value.m_x << ", Y: " << value.m_y << ")" << std::endl;
    return os;
}

#pragma endregion