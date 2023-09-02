#ifndef __FONTLOADER_H__
#define __FONTLOADER_H__

typedef struct FT_LibraryRec_ *FT_Library;
typedef struct FT_FaceRec_ *FT_Face;

namespace fts
{

    class Font;
    class FontLoader
    {
    public:
        FontLoader();
        ~FontLoader();

        Ref<Font> Load(const std::string &path, int32_t pixel_height);

    private:
        void LoadGlyph(FT_Face face, Font *font);
        void LoadRangedGlyph(FT_Face face, Font *font, char32_t start, char32_t end);

        FT_Library m_library;
    };
} // namespace fts

#endif // __FONTLOADER_H__