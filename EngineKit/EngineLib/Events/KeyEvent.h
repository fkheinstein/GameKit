#ifndef __KEYEVENT_H__
#define __KEYEVENT_H__

#include "Event.h"
#include "Core/Keyboard.h"


namespace fts::evt
{

    class KeyEvent : public Event
    {
    protected:
        Keycode keyCode;

    public:
        [[nodiscard]] Keycode GetKeyCode() const;

    protected:
        explicit KeyEvent(Keycode keyCode);
    };

    class KeyPressedEvent : public KeyEvent
    {
    private:
        bool isRepeat;

    public:
        explicit KeyPressedEvent(Keycode keyCode, bool isRepeat = false);

        bool GetIsRepeat();

        std::string toString();

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(Keycode keyCode);

        std::string toString();

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        explicit KeyTypedEvent(Keycode keyCode);

        std::string toString();

        EVENT_CLASS_TYPE(KeyTyped)
    };
} // namespace fts::evt

#endif // __KEYEVENT_H__