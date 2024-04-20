#pragma once

#include "../../Lib/Types.h"

namespace engine
{
    namespace input
    {
        namespace mouse
        {
            enum struct Buttons : uint16
            {
                None = 0,
                LeftButtonDown = 1,
                LeftButtonUp = 1 << 1,
                RightButtonDown = 1 << 2,
                RightButtonUp = 1 << 3,
                WheelButtonDown = 1 << 4,
                WheelButtonUp = 1 << 5
            };

            struct Event
            {
                Point position;
                Point translation;
                uint16 wheel_delta;

                Event() : position(), translation(), wheel_delta(0)
                {
                }

                Event(const Point& position, const Point& translation, uint16 wheel_delta)
                    : position(position), translation(translation), wheel_delta(wheel_delta)
                {
                }
            };
        }
    }
}
