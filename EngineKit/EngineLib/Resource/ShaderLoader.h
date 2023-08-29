#ifndef __SHADERLOADER_H__
#define __SHADERLOADER_H__

#include "Graphics/Shader.h"

namespace fts
{
    class ShaderLoader
    {
    public:
        Ref<Shader> Load(const std::string &comp_path);
        Ref<Shader> Load(const std::string &vert_path, const std::string &frag_path);
        Ref<Shader> Load(const std::string &vert_path, const std::string &frag_path, const std::string &geo_path);
    };
} // namespace fts

#endif // __SHADERLOADER_H__