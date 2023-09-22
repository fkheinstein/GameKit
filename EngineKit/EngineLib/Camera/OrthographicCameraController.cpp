#include <spch.h>

#include "OrthographicCameraController.h"


namespace fts
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel })
        , m_AspectRatio(aspectRatio)
        , m_Rotation(rotation)
        , m_ZoomLevel(2.0f)
    {
        m_Camera = CreateRef<OrthographicCamera>(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        m_CameraPosition = m_Camera->GetPosition();
        m_CameraRotation = m_Camera->GetRotation();

    }


    void OrthographicCameraController::OnResize(uint32_t width, uint32_t height)
    {
        m_AspectRatio = (float)width / (float)height;
        ReCalculateView();
    }

    void OrthographicCameraController::ReCalculateView()
    {
        m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
        dynamic_cast<OrthographicCamera&>(*m_Camera).SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
    }


    void OrthographicCameraController::OnScroll(float offset)
    {
        m_ZoomLevel += offset * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        ReCalculateView();
    }



    void CameraController::AddListeners()
    {
        FTS_CORE_INFO("[Camera::AddListeners()] Add listeners.");

        /*mKeyPressed = fts::event::EventManager::event_dispatcher.appendListener( fts::event::FtsEventType::KEY_PRESSED,

            eventpp::argumentAdapter<void(const event::KeyPressedEvent&)>(
                [this](const event::KeyPressedEvent& t_event) {


                    if (t_event.Key == fts::Keycode::W || t_event.Key == fts::Keycode::Up)
                    {

                    }
                }
            )
        );*/
    }


    void OrthographicCameraController::On(const KeyEvent& e) {
    
        if (!e.state) return;


        /*if (InputCore::IsKeyDown(Key::KEY_W)) { m_CameraPosition.y += m_CameraTranslationSpeed * dt; }
        if (InputCore::IsKeyDown(Key::KEY_S)) { m_CameraPosition.y -= m_CameraTranslationSpeed * dt; }
        if (InputCore::IsKeyDown(Key::KEY_A)) { m_CameraPosition.x -= m_CameraTranslationSpeed * dt; }
        if (InputCore::IsKeyDown(Key::KEY_D)) { m_CameraPosition.x += m_CameraTranslationSpeed * dt; }*/

        float dt = 0.015f;

        switch (e.keycode) {
        default:
            break;

        case Keycode::W: {

        } break;
        case Keycode::S: {

        } break;
        case Keycode::A: {

        } break;
        case Keycode::D: {

        } break;

        case Keycode::E: {
            if (m_Rotation == true)
            {
                m_CameraRotation.z -= m_CameraRotationSpeed * dt;
            }
        } break;

        case Keycode::Q: {
            if (m_Rotation == true)
            {
                m_CameraRotation.z += m_CameraRotationSpeed * dt;
            }
        } break;
        }

        if (m_CameraRotation.z > 180.0f)
            m_CameraRotation.z -= 360.0f;
        else if (m_CameraRotation.z <= -180.0f)
            m_CameraRotation.z += 360.0f;

        m_Camera->SetRotation(m_CameraRotation);
        m_Camera->SetPosition(m_CameraPosition);
    }


    void OrthographicCameraController::On(const MouseMotionEvent&) {}

    void OrthographicCameraController::On(const MouseButtonEvent&) {}

    void OrthographicCameraController::On(const MouseWheelEvent&) {}

    void OrthographicCameraController::ImGuiControls(bool* isOpen)
    {
        if (*isOpen)
        {
            if (ImGui::Begin("Orthographic Camera Controls", isOpen))
            {
                if (ImGui::DragFloat3("Position", glm::value_ptr(m_CameraPosition), 0.1f))
                {
                    m_ShouldUpdate = true;
                }

                if (ImGui::DragFloat("Rotation", &m_CameraRotation.z, 1.0f))
                {
                    m_ShouldUpdate = true;
                }

                ImGui::DragFloat("Movement Speed", &m_CameraTranslationSpeed, 0.1f);
                ImGui::DragFloat("Rotation Speed", &m_CameraRotationSpeed, 0.5f);
                ImGui::DragFloat("Zoom Speed", &m_ScrollSpeed, 0.01f);
                ImGui::End();
            }
        }
    }
} // namespace fts


