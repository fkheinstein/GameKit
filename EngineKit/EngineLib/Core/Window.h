#ifndef __WINDOW_H__
#define __WINDOW_H__


#include "Core/EventStack.h"
#include "Core/Layer.h"
#include "Renderer/Graphics.h"

namespace fts
{

    struct WindowCreateInfo
    {
        std::string title;
        int width;
        int height;
        MultiSampleLevel msaa;
        bool vsync;
    };

    class Window
    {
    public:
        static Scope<Window> Create(const WindowCreateInfo &info);

        Window();
        virtual ~Window() = default;

        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;

        virtual void PollEvents(EventStack<Layer *> &layers) = 0;

        virtual glm::ivec2 GetSize() const = 0;
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
        virtual MultiSampleLevel GetMSAA() const = 0;
        virtual bool GetIsVSync() const = 0;

        virtual std::string GetTitle() const = 0;

        virtual void ImGuiInitBackend() = 0;
        virtual void ImGuiShutdown() = 0;
        virtual void ImGuiNewFrame() = 0;
        virtual void ImGuiRenderDrawData() = 0;

        virtual void SwapBuffer() = 0;

        bool ShouldClose();
        void SetShouldClose(bool shouldClose);

    private:
        bool m_should_close;
    };

} // namespace fts

#endif // __WINDOW_H__