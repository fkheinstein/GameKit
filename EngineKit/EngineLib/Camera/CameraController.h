#ifndef __CAMERACONTROLLER_H__
#define __CAMERACONTROLLER_H__



#include <Core/Event.h>
#include <Events/EventManager.h>

namespace fts {


    class Camera;
    enum Actions : uint16_t
    {
        MoveCameraRight,
        MoveCameraLeft,
        MoveCameraUp,
        MoveCameraDown,

        RotateCameraRight,
        RotateCameraLeft
    };

    class CameraController
    {
    public:
        virtual ~CameraController() = default;

        /*virtual void OnUpdate(const TimeStep& dt) = 0;
        virtual void OnEvent(const Event& e) = 0;*/


        virtual void OnScroll(float new_zoom_level) = 0;
        virtual void OnResize(uint32_t new_width, uint32_t new_height) = 0;
        virtual const Ref<Camera>& GetCamera() const = 0;
        virtual void ImGuiControls(bool* isOpen) {};

        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetViewProjectionMatrix() const;


        virtual void On(const KeyEvent&) {}
        virtual void On(const MouseMotionEvent&) {}
        virtual void On(const MouseButtonEvent&) {}
        virtual void On(const MouseWheelEvent&) {}


        virtual void AddListeners() ;

    protected:
        decltype(fts::evt::EventManager::eventDispatcher)::Handle mKeyPressed;
    };

}

#endif // __CAMERACONTROLLER_H__