#include <spch.h>


#include "Graphics/Shader.h"
#include "Graphics/Graphics.h"
#include "Graphics/Device.h"
#include "Graphics/OpenGL/GLShader.h"


namespace fts
{
Ref<Shader> Shader::Create()
{
    Ref<Shader> shader;
    switch (Device::GetAPI()) {
        case Device::API::OpenGL:
            shader = CreateRef<GLShader>();
            break;
        default:
            FTS_CORE_ERROR("Unsupported API!");
            break;
    }
    return shader;
}

} // namespace fts
