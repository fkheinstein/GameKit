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
    };
} // namespace fts

#endif // __MOUSE_H__