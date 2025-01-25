#ifndef __VECTOR2_H__
    #define __VECTOR2_H__

    #include <math.h>
    #include <ostream>

    struct Vector2
    {
        float m_x;
        float m_y;

        Vector2();
        Vector2(float x, float y);
        Vector2(const Vector2& value);

        Vector2 One();

        Vector2 operator+(const Vector2& value) const;
        Vector2 operator-(const Vector2& value) const;

        Vector2 operator*(const float& value) const;
        Vector2 operator/(const float& value) const;

        float Magnitude() const;
        float MagnitudeSqrt() const;

        void Normalize();
        Vector2 Normalized() const;

        Vector2& operator+=(const Vector2& value);
        Vector2& operator-=(const Vector2& value);
        Vector2& operator*=(float value);
        Vector2& operator/=(float value);

        bool operator==(const Vector2& value)const;
        bool operator!=(const Vector2& value)const;
    };
    std::ostream& operator<<(std::ostream& os, const Vector2& value);
#endif