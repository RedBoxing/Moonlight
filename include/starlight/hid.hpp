#pragma once

#include "common.hpp"
#include "nn.hpp"

namespace Starlight
{
    namespace HID
    {
        void Initialize();
        void updatePadState();

        bool isButtonHold(nn::hid::NpadButton button);
        bool isButtonPressed(nn::hid::NpadButton button);
        bool isButtonReleased(nn::hid::NpadButton button);

        bool isMouseHold(nn::hid::MouseButton button);
        bool isMousePressed(nn::hid::MouseButton button);
        bool isMouseReleased(nn::hid::MouseButton button);

        bool isKeyHold(nn::hid::KeyboardKey button);
        bool isKeyPressed(nn::hid::KeyboardKey button);
        bool isKeyReleased(nn::hid::KeyboardKey button);

        void getMouseCoords(float *x, float *y);
        void getScrollDelta(float *x, float *y);

        bool isReadingInput();
    }
}