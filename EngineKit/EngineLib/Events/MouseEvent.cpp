#include <spch.h>

#include <Events/MouseEvent.h>

namespace fts::evt
{

    std::string MouseMovedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
        return ss.str();
    }

    float MouseMovedEvent::GetX() const { return mouseX; }

    float MouseMovedEvent::GetY() const { return mouseY; }

    MouseMovedEvent::MouseMovedEvent(float x, float y) : mouseX(x), mouseY(y) {}

    MouseScrolledEvent::MouseScrolledEvent(float xOffset, float yOffset) : xOffset(xOffset), yOffset(yOffset) {}

    float MouseScrolledEvent::GetXOffset() const { return xOffset; }

    float MouseScrolledEvent::GetYOffset() const { return yOffset; }

    std::string MouseScrolledEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
        return ss.str();
    }

    MouseButton MouseButtonEvent::GetMouseButton() const { return button; }

    MouseButtonEvent::MouseButtonEvent(MouseButton button) : button(button) {}

    std::string MouseButtonPressedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << (uint32_t)button;
        return ss.str();
    }

    MouseButtonPressedEvent::MouseButtonPressedEvent(MouseButton button) : MouseButtonEvent(button) {}

    MouseButtonReleasedEvent::MouseButtonReleasedEvent(const MouseButton button) : MouseButtonEvent(button) {}

    std::string MouseButtonReleasedEvent::ToString() const
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << (uint32_t)button;
        return ss.str();
    }
}