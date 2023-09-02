#include <spch.h>


#include "Core/Base.h"
#include "Graphics/Texture.h"

#include "Graphics/Font.h"


namespace fts
{
Font::Font(uint32_t pixel_height) : m_pixel_height(pixel_height) {}

const Character &Font::GetCharacter(char32_t utf32) const
{
    if (m_characters.count(utf32) == 0) {
        FTS_ASSERT_MSG(false, "Error, character not loaded");
    }
    return m_characters.at(utf32);
}

void Font::SetCharacter(char32_t utf32, const Character &ch)
{
    m_characters[utf32] = ch;
}

void Font::SetCharacter(char32_t utf32, Character &&ch)
{
    m_characters[utf32] = std::move(ch);
}
    
    
} // namespace fts