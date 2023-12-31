#ifndef __GLDEVICE_H__
#define __GLDEVICE_H__


#include "Graphics/Device.h"

namespace fts
{
    class GLDevice : public Device {
    public:
        GLDevice();

        void DispatchCompute(int32_t num_group_x, int32_t num_group_y,  int32_t num_group_z) override;

        void MemoryBarrier(BarrierBit bit) override;

        void DrawElements(MeshTopology topology, int count, size_t offset) override;

        void DrawElementsInstanced(MeshTopology topology, int count, size_t offset,  size_t amount) override;

        void DrawArrays(MeshTopology topology, int first, int count) override;

        void SetLineWidth(float width) override;

        void SetClearColor(float r, float g, float b, float a) override;

        void Clear(BufferBitMask bit) override;

        void SetVertexArray(const VertexArray* vertexArray) override;

        void SetShader(const Shader* shader) override;

        void SetViewport(int x, int y, int width, int height) override;

        void SetFramebuffer(const Framebuffer* framebuffer) override;

        void SetPolygonMode(PolygonMode mode, Face face) override;

        void SetDepthMask(bool depth_mask) override;

        void Enable(Operation operation) override;

        void Disable(Operation operation) override;

        void SetCullFace(Face face) override;

        void SetDepthfunc(DepthFunc depth_func) override;

        void DrawBuffer(Framebuffer* fb, int buf) override;

        void DrawBuffers(Framebuffer* fb, int n, const int* buf) override;

        void ReadBuffer(const Framebuffer* fb, int buf) override;

        void BlitFramebuffer(const Framebuffer* src, int src_x, int src_y,
            int src_width, int src_height, Framebuffer* dst,
            int dst_x, int dst_y, int dst_width, int dst_height,
            BufferBitMask mask, BlitFilter filter) override;

        void ReadPixels(int x, int y, int width, int height, DataFormat format,  void* data) override;  
    };

} // namespace fts


#endif // __GLDEVICE_H__