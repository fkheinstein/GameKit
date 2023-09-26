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

      

        auto mWindowResize = fts::evt::EventManager::eventDispatcher.appendListener(
            fts::evt::EventType::WindowResize,

            eventpp::argumentAdapter<void(const fts::evt::WindowResizeEvent&)>(
                [this](const fts::evt::WindowResizeEvent& evt) {

                    //FTS_CORE_TRACE(evt.ToString());
                    this->OnResize(evt.GetWidth(), evt.GetHeight());
                }
            )
        );

        fts::evt::EventManager::eventDispatcher.appendListener(
            fts::evt::EventType::MouseScrolled,

            eventpp::argumentAdapter<void(const fts::evt::MouseScrolledEvent&)>(
                [this](const fts::evt::MouseScrolledEvent& evt) {

                    //FTS_CORE_TRACE(evt.ToString());
                    this->OnScroll(evt.GetXOffset()/*, evt.GetHeight()*/);
                }
            )
        );
    }


} // namespace fts


