#ifndef __FPSCAMERACONTROLLER_H__
#define __FPSCAMERACONTROLLER_H__


#include "CameraController.h"
#include "FPSCamera.h"

namespace fts
{
  class FPSCameraController : public CameraController
    {
    public:
        FPSCameraController(float aspectRatio, bool rotation = false);
        ~FPSCameraController() = default;


        virtual void OnUpdate(const float& dt) override;    
        //virtual void OnEvent(const Event& e) override;
        
        virtual void OnResize(uint32_t new_width, uint32_t new_height) override;
        virtual void OnScroll(float new_zoom_level) override;

        virtual const Ref<Camera>& GetCamera() const { return m_Camera; };

    private:
        void OnMouseMove(const fts::evt::MouseMovedEvent& evt);
        void OnMousePress(const fts::evt::MouseButtonPressedEvent& evt);
        void OnMouseRelease(const fts::evt::MouseButtonReleasedEvent& evt);

    private:
        Ref<Camera> m_Camera;

        bool m_Rotation;

        float m_CameraTranslationSpeed = 5.0f;  //0.05f
        float m_CameraRotationSpeed = 0.1f;


        bool m_Cursor = true;


        float m_CursorOffsetX = 0.0f; // Yaw
        float m_CursorOffsetY = 0.0f; // Pitch
        float m_LastMousePositionX = 0.0f;
        float m_LastMousePositionY = 0.0f;

        glm::vec2 mLastMousePosition = { 0.0f ,0.0f };
        bool m_MouseFirstMoved = true;

        bool mKeyLogConsoleChanged = false;
    };

} // namespace fts



#endif // __FPSCAMERACONTROLLER_H__