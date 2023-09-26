#ifndef __FPSCAMERA_H__
#define __FPSCAMERA_H__

#include "Camera/Camera.h"

namespace fts
{
    class FPSCamera : public Camera
    {
    public:
        FPSCamera(float aspectRatio, float fov = 60.f, float near_ = 0.1f, float far_ = 10000.0f);

        void SetProjection(float aspectRatio, float fov = 45.0f, float near_ = 0.1f, float far_ = 10000.0f);

        inline void SetFOV(float FOV)
        {
            m_Fov = FOV;
            RecalculateViewProjection();
        };
        
        void Scroll(float offset);
        void Rotate(float offsetX, float offsetY, bool constrainPitch = true);
        void Translate(const glm::vec3 &translation);

        void SetViewportSize(unsigned int width, unsigned int height);

    private:
        void RecalculateViewProjection() override;
        void RecalculateProjection();

        glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

        float m_Fov = glm::radians(45.0f);
        float m_Aspect = 1280.0f / 720.0f;
        float m_Near = 0.1f;
        float m_Far = 10000.0f;

        float m_Yaw;
        float m_Pitch;
        float m_MovementSpeed;
        float m_MouseSensitivity;
    };

}

#endif // __FPSCAMERA_H__