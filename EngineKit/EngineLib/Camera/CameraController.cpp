#include <spch.h>


#include <Camera/CameraController.h>
#include <Camera/Camera.h>




namespace fts
{

    glm::mat4 CameraController::GetProjectionMatrix() const { return GetCamera()->GetProjectionMatrix(); }
    glm::mat4 CameraController::GetViewMatrix() const { return GetCamera()->GetViewMatrix();; }
    glm::mat4 CameraController::GetViewProjectionMatrix() const { return GetCamera()->GetViewProjectionMatrix();; }


    void CameraController::AddListeners()
    {
        FTS_CORE_INFO("[Camera::AddListeners()] Add listeners.");

        mKeyPressed = fts::evt::EventManager::eventDispatcher.appendListener(
            fts::evt::EventType::KeyPressed,

            eventpp::argumentAdapter<void(const fts::evt::KeyPressedEvent&)>(
                [this](const fts::evt::KeyPressedEvent& t_event) {

                    if (t_event.GetKeyCode() == fts::Keycode::W || t_event.GetKeyCode() == fts::Keycode::Up)
                    {

                    }
                }
            )
        );

    }


} // namespace fts


