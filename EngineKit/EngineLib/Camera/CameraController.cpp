#include <spch.h>


#include <Camera/CameraController.h>
#include <Camera/Camera.h>


#include <eventpp/utilities/argumentadapter.h>


namespace fts
{

    glm::mat4 CameraController::GetProjectionMatrix() const { return GetCamera()->GetProjectionMatrix(); }
    glm::mat4 CameraController::GetViewMatrix() const { return GetCamera()->GetViewMatrix();; }
    glm::mat4 CameraController::GetViewProjectionMatrix() const { return GetCamera()->GetViewProjectionMatrix();; }


    void CameraController::AddListeners()
    {
        FTS_CORE_INFO("[Camera::AddListeners()] Add listeners.");

        mKeyPressed = fts::event::EventManager::event_dispatcher.appendListener(
            fts::event::FtsEventType::KEY_PRESSED,

            eventpp::argumentAdapter<void(const event::KeyPressedEvent&)>(
                [this](const event::KeyPressedEvent& t_event) {


                    if (t_event.Key == fts::Keycode::W || t_event.Key == fts::Keycode::Up)
                    {

                    }
                }    
            )
        );
    }


} // namespace fts


