#include <spch.h>

#include "Keyboard.h"


#include <SDL.h>

namespace fts
{

    Scancode GetScancodeFromKeycode(Keycode keycode)
    {
        return static_cast<Scancode>( SDL_GetScancodeFromKey(static_cast<SDL_KeyCode>(keycode)));
    }

    Keycode GetKeycodeFromScancode(Scancode scancode)
    {
        return static_cast<Keycode>( SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(scancode)));
    }

} // namespace fts
