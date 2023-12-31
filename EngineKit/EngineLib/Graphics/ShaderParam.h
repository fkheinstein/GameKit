#ifndef __SHADERPARAM_H__
#define __SHADERPARAM_H__


#include "Graphics/Texture.h"

#include <string>
#include <cstdint>

namespace fts
{
    enum class UniformType
    {
        Unknown = 0,
        Bool,
        Int,
        UInt,
        Float,
        Double,
        Sampler,
        Image
    };

    class ShaderParam
    {
    public:
        ShaderParam(UniformType type, const std::string &name, int32_t index)
            : m_type(type), m_name(name), m_index(index){};

        virtual ~ShaderParam() = default;

        UniformType GetType() const { return m_type; }

        virtual const std::string &GetName() const { return m_name; };

        int32_t GetIndex() const { return m_index; }

        virtual void SetAsBool(bool value) = 0;

        virtual void SetAsInt(int value) = 0;

        virtual void SetAsUint(uint32_t value) = 0;

        virtual void SetAsFloat(float value) = 0;

        virtual void SetAsVec(const int *value, int32_t count = 1) = 0;
        virtual void SetAsVec(const float *value, int32_t count = 1) = 0;

        virtual void SetAsVec2(const float *value, int32_t count = 1) = 0;
        virtual void SetAsVec3(const float *value, int32_t count = 1) = 0;
        virtual void SetAsVec4(const float *value, int32_t count = 1) = 0;
        virtual void SetAsMat3(const float *value, int32_t count = 1) = 0;
        virtual void SetAsMat4(const float *value, int32_t count = 1) = 0;

        virtual void SetAsTexture(const Texture *texture) = 0;
        virtual void SetAsTextures(const Texture **texture, int count) = 0;
        virtual void SetAsImage(const Texture *texture, int32_t level, bool layered,  int32_t layer, Access access) = 0;

    private:
        UniformType m_type;
        std::string m_name;
        int32_t m_index;
    };

} // namespace fts

#endif // __SHADERPARAM_H__