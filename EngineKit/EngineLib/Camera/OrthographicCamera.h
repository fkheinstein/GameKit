#ifndef __ORTHOGRAPHICCAMERA_H__
#define __ORTHOGRAPHICCAMERA_H__


#include <Camera/Camera.h>

namespace fts {

    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera() = default;
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);


    private:
        void RecalculateViewProjection() override;
    };

}

#endif // __ORTHOGRAPHICCAMERA_H__