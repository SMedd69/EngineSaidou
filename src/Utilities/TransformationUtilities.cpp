#include <Utilities/TransformationUtilities.h>

Vector2 TransformationUtilities::Identity(const Vector2& a)
{
    return a;
}

Vector2 TransformationUtilities::Translation(const Vector2& a, const Vector2& b)
{
    return a + b;
}

Vector2 TransformationUtilities::Scale(const Vector2& a, float s)
{
    return a * s;
}

Vector2 TransformationUtilities::Homothety(const Vector2& a, const Vector2& b, float s)
{
    return (b - a) * s + b;
}

Vector2 TransformationUtilities::PointReflection(const Vector2& a, const Vector2& center)
{
    return (center - a) * 2 + a;
}

float TransformationUtilities::DotProduct(const Vector2& a, const Vector2& b)
{
    return a.m_x * b.m_x + a.m_y * b.m_y;
}

Vector2 TransformationUtilities::AxialSymmetry(const Vector2& a, const Vector2& axe)
{
    float axeMagnitude = axe.MagnitudeSqrt();
    return a + ( axe * (DotProduct(a, axe) / (axeMagnitude * axeMagnitude)) - a) * 2;
}

Vector2 TransformationUtilities::AxialSymmetry(const Vector2& a, const Vector2& axe, const Vector2& center)
{
    float axeMagnitude = axe.MagnitudeSqrt();
    return  a + (axe * (DotProduct(a - center, axe) / (axeMagnitude * axeMagnitude)) - (a - center)) * 2;
}

Vector2 TransformationUtilities::Rotation(const Vector2& a, const float angle)
{
    float angleDegToRad = angle * M_PI / 180.0f;
    float x = a.m_x * cos(angleDegToRad) - a.m_y * sin(angleDegToRad);
    float y = a.m_y * cos(angleDegToRad) + a.m_x * sin(angleDegToRad);
    return {x, y};
}

Vector2 TransformationUtilities::Rotation(const Vector2& a, const Vector2& center, const float angle)
{
    float angleDegToRad = angle * M_PI / 180.0f;
    float x = center.m_x + (a.m_x - center.m_x) * cos(angleDegToRad) - (a.m_x - center.m_y) * sin(angleDegToRad);
    float y = center.m_y + (a.m_y - center.m_y) * cos(angleDegToRad) + (a.m_x - center.m_x) * sin(angleDegToRad);
    return {x, y};
}

float TransformationUtilities::Repeat(float t, float length)
{
    return std::clamp(t - std::floorf(t / length) * length, 0.0f, length);
}

float TransformationUtilities::PingPong(float t, float length)
{
    t = Repeat(t, length * 2.0f);
    return length - std::abs(t - length);
}