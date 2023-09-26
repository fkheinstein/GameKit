#include <spch.h>

#include "FPSCameraController.h"


namespace fts
{
     FPSCameraController::FPSCameraController(float aspectRatio, bool rotation)
        :
        m_Rotation(rotation),
        m_CameraRotationSpeed(45.f),
        m_CameraTranslationSpeed(10.f)
    {

        m_Camera = CreateRef<FPSCamera>(aspectRatio/*, 45.0f, 0.1f, 10000.0f*/);

    }


    void FPSCameraController::OnUpdate(const float& dt) {

        auto camObj = dynamic_cast<FPSCamera*>(m_Camera.get());
        //auto camObj = dynamic_cast<FPSCamera&>(*m_Camera);
        //float translationSpeed = m_CameraTranslationSpeed;

        /*
        mKeyLogConsoleChanged = false;

        if (InputCore::IsKeyDown(Key::KEY_LSHIFT))
        {
            //translationSpeed *= 10;
        }

        if (InputCore::IsKeyDown(Key::KEY_A)) {
            camObj->Translate(-m_CameraTranslationSpeed * m_Camera->GetRight() * (float)dt);
            mKeyLogConsoleChanged = true;
        }
        if (InputCore::IsKeyDown(Key::KEY_D)) {
            camObj->Translate(m_CameraTranslationSpeed * m_Camera->GetRight() * (float)dt);
            mKeyLogConsoleChanged = true;
        }

        if (InputCore::IsKeyDown(Key::KEY_W)) {
            camObj->Translate(-m_CameraTranslationSpeed * m_Camera->GetForward() * (float)dt);
            mKeyLogConsoleChanged = true;
        }
        if (InputCore::IsKeyDown(Key::KEY_S)) {
            camObj->Translate(m_CameraTranslationSpeed * m_Camera->GetForward() * (float)dt);
            mKeyLogConsoleChanged = true;
        }

        if (InputCore::IsKeyDown(Key::KEY_Q))
        {
            camObj->Translate(-m_CameraTranslationSpeed * m_Camera->GetUp() * (float)dt);
            mKeyLogConsoleChanged = true;

        }
        else  if (InputCore::IsKeyDown(Key::KEY_E))
        {
            camObj->Translate(m_CameraTranslationSpeed * m_Camera->GetUp() * (float)dt);
            mKeyLogConsoleChanged = true;
        }


        if (mKeyLogConsoleChanged)
        {
            //auto logString = fmt::format("FPSCameraController Update Changed");
            //Console::log("[FTS] :", logString);

            mKeyLogConsoleChanged = false;

            auto camPosition = camObj->GetPosition();
            auto camRot = camObj->GetRotation();
            //FTS_CORE_INFO("Camera position is: x:{0} y:{1} z:{2}", camPosition.x, camPosition.y, camPosition.z);
            //FTS_CORE_INFO("Camera rotation is: x:{0} y:{1} z:{2}", camRot.x, camRot.y, camRot.z);
        }


        if (m_Rotation)
        {
            if (InputCore::IsMouseButtonDown(Mouse::MouseCode::BUTTON_LEFT))
            {
                if (m_MouseFirstMoved)
                {
                    m_LastMousePositionX = InputCore::GetMouseX();
                    m_LastMousePositionY = InputCore::GetMouseY();
                    m_MouseFirstMoved = false;
                }

                m_CursorOffsetX = (float)InputCore::GetMouseX() - m_LastMousePositionX; // Pitch
                m_CursorOffsetY = m_LastMousePositionY - (float)InputCore::GetMouseY(); // Yaw


                m_LastMousePositionX = InputCore::GetMouseX();
                m_LastMousePositionY = InputCore::GetMouseY();


                m_CameraRotationSpeed = 0.15f;
                glm::vec3 m_CameraRotation = { 0.0f, 0.0f, 0.0f };


                m_CameraRotation.x -= m_CursorOffsetY * m_CameraRotationSpeed ; // Pitch
                m_CameraRotation.y -= m_CursorOffsetX * m_CameraRotationSpeed ; // Yaw

                dynamic_cast<FPSCamera&>(*m_Camera).Rotate(m_CameraRotation.y, m_CameraRotation.x, true);
            }
        }

      

        if (InputCore::IsMouseButtonReleased(Mouse::MouseCode::BUTTON_LEFT))
        {
            m_MouseFirstMoved = true;
        }

        */
    }

    void FPSCameraController::OnResize(uint32_t width, uint32_t height)
    {
        
        std::dynamic_pointer_cast<FPSCamera>(m_Camera)->SetViewportSize(width, height);
    }

    void FPSCameraController::OnScroll(float offset)
    {
        std::dynamic_pointer_cast<FPSCamera>(m_Camera)->Scroll(offset);
    }


   /* void FPSCameraController::OnEvent(const Event& evt)
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


    void FPSCameraController::OnMouseMove(const fts::evt::MouseMovedEvent& evt) {    }
    void FPSCameraController::OnMousePress(const fts::evt::MouseButtonPressedEvent& evt) {    }
    void FPSCameraController::OnMouseRelease(const fts::evt::MouseButtonReleasedEvent& evt) {    }
    
} // namespace fts
