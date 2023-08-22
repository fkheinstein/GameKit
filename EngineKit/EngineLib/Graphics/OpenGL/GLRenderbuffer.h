#ifndef __GLRENDERBUFFER_H__
#define __GLRENDERBUFFER_H__


#include "Graphics/Renderbuffer.h"
#include "Utils/OpenGLLibInclude.h"


namespace fts
{
    class GLRenderbuffer : public Renderbuffer
    {
    public:
        GLRenderbuffer(int width, int height, MultiSampleLevel samples, DataFormat format);

        uint32_t Handle() const override { return m_id; }

    private:
        void Allocate();
        GLuint m_id;
    };

} // namespace fts


#endif // __GLRENDERBUFFER_H__