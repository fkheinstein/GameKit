#ifndef DC57BC98_63BC_4065_9465_168A366BF8FB
#define DC57BC98_63BC_4065_9465_168A366BF8FB

#include "Core/Base.h"
#include "Graphics/Graphics.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderbuffer.h"

namespace fts
{

    class Framebuffer
    {
    public:
        static Ref<Framebuffer> Create();
        Framebuffer() = default;
        virtual ~Framebuffer() = default;

        Framebuffer(const Framebuffer &) = delete;
        Framebuffer &operator=(const Framebuffer &) = delete;

        virtual uint32_t Handle() const = 0;
        virtual void Attach(Texture &texture, int attachment, int level) = 0;
        virtual void Attach(Renderbuffer &buffer, int attachment) = 0;
        virtual Texture *GetAttachment(int attachment) = 0;
        virtual void Prepare() = 0;

        virtual void ClearDepth(const float value = 1) = 0;

        virtual void ClearAttachment(uint32_t attachment_id, const int *value) = 0;
        virtual void ClearAttachment(uint32_t attachment_id,   const uint32_t *value) = 0;
        virtual void ClearAttachment(uint32_t attachment_id,   const float *value) = 0;
    };
} // namespace fts

#endif /* DC57BC98_63BC_4065_9465_168A366BF8FB */
