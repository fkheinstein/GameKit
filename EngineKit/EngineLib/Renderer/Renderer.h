#ifndef __RENDERER_H__
#define __RENDERER_H__


#include <Graphics/Graphics.h>


namespace fts
{

    class Framebuffer;
    class UniformBuffer;
    class Camera;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;

    class Shader;
    class Device;

    struct CameraData {
        glm::mat4 projection;
        glm::mat4 view;
        //glm::mat4 inView;
    };

    struct RenderOperation {
        bool depth_test{ true };
        bool depth_mask{ true };

        DepthFunc depth_func{ DepthFunc::Less };

        bool blend{ true };

        bool face_culling{ true };
        Face cull_face{ Face::Back };
    };


    struct RendererData {
        Ref<UniformBuffer> camera_ubo;
        CameraData camera_data;
        Camera* camera;

        Ref<VertexArray> quad_vao;
        Ref<VertexBuffer> quad_vbo;
        Ref<IndexBuffer> quad_ibo;

        Ref<VertexArray> box_vao;
        Ref<VertexBuffer> box_vbo;
        Ref<IndexBuffer> box_ibo;

        bool is_subpass_begin{ false };
    };


    struct RenderPassInfo {
        Framebuffer* framebuffer;
        int32_t viewport_width;
        int32_t viewport_height;

        RenderOperation op{};
        BufferBitMask clear_mask{ BufferBitMask::ColorBufferBit |  BufferBitMask::DepthBufferBit };
        std::array<float, 4> clear_value{ 0.f, 0.f, 0.f, 1.0f };
    };

    struct RenderSubpassInfo {
        const int* draw_buffer;
        int draw_buffer_count;
        RenderOperation op{};
    };


    class Renderer 
    {
    public:

        static void Init(Device* device);
        static void BeginRenderPass(const RenderPassInfo& info);
        static void BeginRenderSubpass(const RenderSubpassInfo& info);
        static void EndRenderSubpass();
        static void EndRenderPass();
        static void Submit(const Shader& shader, const VertexArray& vao,  MeshTopology topology, size_t count, size_t offset,   bool index = true);
        static void ComputeImage(const Shader& shader, int32_t width,   int32_t height, int32_t depth);


        static const RenderPassInfo& GetCurrentRenderPass();

        static bool IsEmptyStack();

        static void SetCamera(Camera& camera);
        static Camera* GetCamera();

        static void BindCamera(Shader& shader);

        static void DrawNDCQuad(const Shader& shader);
        static void DrawNDCBox(const Shader& shader);


        // blit current renderpass framebuffer content to draw_fb
        // static void BlitToBuffer(int read_attachment, Framebuffer *draw_fb, int draw_attachment, BufferBitMask mask);
        // blit read_fb content to current renderpass's framebuffer
        // static void BlitFromBuffer(int draw_attachment, Framebuffer *read_fb,  int read_attachment, BufferBitMask mask);

    protected:
        static void SetRenderState(Framebuffer* framebuffer, int32_t viewport_width,  int32_t viewport_height,  const RenderOperation& op);

        static Device* s_device;
        static RendererData s_data;
    };



} // namespace fts

#endif // __RENDERER_H__