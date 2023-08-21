#ifndef __INPUTDEVICE_H__
#define __INPUTDEVICE_H__


#include "Core/Base.h"
#include "Core/Keyboard.h"
#include "Core/Mouse.h"


namespace fts
{
    class  InputDevice {
    public:
        bool IsKeyDown(Keycode keycode);
        bool WasKeyDown(Keycode keycode);
        bool IsKeyPressed(Keycode keycode);

        bool IsMouseDown(MouseButton mouse);
        bool WasMouseDown(MouseButton mouse);
        bool IsMousePressed(MouseButton mouse);

        glm::vec2 GetMouseCoord();
        glm::vec2 GetMouseWheel();

        void Tick();

        void SetKeyState(Keycode keycode, bool state);
        void SetMouseButtonState(MouseButton mouse, bool state);
        void SetMouseCoord(float x, float y);
        void SetMouseWheel(float x, float y);

    private:
        std::unordered_map<Keycode, bool> m_key;
        std::unordered_map<Keycode, bool> m_last_key;

        std::unordered_map<MouseButton, bool> m_mouse_button;
        std::unordered_map<MouseButton, bool> m_last_mouse_button;

        glm::vec2 m_mouse_wheel;
        glm::vec2 m_mouse_coord;
    };
} // namespace fts

#endif // __INPUTDEVICE_H__