#include <spch.h>

#include "Core/InputLayer.h"
#include "Core/InputDevice.h"



namespace fts
{
    InputLayer::InputLayer(InputDevice *input) : Layer("InputLayer"), m_input(input)
    {
    }

    void InputLayer::OnTick(float) 
    {
        m_input->Tick(); 
    }

    void InputLayer::On(const KeyEvent &event)
    {
        m_input->SetKeyState(event.keycode, event.state);
    }

    void InputLayer::On(const MouseMotionEvent &event)
    {
        m_input->SetMouseCoord(event.x, event.y);
    }

    void InputLayer::On(const MouseButtonEvent &event)
    {
        m_input->SetMouseCoord(event.x, event.y);
        m_input->SetMouseButtonState(event.button, event.state);
    }

    void InputLayer::On(const MouseWheelEvent &event)
    {
        m_input->SetMouseWheel(event.x, event.y);
    }
} // namespace fts
