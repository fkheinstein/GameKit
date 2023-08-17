#ifndef __LAYER_H__
#define __LAYER_H__


#include <Core/Event.h>


namespace fts
{

    class Layer
    {
    public:
        Layer(const std::string &name) : m_name(name)
        {
            FTS_CORE_TRACE("Initializing layer: {}", name);
        }

        virtual ~Layer() { FTS_CORE_TRACE("Deleteing layer: {}", m_name); }

        Layer(const Layer &) = delete;

        Layer &operator=(const Layer &) = delete;

        virtual void OnPush() {}

        virtual void OnPop() {}

        virtual void OnTick(float) {}

        virtual void On(const WindowSizeEvent &) {}
        virtual void On(const KeyEvent &) {}
        virtual void On(const MouseMotionEvent &) {}
        virtual void On(const MouseButtonEvent &) {}
        virtual void On(const MouseWheelEvent &) {}
        virtual void On(const TextInputEvent &) {}
        virtual void On(const AppQuitEvent &) {}

        virtual void OnRender() {}

        virtual void OnImGui() {}

        const std::string &GetName() const { return m_name; }

    private:
        friend class Application;

        std::string m_name;
    };

} // namespace fts

#endif // __LAYER_H__