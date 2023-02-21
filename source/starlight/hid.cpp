#include "starlight/hid.hpp"

nn::hid::NpadBaseState curControllerState;
nn::hid::NpadBaseState prevControllerState;

nn::hid::KeyboardState curKeyboardState{};
nn::hid::KeyboardState prevKeyboardState{};

nn::hid::MouseState curMouseState{};
nn::hid::MouseState prevMouseState{};

bool isReadInput = false;

void tryGetContState(nn::hid::NpadBaseState *state, ulong port)
{

    nn::hid::NpadStyleSet styleSet = nn::hid::GetNpadStyleSet(port);
    isReadInput = true;

    if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleFullKey))
    {
        nn::hid::GetNpadState((nn::hid::NpadFullKeyState *)state, port);
    }
    else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyDual))
    {
        nn::hid::GetNpadState((nn::hid::NpadJoyDualState *)state, port);
    }
    else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyLeft))
    {
        nn::hid::GetNpadState((nn::hid::NpadJoyLeftState *)state, port);
    }
    else if (styleSet.isBitSet(nn::hid::NpadStyleTag::NpadStyleJoyRight))
    {
        nn::hid::GetNpadState((nn::hid::NpadJoyRightState *)state, port);
    }
    else
    {
        nn::hid::GetNpadState((nn::hid::NpadHandheldState *)state, 0x20);
    }

    isReadInput = false;
}

void Starlight::HID::Initialize()
{
    nn::hid::InitializeKeyboard();
    nn::hid::InitializeMouse();
}

void Starlight::HID::updatePadState()
{
    prevControllerState = curControllerState;
    tryGetContState(&curControllerState, 0);

    prevKeyboardState = curKeyboardState;
    nn::hid::GetKeyboardState(&curKeyboardState);

    prevMouseState = curMouseState;
    nn::hid::GetMouseState(&curMouseState);
}

bool Starlight::HID::isButtonHold(nn::hid::NpadButton button)
{
    return curControllerState.mButtons.isBitSet(button);
}

bool Starlight::HID::isButtonPressed(nn::hid::NpadButton button)
{
    return curControllerState.mButtons.isBitSet(button) && !prevControllerState.mButtons.isBitSet(button);
}

bool Starlight::HID::isButtonReleased(nn::hid::NpadButton button)
{
    return !curControllerState.mButtons.isBitSet(button) && prevControllerState.mButtons.isBitSet(button);
}

bool Starlight::HID::isMouseHold(nn::hid::MouseButton button)
{
    return curMouseState.buttons.isBitSet(button);
}

bool Starlight::HID::isMousePressed(nn::hid::MouseButton button)
{
    return curMouseState.buttons.isBitSet(button) && !prevMouseState.buttons.isBitSet(button);
}

bool Starlight::HID::isMouseReleased(nn::hid::MouseButton button)
{
    return !curMouseState.buttons.isBitSet(button) && prevMouseState.buttons.isBitSet(button);
}

bool Starlight::HID::isKeyHold(nn::hid::KeyboardKey button)
{
    return curKeyboardState.keys.isBitSet(button);
}

bool Starlight::HID::isKeyPressed(nn::hid::KeyboardKey button)
{
    return curKeyboardState.keys.isBitSet(button) && !prevKeyboardState.keys.isBitSet(button);
}

bool Starlight::HID::isKeyReleased(nn::hid::KeyboardKey button)
{
    return !curKeyboardState.keys.isBitSet(button) && prevKeyboardState.keys.isBitSet(button);
}

void Starlight::HID::getMouseCoords(float *x, float *y)
{
    *x = curMouseState.x;
    *y = curMouseState.y;
}

void Starlight::HID::getScrollDelta(float *x, float *y)
{
    *x = curMouseState.wheelDeltaX;
    *y = curMouseState.wheelDeltaY;
}

bool Starlight::HID::isReadingInput()
{
    return isReadInput;
}