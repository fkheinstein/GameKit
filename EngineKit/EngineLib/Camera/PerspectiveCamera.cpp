#include <spch.h>

#include "PerspectiveCamera.h"


namespace fts
{
    PerspectiveCamera::PerspectiveCamera(float aspectRatio, float fieldOfView) : Camera()
    {

        SetProjection(aspectRatio, fieldOfView, 0.0f, 5000.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }


    void PerspectiveCamera::SetProjection(float aspect_ratio, float field_of_view, float near_field, float far_field)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(field_of_view), aspect_ratio, near_field, far_field);

        RecalculateViewProjection();
    }


    void PerspectiveCamera::SetProjection(float aspectRatio, float fieldOfView)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.0f, 5000.0f);

        RecalculateViewProjection();
    }




    void PerspectiveCamera::RecalculateViewProjection()
    {
        glm::vec3 direction;
        direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        direction.y = sin(glm::radians(Pitch));
        direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        CameraFront = glm::normalize(direction);

        m_ViewMatrix = glm::lookAt(m_Position, m_Position - CameraFront, GetUp());
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }




    /*void PerspectiveCamera::CalculateVector()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));
        front.y = sin(glm::radians(m_Rotation.x));
        front.z = sin(glm::radians(m_Rotation.y)) * cos(glm::radians(m_Rotation.x));

        m_CameraForward = glm::normalize(front);
        m_CameraRight = glm::normalize(glm::cross(m_WorldUp, m_CameraForward));
        m_CameraUp = glm::normalize(glm::cross(m_CameraForward, m_CameraRight));

        glm::mat4 projTrans = glm::perspective(glm::radians(45.0f), (float)1280.0f / (float)720.0f, 0.1f, 100.0f);
        m_ViewProjection = projTrans * glm::lookAt(m_Position, m_Position + m_CameraForward, m_CameraUp);
    }*/
} // namespace fts



