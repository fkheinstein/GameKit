#include <spch.h>


#include "Graphics/VertexArray.h"
#include "Graphics/Device.h"
#include "Graphics/Graphics.h"
#include "Graphics/OpenGL/GLVertexArray.h"



namespace fts
{
    Ref<VertexArray> VertexArray::Create()
    {
        Ref<VertexArray> va;

        switch (Device::GetAPI()) 
        {
        case Device::API::OpenGL:
            va = CreateRef<GLVertexArray>();
            break;
        default:
            FTS_CORE_ERROR("Unsupported API!");
            break;
        }
        return va;
    }

} // namespace fts
