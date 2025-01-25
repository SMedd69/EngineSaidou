#include <Engine/Color.h>

Color::Color()
{
    m_r = 0.0f;
    m_g = 0.0f;
    m_b = 0.0f;
    m_a = 0.0f;
}

Color::Color(float r, float g, float b, float a)
    : m_r(r), m_g(g), m_b(b), m_a(a)
{
}