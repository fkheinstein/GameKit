#include <spch.h>

#include "Graphics/Framebuffer.h"
#include "Graphics/Device.h"
#include "Graphics/OpenGL/GLFramebuffer.h"


namespace fts
{

Ref<Framebuffer> Framebuffer::Create()
{
    Ref<Framebuffer> framebuffer;
    switch (Device::GetAPI()) {
        case Device::API::OpenGL:
            framebuffer = CreateRef<GLFramebuffer>();
            break;
        default:
            FTS_CORE_ERROR("Unsupported API!");
            break;
    }
    return framebuffer;
}

} // namespace fts

