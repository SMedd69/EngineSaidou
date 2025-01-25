#ifndef __MATRIX4X4_H
    #define __MATRIX4X4_H

    #include <ostream>
    #include <math.h>
    #include <Math/Vector3.h>
    #include <Math/Vector4.h>
	#include <Math/Quaternion.h>
    #include <array>

    struct Matrix4x4
{
public:
	float m[4][4];

	Matrix4x4();
	Matrix4x4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	Matrix4x4(const Vector3& a, const Vector3& b, const Vector3& c);
	Matrix4x4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d);

	Matrix4x4(const Matrix4x4& value);

	float& operator ()(int i, int j);
	const float& operator ()(int i, int j)const;

	Matrix4x4& operator +=(const Matrix4x4& b);
	Matrix4x4& operator -=(const Matrix4x4& b);
	Matrix4x4& operator *=(const float& s);
	Matrix4x4& operator *=(const Matrix4x4& b);
	bool operator==(const Matrix4x4& value)const;
	bool operator!=(const Matrix4x4& value)const;


	Matrix4x4 Transpose()const;
	Matrix4x4 Inverse()const;
	float Determinant()const;

	static Matrix4x4 Identity();
	static Matrix4x4 Translate(const Vector3& translate);
	static Matrix4x4 RotateX(const float& angle);
	static Matrix4x4 RotateY(const float& angle);
	static Matrix4x4 RotateZ(const float& angle);
	static Matrix4x4 Rotate(const Vector3& angles);
	static Matrix4x4 Rotate(const Quaternion& q);
	static Matrix4x4 ScaleXYZ(const Vector3& scale);

	static Matrix4x4 TS(const Vector3& translate, const Vector3& scale);
	static Matrix4x4 RS(const Quaternion& rotation, const Vector3& scale);
	static Matrix4x4 TR(const Vector3& translate, const Quaternion& v);
	static Matrix4x4 TRS(const Vector3& translate, const Quaternion& rotation, const Vector3& scale);
	static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float near, float far);
	static Matrix4x4 Perspective(float left, float right, float bottom, float top, float near, float far); //Work
	static Matrix4x4 Perspective(float fov, float aspect, float near, float far); //Work

	std::array<float, 16> GetAsArray() const;
};
Matrix4x4 operator +(const Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator -(const Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator *(const Matrix4x4& a, const float& s);
Matrix4x4 operator *(const float& s, const Matrix4x4& a);
Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x4& b);
std::ostream& operator<<(std::ostream& os, const Matrix4x4& value);

Vector3 operator*(const Matrix4x4& a, const Vector3& b);
Vector3 operator*(const Vector3& b, const Matrix4x4& a);
Vector4 operator*(const Vector4& b, const Matrix4x4& a);
Vector4 operator*(const Matrix4x4& a, const Vector4& b);

#endif