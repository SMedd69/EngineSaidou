#ifndef __MATRIX3X3_H
    #define __MATRIX3X3_H
    #include <Math/Vector2.h>
    #include <math.h>
    #include <array>
    #include <ostream>

    /// @brief Matrice 3 x 3
    struct Matrix3x3
    {
        public:
            float m[3][3];

            Matrix3x3();
            Matrix3x3(float m00, float m01, float m02,
                    float m10, float m11, float m12,
                    float m20, float m21, float m22);

            Matrix3x3(const Matrix3x3& value);

            float& operator ()(int i, int j);
            const float& operator ()(int i, int j)const;

            Matrix3x3& operator +=(const Matrix3x3& b);
            Matrix3x3& operator -=(const Matrix3x3& b);
            Matrix3x3& operator *=(const float& s);
            Matrix3x3& operator *=(const Matrix3x3& b);
            bool operator==(const Matrix3x3& value)const;
            bool operator!=(const Matrix3x3& value)const;

            Matrix3x3 Transpose()const;
            Matrix3x3 Inverse()const;
            float Determinant()const;

            static Matrix3x3 Identity();
            static Matrix3x3 Translate(const Vector2& translate);
            static Matrix3x3 RotateZ(const float& angle);
            static Matrix3x3 ScaleXY(const Vector2& scale);

            static Matrix3x3 TS(const Vector2& translate, const Vector2& scale);
            static Matrix3x3 RS(const float& angle, const Vector2& scale);
            static Matrix3x3 TR(const Vector2& translate, const float& angle);
            static Matrix3x3 TRS(const Vector2& translate, const float& angle, const Vector2& scale);

            std::array<float, 9> GetAsArray() const;
        };

        Matrix3x3 operator +(const Matrix3x3& a, const Matrix3x3& b);
        Matrix3x3 operator -(const Matrix3x3& a, const Matrix3x3& b);
        Matrix3x3 operator *(const Matrix3x3& a, const float& s);
        Matrix3x3 operator *(const float& s, const Matrix3x3& a);
        Matrix3x3 operator *(const Matrix3x3& a, const Matrix3x3& b);

        std::ostream& operator<<(std::ostream& os, const Matrix3x3& value);

        Vector2 operator*(const Matrix3x3& a, const Vector2& b);
        Vector2 operator*(const Vector2& b, const Matrix3x3& a);

#endif