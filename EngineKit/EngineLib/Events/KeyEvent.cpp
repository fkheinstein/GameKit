#include <spch.h>

#include <Events/KeyEvent.h>

namespace fts::evt
{
    Keycode KeyEvent::GetKeyCode() const
    {
        return keyCode;
    }

    KeyEvent::KeyEvent(const Keycode keyCode)  : keyCode(keyCode)
    {
    }

    KeyPressedEvent::KeyPressedEvent(Keycode keyCode, bool isRepeat) : KeyEvent(keyCode), isRepeat(isRepeat) {}

    bool KeyPressedEvent::GetIsRepeat()
    {
        return isRepeat;
    }

    std::string KeyPressedEvent::toString()
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << (uint32_t)keyCode << ", " << isRepeat;
        return ss.str();
    }

    KeyReleasedEvent::KeyReleasedEvent(Keycode keyCode) : KeyEvent(keyCode)
    {
    }

    std::string KeyReleasedEvent::toString()
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << (uint32_t)keyCode;
        return ss.str();
    }

    KeyTypedEvent::KeyTypedEvent(Keycode keyCode) : KeyEvent(keyCode)
    {
    }

    std::string KeyTypedEvent::toString()
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << (uint32_t)keyCode;
        return ss.str();
    }
}