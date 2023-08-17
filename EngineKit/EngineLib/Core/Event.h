#ifndef __EVENT_H__
#define __EVENT_H__


#include <Core/Mouse.h>
#include <Core/Keyboard.h>

namespace fts
{
    struct WindowSizeEvent
    {
        uint32_t width;
        uint32_t height;
    };

    struct KeyEvent
    {
        Keycode keycode;
        uint16_t mod;
        bool state;
    };

    struct MouseMotionEvent
    {
        int32_t x;
        int32_t y;
        int32_t x_rel;
        int32_t y_rel;
    };

    struct MouseButtonEvent
    {
        MouseButton button;
        int32_t x;
        int32_t y;
        uint8_t clicks;
        bool state;
    };

    struct MouseWheelEvent
    {
        int32_t x;
        int32_t y;
    };

    struct TextInputEvent
    {
        char text[32]; // std::string is not allowed in union
    };

    struct AppQuitEvent
    {
    };
} // namespace fts

#endif // __EVENT_H__