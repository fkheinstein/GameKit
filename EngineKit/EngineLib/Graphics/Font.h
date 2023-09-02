#ifndef __FONT_H__
#define __FONT_H__

namespace fts
{

    class Texture;

    struct Character
    {
        Character() = default;
        Ref<Texture> glyph;
        std::array<glm::vec2, 2> uv;
        glm::ivec2 size;
        glm::ivec2 bearing;
        uint32_t advance;
    };

    class Font
    {
    public:
        Font(uint32_t pixel_height);
        ~Font() = default;

        Font(const Font &) = delete;
        Font operator=(const Font &) = delete;

        uint32_t GetPixelHeight() const { return m_pixel_height; }
        const Character &GetCharacter(char32_t ch) const;

        void SetCharacter(char32_t utf32, const Character &ch);
        void SetCharacter(char32_t utf32, Character &&ch);

    private:
        uint32_t m_pixel_height;
        std::unordered_map<char32_t, Character> m_characters;
    };

} // namespace fts

#endif // __FONT_H__