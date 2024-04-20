#pragma once

#include "Device.h"

namespace engine
{
    namespace input
    {
        class DevicePC final : public Device
        {
        public:
            void Compose(PHandlerWindow handler_window) override;
            pInt64 CALLBACK HandleInput(
                PHandlerWindow handler_window, uint32 message, pUint64 uint_param, pInt64 int_param) override;
            void Destroy() override;

        private:
            RawInput* ReadRawInput(uint32* size, pInt64 int_param);
            void ProcessKeyboard(const RawInput* raw_input);
            void ProcessMouse(const RawInput* raw_input);

            uint32 input_buffer_[32]{};
        };
    }
}
