#ifndef __TRANSFORMATION_UTILITIES_H__
    #define __TRANSFORMATION_UTILITIES_H__

    #include <Math/Vector2.h>
    #include <algorithm>
    #include <math.h>

    class TransformationUtilities
    {
        public:
        static Vector2 Identity(const Vector2& a);
        static Vector2 Translation(const Vector2& a, const Vector2& b);
        static Vector2 Scale(const Vector2& a, float s);

        static Vector2 Homothety(const Vector2& a, const Vector2& b, float s);
        static Vector2 PointReflection(const Vector2& a, const Vector2& center);

        static Vector2 AxialSymmetry(const Vector2& a, const Vector2& axe);
        static Vector2 AxialSymmetry(const Vector2& a, const Vector2& axe, const Vector2& center);

        static Vector2 Rotation(const Vector2& a, const float angle);
        static Vector2 Rotation(const Vector2& a, const Vector2& center, const float angle);

        static float Repeat(float t, float length);
        static float PingPong(float t, float length);

        private:
        TransformationUtilities() {};
        static float DotProduct(const Vector2& a, const Vector2& b);
    };
#endif