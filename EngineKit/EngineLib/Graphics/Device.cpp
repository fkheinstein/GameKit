#include <spch.h>


#include "Core/Base.h"
#include "Graphics/Device.h"
#include "Graphics/OpenGL/GLDevice.h"


namespace fts
{
    static Device::API s_api = Device::API::OpenGL;

    Device::API Device::GetAPI() { return s_api; }

    void Device::SetAPI(API api) { s_api = api; }

    Scope<Device> Device::Create()
    {
        FTS_CORE_TRACE("Initializing Graphics Deivce...");
        Scope<Device> device;
        switch (s_api)
        {
        case API::OpenGL:
            device = CreateScope<GLDevice>();
            break;
        default:
            FTS_CORE_ERROR("Unsupported API!");
            break;
        }
        return device;
    }
} // namespace fts