#ifndef B4A482BA_C1C1_43B3_8A2E_25BA619DB63A
#define B4A482BA_C1C1_43B3_8A2E_25BA619DB63A



#include "CameraController.h"
#include "PerspectiveCamera.h"


namespace fts {

    class PerspectiveCameraController : public CameraController
    {
    public:
        PerspectiveCameraController(float aspectRatio, bool rotation = false);
        ~PerspectiveCameraController() = default;


        virtual void OnUpdate(const float& dt) override;
        //virtual void OnEvent(const Event& e) override;

        virtual void OnResize(uint32_t new_width, uint32_t new_height) override;
        virtual void OnScroll(float new_zoom_level) override;

        const Ref<Camera>& GetCamera() const;

        void ReadjustCameraTranslationSpeed();
    private:
        Ref<Camera> m_Camera;

        float m_AspectRatio = 1.22f;


        float m_FieldOfView;
        bool m_Rotation;

        glm::vec3 mCameraPosition = { 0.0f, 0.0f, 0.0f };
        glm::vec3 mCameraRotation = { 0.0f, 0.0f, 0.0f };

        float mCameraRotationSpeed;
        float mCameraTranslationSpeed;
    };

}

#endif /* B4A482BA_C1C1_43B3_8A2E_25BA619DB63A */
