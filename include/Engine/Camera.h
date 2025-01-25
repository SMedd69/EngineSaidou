#ifndef __CAMERA_H__
    #define __CAMERA_H__

    #include <Math/Matrix4x4.h>
    #include <Math/Vector2.h>

    class Camera
    {
        private:
            Vector3 m_position;
            Vector3 m_angle;
            float m_size;

            bool m_isHorizontal;
            bool m_isPerspective;

            float m_near = 0.1f;
            float m_far = 1000.0f;

        public:
            Camera(Vector3 position, Vector3 angle, float size, bool isPerspective = true, bool isHorizontal = true);
            void SetPosition(const Vector3& position);
            void SetAngle(const Vector3& angle);
            void SetSize(float size);
            void SetSizeType(bool isHorizontal);

            void SetNear(float _near);
            void SetFar(float _far);
            void SetFov(float fov);

            // To String()
            std::string ToString()const;

            Vector2 GetVerticalAndHorizontalSize(float width, float height)const;
            Vector3 GetPosition()const;
            Vector3 GetAngle()const;

            float GetNear()const;
            float GetFar()const;
            float GetSize()const;
            bool GetSizeType()const;

            Matrix4x4 ViewMatrix()const;
            Matrix4x4 ProjectionMatrix(float windowWidth, float windowHeight)const;
    };

#endif