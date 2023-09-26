#include <spch.h>


#include "SkyboxRenderPass.h"

#include "Graphics/Device.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"
#include "Graphics/Framebuffer.h"
#include "Resource/Resource.h"
#include "Renderer/Renderer.h"

#include "Camera/Camera.h"


namespace fts
{

    static ShaderHandle s_skybox_shader;
    static const Texture* s_skybox;

    void SkyboxRenderPass::Init(ShaderCache& shaders, const Texture* skybox)
    {
        s_skybox_shader = shaders.Load("shader/skybox", "assets/shaders/skybox.vert.glsl", "assets/shaders/skybox.frag.glsl");
        s_skybox = skybox;
    }

    void SkyboxRenderPass::Render()
    {
        int index = 0;
        RenderOperation op;
        op.depth_func = DepthFunc::LessEqual;
        Renderer::BeginRenderSubpass(RenderSubpassInfo{ &index, 1, op });

        Camera* camera = Renderer::GetCamera();

        Vector3f pos = camera->GetPosition();
        Matrix4f projection = camera->GetViewProjectionMatrix() * glm::translate(Matrix4f(1.0f), pos);


        s_skybox_shader->GetParam("u_projection")->SetAsMat4(&projection[0][0]);
        s_skybox_shader->GetParam("u_skybox")->SetAsTexture(s_skybox);

        Renderer::DrawNDCBox(*s_skybox_shader);

        Renderer::EndRenderSubpass();
    }

}