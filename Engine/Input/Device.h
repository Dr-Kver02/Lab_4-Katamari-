#pragma once

#include <unordered_set>

#include "../../Lib/Types.h"
#include "../../Lib/Delegates.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace engine
{
    namespace input
    {
        class Device
        {
        public:
            virtual ~Device() = default;

            virtual void Compose(PHandlerWindow handler_window);
            virtual pInt64 CALLBACK HandleInput(
                PHandlerWindow handler_window, uint32 message, pUint64 uint_param, pInt64 int_param) = 0;
            virtual void Destroy() = 0;

            bool IsKeyDown(keyboard::Keys key) const;
            Lib::MulticastDelegate<const mouse::Event&> mouse_event;
            Lib::MulticastDelegate<const keyboard::Event&> keyboard_event;

        protected:
            void UpdateMouseMovement(const Point& translation, uint16 wheel_delta);
            void AddPressedKey(keyboard::Keys key);
            void RemovePressedKey(keyboard::Keys key);

            std::unordered_set<keyboard::Keys> keys_{};
            PHandlerWindow handler_window_ = nullptr;
        };
    }
}
