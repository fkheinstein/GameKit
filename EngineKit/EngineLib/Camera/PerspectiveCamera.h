#ifndef __PERSPECTIVECAMERA_H__
#define __PERSPECTIVECAMERA_H__

#include "Camera/Camera.h"


namespace fts 
{

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float aspectRatio, float fieldOfView = 60.f);
        //virtual ~PerspectiveCamera();

        void SetProjection(float aspect_ratio, float field_of_view /*= 45.f*/);
        void SetProjection(float aspect_ratio, float field_of_view, float near_field/* = 0.1f*/, float far_field = 5000.0f);

        glm::vec3 CameraFront;
        float Yaw = 0.f;
        float Pitch = 90.f;


    private:
        void RecalculateViewProjection();

    };
}



#endif // __PERSPECTIVECAMERA_H__