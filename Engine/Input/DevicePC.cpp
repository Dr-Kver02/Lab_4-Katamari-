#include "DevicePC.h"

using namespace engine::input;

void DevicePC::Compose(PHandlerWindow handler_window)
{
    Device::Compose(handler_window);

    RAWINPUTDEVICE devices[2];

    devices[0].usUsagePage = 1; // Keyboard
    devices[0].usUsage = 2;
    devices[0].dwFlags = 0;
    devices[0].hwndTarget = handler_window;

    devices[1].usUsagePage = 1; // Mouse
    devices[1].usUsage = 6;
    devices[1].dwFlags = 0;
    devices[1].hwndTarget = handler_window;

    RegisterRawInputDevices(devices, 2, sizeof(devices[0]));
}

pInt64 CALLBACK DevicePC::HandleInput(
    PHandlerWindow handler_window, uint32 message, pUint64 uint_param, pInt64 int_param)
{
    if (message != WM_INPUT) return DefWindowProc(handler_window, message, uint_param, int_param);

    uint32 size;
    auto* pRawInput = ReadRawInput(&size, int_param);
    if (size == 0) return DefWindowProc(handler_window, message, uint_param, int_param);

    if (pRawInput->header.dwType == RIM_TYPEKEYBOARD) ProcessKeyboard(pRawInput);
    else if (pRawInput->header.dwType == RIM_TYPEMOUSE) ProcessMouse(pRawInput);

    return DefWindowProc(handler_window, message, uint_param, int_param);
}

void DevicePC::Destroy()
{
    RAWINPUTDEVICE devices[2];

    devices[0].usUsagePage = 1; // Keyboard
    devices[0].usUsage = 2;
    devices[0].dwFlags = RIDEV_REMOVE;
    devices[0].hwndTarget = nullptr;

    devices[1].usUsagePage = 1; // Mouse
    devices[1].usUsage = 6;
    devices[1].dwFlags = RIDEV_REMOVE;
    devices[1].hwndTarget = nullptr;

    RegisterRawInputDevices(devices, 2, sizeof(devices[0]));
}

RAWINPUT* DevicePC::ReadRawInput(uint32* size, pInt64 int_param)
{
    GetRawInputData(reinterpret_cast<PHandlerRawInput>(int_param), RID_INPUT,
                    input_buffer_, size, sizeof(RAWINPUTHEADER));
    return reinterpret_cast<RawInput*>(input_buffer_);
}

void DevicePC::ProcessKeyboard(const RawInput* raw_input)
{
    auto key = static_cast<keyboard::Keys>(raw_input->data.keyboard.VKey);

    if (raw_input->data.keyboard.MakeCode == 42) key = keyboard::Keys::LeftShift;
    else if (raw_input->data.keyboard.MakeCode == 54) key = keyboard::Keys::RightShift;

    if (raw_input->data.keyboard.Flags & RI_KEY_BREAK)
    {
        if (keys_.count(key) != 0) RemovePressedKey(key);
    }
    else if (keys_.count(key) == 0) AddPressedKey(key);
}

void DevicePC::ProcessMouse(const RawInput* raw_input)
{
    const auto flags = raw_input->data.mouse.usButtonFlags;
    if (flags & static_cast<uint16>(mouse::Buttons::LeftButtonDown)) AddPressedKey(keyboard::Keys::MouseLeftButton);
    if (flags & static_cast<uint16>(mouse::Buttons::LeftButtonUp)) RemovePressedKey(keyboard::Keys::MouseLeftButton);
    if (flags & static_cast<uint16>(mouse::Buttons::RightButtonDown)) AddPressedKey(keyboard::Keys::MouseRightButton);
    if (flags & static_cast<uint16>(mouse::Buttons::RightButtonUp)) RemovePressedKey(keyboard::Keys::MouseRightButton);
    if (flags & static_cast<uint16>(mouse::Buttons::WheelButtonDown)) AddPressedKey(keyboard::Keys::MouseWheelButton);
    if (flags & static_cast<uint16>(mouse::Buttons::WheelButtonUp)) RemovePressedKey(keyboard::Keys::MouseWheelButton);
    const Point translation = {raw_input->data.mouse.lLastX, raw_input->data.mouse.lLastY};
    UpdateMouseMovement(translation, raw_input->data.mouse.usButtonData);
}
