#include <spch.h>


#include "Graphics/PointShadow.h"


namespace fts
{
    PointShadow::PointShadow() : m_far_z(25.f), m_near_z(1.f) {}

void PointShadow::CreateShadowMap(int32_t width, int32_t height)
{
    m_framebuffer = Framebuffer::Create();
    m_shadow_map = Texture::Create(width, height, 0, MultiSampleLevel::None,
                                   TextureType::Cube, DataFormat::Depth24);
    m_framebuffer->Attach(*m_shadow_map, 0, 0);
}

void PointShadow::DestroyShadowMap()
{
    m_shadow_map.reset();
    m_framebuffer.reset();
}

    
} // namespace fts
