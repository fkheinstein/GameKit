#ifndef __RENDERER2D_H__
#define __RENDERER2D_H__


#include "Renderer/Renderer.h"
#include "Resource/Resource.h"


# ifdef _WIN32
# undef DrawText
# endif

namespace fts
{


    class Font;
    class Texture;
    //class ShaderCache;

    class  Renderer2D : protected Renderer 
    {
    public:
        static void Init(ShaderCache& shaders);
        static void Begin();
        static void End();

        static void Reset();
        static std::string GetDebugInfo();

        static void SetTextOrigin(int x, int y);
        static glm::ivec2 GetTextCursor();

        static void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color, uint32_t entity_id = -1);
        static void DrawQuad(const glm::vec3& pos, const glm::quat& rot, const glm::vec2& scale, const glm::vec4& color, uint32_t entity_id = -1);
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color,   uint32_t entity_id = -1);

        static void DrawTexture(const Texture& texture,  const std::array<glm::vec2, 2>& uv,
            const glm::vec3& pos, const glm::quat& rot, const glm::vec2& scale, const glm::vec4& color = glm::vec4(1.0f), uint32_t entity_id = -1);

        static void DrawTexture(const Texture& texture, const std::array<glm::vec2, 2>& uv, const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f),  uint32_t entity_id = -1);
        static void DrawTexture(const Texture& texture, const glm::vec3& pos, const glm::quat& rot, const glm::vec2& scale, const glm::vec4& color = glm::vec4(1.0f), uint32_t entity_id = -1);
        static void DrawTexture(const Texture& texture, const glm::mat4& transform,  const glm::vec4& color = glm::vec4(1.0f), uint32_t entity_id = -1);

        static void DrawBillboard(const Texture& texture, const std::array<glm::vec2, 2>& uv,
            const glm::vec3& pos, const glm::vec2& scale, const glm::vec4& color = glm::vec4(1.0f), uint32_t entity_id = -1);

        static void DrawBillboard(const Texture& texture, const glm::vec3& pos,
            const glm::vec2& scale, const glm::vec4& color = glm::vec4(1.0f), uint32_t entity_id = -1);

        static void DrawText(const Font& font, const std::string& text, const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f),  uint32_t entity_id = -1);
        static void DrawCircle(const glm::vec3& pos, const glm::vec2& scale, const glm::vec4& color, float thickness, float fade, uint32_t entity_id = -1);
        static void DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness, float fade,  uint32_t entity_id = -1);

    private:
        static void StartBatch();
        static void Flush();

        static void StartLineBatch();
        static void StartQuadBatch();
        static void StartCircleBatch();

        static void FlushLines();
        static void FlushQuads();
        static void FlushCircles();

        static void NextLineBatch();
        static void NextQuadBatch();
        static void NextCircleBatch();
    };
} // namespace fts

#endif // __RENDERER2D_H__