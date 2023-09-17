#include <spch.h>

#include "OrthographicCamera.h"


namespace fts
{

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    {
        m_ViewMatrix = glm::mat4(1.0f);
        SetProjection(left, right, bottom, top);
    }


    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -100.0f, 100.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }


    void OrthographicCamera::RecalculateViewProjection() {

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
        glm::mat4 rotation = glm::mat4(1.f);

        rotation = glm::rotate(rotation, m_Rotation.x, glm::vec3(1.f, 0.f, 0.f));
        rotation = glm::rotate(rotation, m_Rotation.y, glm::vec3(0.f, 1.f, 0.f));
        rotation = glm::rotate(rotation, m_Rotation.z, glm::vec3(0.f, 0.f, 1.f));

        transform = transform * rotation;

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

    }

} // namespace fts


