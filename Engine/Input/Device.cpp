#include "Device.h"

using namespace engine::input;

void Device::Compose(PHandlerWindow handler_window)
{
    handler_window_ = handler_window;
}

bool Device::IsKeyDown(const keyboard::Keys key) const
{
    return keys_.count(key) != 0;
}

void Device::UpdateMouseMovement(const Point& translation, uint16 wheel_delta)
{
    Point position;
    GetCursorPos(&position);
    ScreenToClient(handler_window_, &position);
    const mouse::Event event = {position, translation, wheel_delta};
    mouse_event.Broadcast(event);
}

void Device::AddPressedKey(keyboard::Keys key)
{
    keys_.insert(key);
    const keyboard::Event event = {key, keyboard::Buttons::Down};
    keyboard_event.Broadcast(event);
}

void Device::RemovePressedKey(keyboard::Keys key)
{
    keys_.erase(key);
    const keyboard::Event event = {key, keyboard::Buttons::Up};
    keyboard_event.Broadcast(event);
}
