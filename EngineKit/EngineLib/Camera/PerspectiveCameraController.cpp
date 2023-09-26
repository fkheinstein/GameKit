#include <spch.h>

#include "PerspectiveCameraController.h"


namespace fts
{
    PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, bool rotation)
        :
        m_AspectRatio(aspectRatio),

        m_FieldOfView(45.f),
        m_Rotation(rotation),

        mCameraPosition(0.f, 0.f, 0.f),
        mCameraRotation(0.f),
        mCameraRotationSpeed(45.f),
        mCameraTranslationSpeed(0.5f)
    {
        m_Camera = CreateRef<PerspectiveCamera>(m_AspectRatio, m_FieldOfView);

        mCameraPosition = m_Camera->GetPosition();
        mCameraRotation = m_Camera->GetRotation();


        AddListeners();


        mKeyPressed = fts::evt::EventManager::eventDispatcher.appendListener(
            fts::evt::EventType::KeyPressed,

            eventpp::argumentAdapter<void(const fts::evt::KeyPressedEvent&)>(
                [this](const fts::evt::KeyPressedEvent& t_event) {

                    float dt = 0.016f;


                    if (t_event.GetKeyCode() == fts::Keycode::W) { mCameraRotation.y += mCameraTranslationSpeed * dt; }
                    if (t_event.GetKeyCode() == fts::Keycode::S) { mCameraRotation.y -= mCameraTranslationSpeed * dt; }
                    if (t_event.GetKeyCode() == fts::Keycode::A) { mCameraRotation.x += mCameraTranslationSpeed * dt; }
                    if (t_event.GetKeyCode() == fts::Keycode::D) { mCameraRotation.x -= mCameraTranslationSpeed * dt; }
                    

                    if (m_Rotation == true)
                    {
                        if (t_event.GetKeyCode() == fts::Keycode::Q) { mCameraRotation.y += mCameraRotationSpeed * dt; }
                        if (t_event.GetKeyCode() == fts::Keycode::E) { mCameraRotation.y -= mCameraRotationSpeed * dt; }

                        m_Camera->SetRotation(mCameraRotation);
                    }

                    m_Camera->SetPosition(mCameraPosition);

                    FTS_CORE_INFO("Camera position is: x:{0} y:{1} z:{2}", mCameraPosition.x, mCameraPosition.y, mCameraPosition.z);
                    FTS_CORE_INFO("Camera rotation is: {0}", mCameraRotation.y);
                }
            )
        );


      
    }



    
    void PerspectiveCameraController::OnUpdate(const float& dt)
    {
        /*if (InputCore::IsKeyDown(Key::KEY_W)) { mCameraPosition.y += mCameraTranslationSpeed * dt; }
        if (InputCore::IsKeyDown(Key::KEY_S)) { mCameraPosition.y -= mCameraTranslationSpeed * dt; }
        if (InputCore::IsKeyDown(Key::KEY_A)) { mCameraPosition.x -= mCameraTranslationSpeed * dt; }
        if (InputCore::IsKeyDown(Key::KEY_D)) { mCameraPosition.x += mCameraTranslationSpeed * dt; }


        if (m_Rotation == true)
        {
            if (InputCore::IsKeyDown(Key::KEY_Q)) { mCameraRotation.y += mCameraRotationSpeed * dt; }
            if (InputCore::IsKeyDown(Key::KEY_E)) { mCameraRotation.y -= mCameraRotationSpeed * dt; }

            m_Camera->SetRotation(mCameraRotation);
        }


        FTS_CORE_INFO("Camera position is: x:{0} y:{1} z:{2}", mCameraPosition.x, mCameraPosition.y, mCameraPosition.z);
        FTS_CORE_INFO("Camera rotation is: {0}", mCameraRotation.y);

        m_Camera->SetPosition(mCameraPosition);

        //ReadjustCameraTranslationSpeed();*/
    
    }
   

    void PerspectiveCameraController::OnResize(uint32_t width, uint32_t height)
    {
       // HZ_PROFILE_FUNCTION();

        m_AspectRatio = (float)width / (float)height;
        dynamic_cast<PerspectiveCamera&>(*m_Camera).SetProjection(m_AspectRatio, m_FieldOfView);
    }

    void PerspectiveCameraController::OnScroll(float offset) {

        //https://github.com/AlbertBoll/GEngine/blob/0ad6581b3104550070b519874a160756e78c1671/GEngine/src/Camera/PerspectiveCamera.cpp

        float fieldOfView = m_FieldOfView - offset;
        m_FieldOfView = fieldOfView;

        m_FieldOfView = glm::clamp(m_FieldOfView, 0.f, 90.f);
        dynamic_cast<PerspectiveCamera&>(*m_Camera).SetProjection(m_AspectRatio, m_FieldOfView);
    }

    const Ref<Camera>& PerspectiveCameraController::GetCamera() const
    {
        return m_Camera;
    }


    /*void PerspectiveCameraController::OnEvent(const Event& evt)
    {
        switch (evt.id)
        {
        case fts::EventType::FTS_EVENT_MOUSE_SCROLLED: {
            const auto& data = evt.get<MouseWheel>();
            OnScroll(data.Y);
            break;
        }

        case fts::EventType::FTS_EVENT_WINDOW_RESIZE: {
            const auto& data = evt.get<WindowResizeEvent>();
            OnResize(data.Width, data.Height);
            break;
        }

        default:
            break;
        }
    }*/

    void PerspectiveCameraController::ReadjustCameraTranslationSpeed()
    {
        mCameraTranslationSpeed = std::exp(1.f / m_FieldOfView);
    }
} // namespace fts



