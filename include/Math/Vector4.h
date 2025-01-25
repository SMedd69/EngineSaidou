#ifndef __VECTOR4_H__
    #define __VECTOR4_H__

    #include <ostream>
    #include <math.h>
    #include <cfloat>

    #include <Math/Mathf.h>

    struct Vector4
    {
        float m_x;
        float m_y;
        float m_z;
        float m_w;

        Vector4();
        Vector4(float x, float y, float z, float w);
        Vector4(const Vector4& value);

        Vector4 operator+(const Vector4& value) const;
        Vector4 operator*(const float& value) const;
        Vector4 operator*(const Vector4& value) const;
        Vector4 operator-(const Vector4& value) const;
        Vector4 operator/(const float& value) const;

        float Magnitude() const;
        void Normalize();
        Vector4 Normalized() const;
        Vector4 GetSafeInvertedVector()const;

        Vector4& operator+=(const Vector4& value);
        Vector4& operator*=(const float& value);
        Vector4& operator*=(const Vector4& value);
        Vector4& operator-=(const Vector4& value);
        Vector4& operator/=(const float& value);
        bool operator==(const Vector4& value)const;
        bool operator!=(const Vector4& value)const;

        static float DotProduct(const Vector4& a, const Vector4& b);
    };
    std::ostream& operator<<(std::ostream& os, const Vector4& value);

#endif