#ifndef __GLSHADER_H__
#define __GLSHADER_H__

#include "Core/Base.h"
#include "Graphics/Shader.h"

namespace fts
{
    class UniformBuffer;

    class GLShader : public Shader
    {
    public:
        GLShader();

        ~GLShader();

        uint32_t Handle() const override { return m_id; }

        ShaderParam *GetParam(int32_t index) override;
        ShaderParam *GetParam(const std::string &name) override;

        void CompileShader(ShaderType type, const std::string &code) override;

        void LinkShaders() override;

        void SetUniformBuffer(const std::string &name,
                              const UniformBuffer &buffer) override;

        uint32_t GetUint(const std::string &name) const override;

        glm::ivec3 GetLocalGroupSize() const override;

    private:
        static void CheckCompileErrors(uint32_t shader, const std::string &type);

        void DestroyShaders();

        int32_t GetUniformCount() const;
        int32_t GetUniformBufferCount() const;

        GLuint m_id;
        GLuint m_vertexId;
        GLuint m_fragmentId;
        GLuint m_geometryId;
        GLuint m_computeId;

        std::unordered_map<std::string, ShaderParam *> m_params;
        uint32_t m_texture_cnt;
        uint32_t m_image_cnt;
    };

} // namespace fts

#endif // __GLSHADER_H__