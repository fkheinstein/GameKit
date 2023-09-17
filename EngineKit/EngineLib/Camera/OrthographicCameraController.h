#ifndef __ORTHOGRAPHICCAMERACONTROLLER_H__
#define __ORTHOGRAPHICCAMERACONTROLLER_H__


#include <Camera/CameraController.h>
#include <Camera/OrthographicCamera.h>


namespace fts {


    struct OrthographicCameraBounds
    {
        float Left, Right;
        float Bottom, Top;

        float GetWidth() { return Right - Left; }
        float GetHeight() { return Top - Bottom; }
    };

    class OrthographicCameraController : public CameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);
        ~OrthographicCameraController() = default;


        /*void OnUpdate(const TimeStep& dt) override;
        void OnEvent(const Event& e) override;*/
        virtual void On(const KeyEvent&) override;
        virtual void On(const MouseMotionEvent&) override;
        virtual void On(const MouseButtonEvent&) override;
        virtual void On(const MouseWheelEvent&) override;

        void OnResize(uint32_t new_width, uint32_t new_height) override;
        void OnScroll(float new_zoom_level) override;       



        virtual const Ref<Camera>& GetCamera() const { return m_Camera; };

        [[nodiscard]] const OrthographicCamera& GetOrthoCamera() const { return dynamic_cast<OrthographicCamera&>(*m_Camera.get()); }


        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }

        const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

        void ReCalculateView();


        virtual void ImGuiControls(bool* isOpen) override;

    private:
        Ref<Camera> m_Camera;
        OrthographicCameraBounds m_Bounds;

        float m_ZoomLevel = 1.0f;
        float m_AspectRatio = 1.33f;
        float m_CameraTranslationSpeed = 5.0;
        float m_CameraRotationSpeed = 180.0;;
        float m_ScrollSpeed = 0.1f;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_CameraRotation = { 0.0f, 0.0f, 0.0f };

        bool m_Rotation = true;


        bool m_ShouldUpdate = false;

    };
}
#endif // __ORTHOGRAPHICCAMERACONTROLLER_H__