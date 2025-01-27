#ifndef __TRANSFORM_H__
    #define __TRANSFORM_H__

    #include <Math/Vector3.h>
    #include <Math/Matrix4x4.h>
    #include <Math/Quaternion.h>
    #include <Engine/Component.h>

    struct Transform : public Component
    {
        Vector3 m_position;
        Vector3 m_scale;
        Quaternion m_rotation;
        public:
        Transform();
        Transform(Vector3 position, Vector3 scale, Quaternion rotation);

        void SetPosition(const Vector3& position);
        void SetScale(const Vector3& scale);
        void SetEulerAngles(const Vector3& eulerAngles);
        void SetRotation(const Quaternion& rotation);

        Vector3 GetPosition();
        Vector3 GetScale();
        Vector3 GetEulerAngles();
        Quaternion GetRotation();

        Matrix4x4 TransformMatrix()const;
    };
#endif