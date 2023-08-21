#ifndef __INPUTLAYER_H__
#define __INPUTLAYER_H__

#include "Core/Layer.h"
#include "Core/InputDevice.h"

namespace fts
{
    class InputLayer : public Layer
    {
    public:
        InputLayer(InputDevice *input);

        void OnTick(float dt) override;

        void On(const KeyEvent &) override;
        void On(const MouseMotionEvent &) override;
        void On(const MouseButtonEvent &) override;
        void On(const MouseWheelEvent &) override;

    private:
        InputDevice *m_input;
    };
} // namespace fts

#endif // __INPUTLAYER_H__