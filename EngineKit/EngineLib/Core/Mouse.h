#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <cstdint>

namespace fts
{
    enum class MouseButton : uint8_t
    {
        Left = 1,
        Middle = 2,
        Right = 3,
        X1 = 4,
        X2 = 5,


        Count,
        Invalid = 0xFF,
    };


    struct MouseButtonStruct {
        enum class Code : uint8_t {
            None = 0,
            Left,
            Right,
            Middle,

            X1 ,
            X2 ,
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


} // namespace fts

#endif // __MOUSE_H__