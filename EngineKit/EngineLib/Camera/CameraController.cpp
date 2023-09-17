#include <spch.h>


#include <Camera/CameraController.h>
#include <Camera/Camera.h>


namespace fts
{

    glm::mat4 CameraController::GetProjectionMatrix() const { return GetCamera()->GetProjectionMatrix(); }
    glm::mat4 CameraController::GetViewMatrix() const { return GetCamera()->GetViewMatrix();; }
    glm::mat4 CameraController::GetViewProjectionMatrix() const { return GetCamera()->GetViewProjectionMatrix();; }

} // namespace fts


