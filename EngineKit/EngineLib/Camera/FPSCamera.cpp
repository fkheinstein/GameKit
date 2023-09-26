#include <spch.h>


#include "FPSCamera.h"


namespace fts
{

    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 5.0f;
    const float SENSITIVITY = 0.1f;
    const float NEAR_PLANE = 0.1f;
    const float FAR_PLANE = 10000.0f;


    FPSCamera::FPSCamera(float aspect, float fov, float near_, float far_) :
        m_MovementSpeed(SPEED),
        m_MouseSensitivity(SENSITIVITY),
        m_Yaw(YAW),
        m_Pitch(PITCH)
    {
        m_Fov = fov;
        m_Aspect = aspect;
        m_Near = near_;
        m_Far = far_;

        RecalculateProjection();
    }

    void FPSCamera::SetProjection(float aspect, float fov, float near_, float far_)
    {
        m_Fov = fov;
        m_Aspect = aspect;
        m_Near = near_;
        m_Far = far_;

        RecalculateProjection();
    }



    void FPSCamera::SetViewportSize(unsigned int width, unsigned int height)
    {
        m_Aspect = (float)width / (float)height;
        RecalculateProjection();
    }


    void FPSCamera::Translate(const glm::vec3& translation)
    {
        m_Position += translation;
        RecalculateViewProjection();
    }


    void FPSCamera::Scroll(float offset)
    {
        if (m_Fov >= 1.0f && m_Fov <= 75.0f)
            m_Fov -= offset;

        else if (m_Fov <= 1.0f)
            m_Fov = 1.0f;
        else if (m_Fov >= 75.0f)
            m_Fov = 75.0f;

        RecalculateProjection();
    }


    // Process mouse movement
    void FPSCamera::Rotate(float offsetX, float offsetY, bool constrainPitch)
    {
        offsetX *= m_MouseSensitivity;
        offsetY *= m_MouseSensitivity;

        m_Yaw += offsetX;
        m_Pitch += offsetY;


        if (constrainPitch)
            m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

        RecalculateViewProjection();
    }

    void FPSCamera::RecalculateProjection()
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
        RecalculateViewProjection();
    }

    // calculates the front vector from the Camera's (updated) Euler Angles
    void FPSCamera::RecalculateViewProjection()
    {
        m_Rotation = glm::vec3(m_Pitch, m_Yaw, 0.0f);

        //Calculate the new forward vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
        front.y = sin(glm::radians(m_Rotation.x));
        front.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
        m_CameraFront = glm::normalize(front);

        //Re-calculate the right and up vector
        m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
        m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));

        //Re-calculate view matrix
        m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}