#ifndef __MOUSEEVENT_H__
#define __MOUSEEVENT_H__

#include "Event.h"
#include "Core/Mouse.h"

namespace fts::evt
{
    class MouseMovedEvent : public Event
    {
    private:
        float mouseX;
        float mouseY;

    public:
        MouseMovedEvent(float x, float y);

        [[nodiscard]] float GetX() const;
        [[nodiscard]] float GetY() const;

        [[nodiscard]] std::string ToString() const override;

        EVENT_CLASS_TYPE(MouseMoved)
    };

    class MouseScrolledEvent : public Event
    {
    private:
        float xOffset, yOffset;

    public:
        MouseScrolledEvent(float xOffset, float yOffset);

        [[nodiscard]] float GetXOffset() const;
        [[nodiscard]] float GetYOffset() const;

        [[nodiscard]] std::string ToString() const override;

        EVENT_CLASS_TYPE(MouseScrolled)
    };

    class MouseButtonEvent : public Event
    {
    protected:
        MouseButton button;

    public:
        [[nodiscard]] MouseButton GetMouseButton() const;

    protected:
        explicit MouseButtonEvent(MouseButton button);
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonPressedEvent(MouseButton button);

        [[nodiscard]] std::string ToString() const override;

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonReleasedEvent(const MouseButton button);

        [[nodiscard]] std::string ToString() const override;

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

} // namespace fts::evt

#endif // __MOUSEEVENT_H__