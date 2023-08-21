#ifndef F38262CF_3444_402A_B459_AD0DB5E24205
#define F38262CF_3444_402A_B459_AD0DB5E24205

#include "Core/Layer.h"
#include "Core/Window.h"


#ifdef FTS_IMGUI
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>
#endif


namespace fts
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer(Window *window);

        ~ImGuiLayer();

        void Begin();

        void End();

        ImGuiContext *GetContext() const { return m_context; }

    private:
        void SetDarkThemeColor();
        ImGuiContext *m_context;
        Window *m_window;
    };
} // namespace fts

#endif /* F38262CF_3444_402A_B459_AD0DB5E24205 */
