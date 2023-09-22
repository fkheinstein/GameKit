#ifndef __EVENT2_H__
#define __EVENT2_H__




#include <Core/Keyboard.h>


namespace fts::evt {

    enum class EventType {
        None = 0,

        // Window
        WindowClose,
        WindowResize,
        WindowFocus,

        // App
        AppTick,
        AppUpdate,
        AppRender,

        // Key
        KeyPressed,
        KeyReleased,
        KeyTyped,

        // Mouse
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    class Event {
    public:
        virtual ~Event() = default;

        [[nodiscard]] virtual EventType GetEventType() const = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
        [[nodiscard]] virtual std::string ToString() const { return GetName(); }
    };

    struct EventPolicies {
        static EventType getEvent(const Event& e);
    };

#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

}

namespace fts::event
{

    //-------------------------------------------------
    // Types
    //-------------------------------------------------

    enum class FtsEventType
    {
        // default
        NONE,
        EVENT_QUIT,

        // keyboard events
        KEY_PRESSED,
        KEY_RELEASED,

        // mouse events
        MOUSE_BUTTON_PRESSED,
        MOUSE_BUTTON_RELEASED,
        MOUSE_MOVED_EVT,
        MOUSE_SCROLLED_EVT,
        MOUSE_ENTER_EVT,
    };

    //-------------------------------------------------
    // Event base class
    //-------------------------------------------------

    struct FtsEvent
    {
        FtsEvent() = default;
        virtual ~FtsEvent() = default;

        FtsEventType type{FtsEventType::NONE};
    };

    //-------------------------------------------------
    // Keyboard events
    //-------------------------------------------------

    struct QuitEvent : FtsEvent
    {
        explicit QuitEvent()
        {
            type = FtsEventType::EVENT_QUIT;
        }
    };


    struct KeyPressedEventV2 : FtsEvent
    {
        int key;
        int repeatCount;

        explicit KeyPressedEventV2(const int t_key, const int t_repeatCount = 0) : key{ t_key }, repeatCount{ t_repeatCount }
        {
            type = FtsEventType::KEY_PRESSED;
        }
    };

    struct KeyReleasedEventV2 : FtsEvent
    {
        int key;
        explicit KeyReleasedEventV2(const int t_key) : key{ t_key }
        {
            type = FtsEventType::KEY_RELEASED;
        }
    };

    struct  KeyPressedEvent : FtsEvent
    {
        Keycode Key;
        uint16_t Mod {0};
        bool Repeat{ false };
        explicit KeyPressedEvent(Keycode t_key, bool t_repeatCount = false) : Key{ t_key }, Repeat{ t_repeatCount }
        {
            type = FtsEventType::KEY_PRESSED;
        }
    };

    struct  KeyReleasedEvent : FtsEvent
    {
        Keycode Key;
        uint16_t Mod{ 0 };
        explicit KeyReleasedEvent(Keycode t_key) : Key{ t_key }
        {
            type = FtsEventType::KEY_RELEASED;
        }
    };



    //-------------------------------------------------
    // Mouse events
    //-------------------------------------------------


    struct MouseButton {
        enum class Code : uint8_t {
            None = 0,
            Left,
            Right,
            Middle,

            Count,
            Invalid = 0xFF,
        };

        enum class State : uint8_t {
            Release = 0,
            Press
        };

        enum class WheelDirection : uint8_t {
            Normal,
            Flipped
        };
    };


    struct MouseMoveEvt : FtsEvent {
        uint32_t PosX = 0;
        uint32_t PosY = 0;

        float DeltaX = 0.0f;
        float DeltaY = 0.0f;

        explicit MouseMoveEvt() {
            type = FtsEventType::MOUSE_MOVED_EVT;
        }
    };


    struct MouseButtonReleasedEvt : FtsEvent {
        uint32_t X = 0;;
        uint32_t Y = 0;;
        uint8_t Clicks = 0;        

        MouseButton::Code Button = MouseButton::Code::None;
        MouseButton::State ButtonState = MouseButton::State::Release;

        explicit MouseButtonReleasedEvt() {
            type = FtsEventType::MOUSE_BUTTON_RELEASED;
        }
    };

    struct MouseButtonPressedEvt : FtsEvent {
        uint32_t X = 0;
        uint32_t Y = 0;
        uint8_t Clicks = 0;

        MouseButton::Code Button = MouseButton::Code::None;
        MouseButton::State ButtonState = MouseButton::State::Release;

        explicit MouseButtonPressedEvt() {
            type = FtsEventType::MOUSE_BUTTON_PRESSED;
        }
    };

    struct MouseWheelEvt : FtsEvent {
        float Y = 0.0f;
        float X = 0.0f;
        float DeltaY = 0.0f;
        float DeltaX = 0.0f;

        MouseButton::WheelDirection direction = MouseButton::WheelDirection::Normal;

        explicit MouseWheelEvt() {
            type = FtsEventType::MOUSE_SCROLLED_EVT;
        }
    };




    struct MouseButtonPressedEvent : FtsEvent
    {
        int button;
        explicit MouseButtonPressedEvent(const int t_button) : button{t_button}
        {
            type = FtsEventType::MOUSE_BUTTON_PRESSED;
        }
    };

    struct MouseButtonReleasedEvent : FtsEvent
    {
        int button;

        explicit MouseButtonReleasedEvent(const int t_button) : button{t_button}
        {
            type = FtsEventType::MOUSE_BUTTON_RELEASED;
        }
    };

    struct MouseMovedEvent : FtsEvent
    {
        float x;
        float y;

        MouseMovedEvent(const float t_x, const float t_y): x{t_x}, y{t_y} {
            type = FtsEventType::MOUSE_MOVED_EVT;
        }
    };

    struct MouseScrolledEvent : FtsEvent
    {
        float xOffset;
        float yOffset;

        MouseScrolledEvent(const float t_xOffset, const float t_yOffset) : xOffset{t_xOffset}, yOffset{t_yOffset} {
            type = FtsEventType::MOUSE_SCROLLED_EVT;
        }
    };

    struct MouseEnterEvent : FtsEvent
    {
        bool enter;
        explicit MouseEnterEvent(const bool t_enter) : enter{t_enter}
        {
            type = FtsEventType::MOUSE_ENTER_EVT;
        }
    };

} // namespace fts::event




#endif // __EVENT2_H__