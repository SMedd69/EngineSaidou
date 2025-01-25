#ifndef __VECTOR3_H__
    #define __VECTOR3_H__

    #include <ostream>

    struct Vector3
    {
        static const Vector3 Right;
        static const Vector3 Up;
        static const Vector3 Forward;

        float m_x;
        float m_y;
        float m_z;

        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector3& value);

        Vector3 One();

        Vector3 operator+(const Vector3& value) const;
        Vector3 operator-(const Vector3& value) const;

        Vector3 operator*(const float& value) const;
        Vector3 operator/(const float& value) const;

        float Magnitude() const;
        float MagnitudeSqrt() const;

        void Normalize();
        Vector3 Normalized() const;

        Vector3& operator+=(const Vector3& value);
        Vector3& operator-=(const Vector3& value);
        Vector3& operator*=(float value);
        Vector3& operator/=(float value);

        bool operator==(const Vector3& value)const;
        bool operator!=(const Vector3& value)const;

        static Vector3 CrossProduct(const Vector3& a, const Vector3& b);
        Vector3 Cross(const Vector3& other) const;
        static float DotProduct(const Vector3& a, const Vector3& b);
        static Vector3 Orthogonal(const Vector3& v);
        static Vector3 Lerp(const Vector3& v, const Vector3& v2, float t);
        static Vector3 Slerp(const Vector3& v, const Vector3& v2, float t, bool longPath);

        // To String()
        std::string ToString()const;
    };
    std::ostream& operator<<(std::ostream& os, const Vector3& value);
#endif