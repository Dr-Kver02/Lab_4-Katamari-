#pragma once

#include <windows.h>
#include <WinUser.h>

#include "../../Lib/Types.h"

namespace engine
{
    namespace graphics
    {
        class Window final
        {
        public:
            void Compose(const char16* name, const Point& size);
            void Show() const;
            void Hide() const;
            void Destroy() const;

            PHandlerWindow handler_window() const;

        private:
            void ComposeWindowClass();
            void ComposeHandlerWindow();

            static pInt64 CALLBACK WindowProcedure(
                PHandlerWindow handler_window, uint32 message, pUint64 uint_param, pInt64 int_param);

            const char16* name_ = nullptr;
            Point size_{};
            PHandlerInstance handler_instance_ = nullptr;
            WindowClassEx window_class_ex_{};
            PHandlerWindow handler_window_ = nullptr;
        };
    }
}
