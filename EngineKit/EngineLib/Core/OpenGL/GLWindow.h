#ifndef A6EA8710_2812_473C_91C5_76456078B9CA
#define A6EA8710_2812_473C_91C5_76456078B9CA

#pragma once

#include "Core/Base.h"
#include "Core/Window.h"

class SDL_Window;

namespace fts
{
    class GLWindow : public Window {
    public:
        GLWindow(const WindowCreateInfo& info);
        ~GLWindow();
        void PollEvents(EventStack<Layer*>& layers) override;

        glm::ivec2 GetSize() const override;
        int GetWidth() const override;
        int GetHeight() const override;
        MultiSampleLevel GetMSAA() const override;

        bool GetIsVSync() const override;

        std::string GetTitle() const override;

        void ImGuiInitBackend() override;
        void ImGuiShutdown() override;
        void ImGuiNewFrame() override;
        void ImGuiRenderDrawData() override;


        virtual void* GetNativeWindow() const  override;
        //virtual GraphicsContext* GetGraphicsContext() const  override;

        
    private:
        void SwapBuffer() override;

        void* m_context;
        SDL_Window* m_window;
        bool m_is_init_imgui;

        //fts::event::MouseButton::Code ConvertToButton(uint8_t button);
    };
} // namespace fts

#endif /* A6EA8710_2812_473C_91C5_76456078B9CA */
