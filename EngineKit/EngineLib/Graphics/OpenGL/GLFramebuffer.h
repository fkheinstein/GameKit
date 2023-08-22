#ifndef __GLFRAMEBUFFER_H__
#define __GLFRAMEBUFFER_H__


#include "Graphics/Framebuffer.h"
#include <vector>

namespace fts
{
    class GLFramebuffer : public Framebuffer {
    public:
        GLFramebuffer();
        virtual ~GLFramebuffer();

        uint32_t Handle() const override { return m_id; }

        void Attach(Texture& texture, int attachment, int level) override;
        void Attach(Renderbuffer& buffer, int attachment) override;
        Texture* GetAttachment(int attachment) override
        {
            return m_textures.at(attachment);
        }
        void Prepare() override;

        void ClearDepth(const float depth) override;

        void ClearAttachment(uint32_t attachment_id, const int* value) override;
        void ClearAttachment(uint32_t attachment_id,
            const uint32_t* value) override;
        void ClearAttachment(uint32_t attachment_id, const float* value) override;

    private:
        int32_t m_width;
        int32_t m_height;
        GLuint m_id;
        std::vector<Texture*> m_textures;
        std::vector<GLenum> m_drawables;
    };


} // namespace fts


#endif // __GLFRAMEBUFFER_H__