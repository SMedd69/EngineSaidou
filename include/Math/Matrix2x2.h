#ifndef __MATRIX2X2_H
    #define __MATRIX2X2_H

    #include <Math/Vector2.h>

    struct Matrix2x2
    {
        public:
            float m[2][2];

            Matrix2x2();
            Matrix2x2(float m00, float m01, float m10, float m11);
            Matrix2x2(const Vector2& a, const Vector2& b);

            float& operator ()(int i, int j);
            const float& operator ()(int i, int j)const;

            Matrix2x2& operator +=(const Matrix2x2& b);
            Matrix2x2& operator -=(const Matrix2x2& b);
            Matrix2x2& operator *=(const float& s);
            Matrix2x2& operator *=(const Matrix2x2& b);
            bool operator==(const Matrix2x2& value)const;
	        bool operator!=(const Matrix2x2& value)const;

            Matrix2x2 Transpose()const;
            Matrix2x2 Inverse()const;
            float Determinant()const;

            static Matrix2x2 Identity();
            static Matrix2x2 Rotate(const float& angle);
            static Matrix2x2 Scale(const Vector2& scale);
            static Matrix2x2 RS(const float& angle, const Vector2& scale);
    };

    Matrix2x2 operator +(const Matrix2x2& a, const Matrix2x2& b);
    Matrix2x2 operator -(const Matrix2x2& a, const Matrix2x2& b);
    Matrix2x2 operator *(const Matrix2x2& a, const float& s);
    Matrix2x2 operator *(const float& s, const Matrix2x2& a);
    Matrix2x2 operator *(const Matrix2x2& a, const Matrix2x2& b);

    std::ostream& operator<<(std::ostream& os, const Matrix2x2& value);

    Vector2 operator*(const Matrix2x2& a, const Vector2& b);
    Vector2 operator*(const Vector2& b, const Matrix2x2& a);

#endif