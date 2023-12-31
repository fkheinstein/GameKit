#include <spch.h>


#include <Renderer/SpriteRenderPass.h>
#include <Renderer/Renderer2D.h>
#include <ECS/Component.h>


namespace fts
{
    struct SpriteDrawData {
        const Texture* texture;
        std::array<glm::vec2, 2> uvs;
        Vector3f pos;
        glm::quat rot;
        glm::vec2 size;
        uint32_t entity_id;
        int priority;
    };

    static TextureCache* s_textures;


    void SpriteRenderPass::Init(TextureCache& textures) { s_textures = &textures; }

    void SpriteRenderPass::Render(const Scene& scene)
    {
        int index[] = { 0, 1 };
        RenderOperation op;
        op.depth_mask = false;
        Renderer::BeginRenderSubpass(RenderSubpassInfo{ index, 2, op });
        Renderer2D::Begin();

        std::vector<SpriteDrawData> datas;
        auto sprite_view = scene.view<SpriteComponent, TransformComponent>();
        sprite_view.each([&](entt::entity entity_id,
            const SpriteComponent& sprite_comp,
            const TransformComponent& transform_comp) {
                uint32_t id = static_cast<uint32_t>(entity_id);
                auto& frame = sprite_comp.frame;
                if (s_textures->Contains(frame.texture_id)) {
                    datas.push_back({ s_textures->Get(frame.texture_id).Get(), frame.uvs,
                                     transform_comp.GetWorldPosition(),
                                     transform_comp.GetWorldRotation(), frame.size, id,
                                     frame.priority });
                }
            });


       /* auto anim_view = scene.view<SpriteAnimationComponent, TransformComponent>();
        anim_view.each([&](entt::entity entity_id,
            const SpriteAnimationComponent& anim_comp,
            const TransformComponent& transform_comp) {
                uint32_t id = static_cast<uint32_t>(entity_id);
                auto anim = anim_comp.animator.GetAnimation();
                if (anim) {
                    if (anim->GetFrameSize()) {
                        auto& frame = anim->GetFrame();
                        if (s_textures->Contains(frame.texture_id)) {
                            datas.push_back({ s_textures->Get(frame.texture_id).Get(),
                                             frame.uvs,
                                             transform_comp.GetWorldPosition(),
                                             transform_comp.GetWorldRotation(),
                                             frame.size, id, frame.priority });
                        }
                    }
                }
            });*/

        std::sort(datas.begin(), datas.end(), [](const auto& lhs, const auto& rhs) {
            auto l_z = lhs.pos.z;
            auto r_z = rhs.pos.z;
            auto l_p = lhs.priority;
            auto r_p = rhs.priority;
            if (l_z < r_z) {
                return true;
            }
            else if (l_z > r_z) {
                return false;
            }
            else {
                return l_p < r_p;
            }
            });

        for (const auto& data : datas) {
            Renderer2D::DrawTexture(*data.texture, data.uvs, data.pos, data.rot, data.size, Vector4f(1.0f), data.entity_id);
        }

        // auto textView = entities.view<TransformComponent, TextComponent>();

       // textView.each([&](entt::entity entity_id,
       //                   const TransformComponent &transformComp,
       //                   const TextComponent &textComp) {
       // Renderer2D::SetTextOrigin(0, 0);
       // if (resource.Exist<Font>(textComp.font_id)) {
       //     auto font = resource.GetResource<Font>(textComp.font_id);
       //     Renderer2D::DrawText(*font, textComp.text,
       //                          transformComp.GetWorldTransform().GetMatrix(),
       //                          textComp.color,
       //                          static_cast<uint32_t>(entity_id));
       // }
       // });
        Renderer2D::End();

        Renderer::EndRenderSubpass();
    }

} // namespace fts