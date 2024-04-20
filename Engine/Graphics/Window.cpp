#include "Window.h"

#include "../../Game.h"

using namespace engine::graphics;

void Window::Compose(const char16* name, const Point& size)
{
    name_ = name;
    size_ = size;
    handler_instance_ = GetModuleHandle(nullptr);
    ComposeWindowClass();
    ComposeHandlerWindow();
    Show();
}

void Window::Show() const
{
    ShowWindow(handler_window_, SW_SHOW);
    SetForegroundWindow(handler_window_);
    SetFocus(handler_window_);
    ShowCursor(true);
}

void Window::Hide() const
{
    ShowWindow(handler_window_, SW_HIDE);
}

void Window::Destroy() const
{
    DestroyWindow(handler_window_);
    UnregisterClass(name_, handler_instance_);
}

PHandlerWindow Window::handler_window() const
{
    return handler_window_;
}

void Window::ComposeWindowClass()
{
    window_class_ex_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class_ex_.lpfnWndProc = WindowProcedure;
    window_class_ex_.cbClsExtra = 0;
    window_class_ex_.cbWndExtra = 0;
    window_class_ex_.hInstance = handler_instance_;
    window_class_ex_.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    window_class_ex_.hIconSm = window_class_ex_.hIcon;
    window_class_ex_.hCursor = LoadCursor(nullptr, IDC_ARROW);
    window_class_ex_.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    window_class_ex_.lpszMenuName = nullptr;
    window_class_ex_.lpszClassName = name_;
    window_class_ex_.cbSize = sizeof(WindowClassEx);
    RegisterClassEx(&window_class_ex_);
}

void Window::ComposeHandlerWindow()
{
    Rect window_rectangle = {0, 0, size_.x, size_.y};
    AdjustWindowRect(&window_rectangle, WS_OVERLAPPEDWINDOW, FALSE);
    constexpr auto drawing_style = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME;
    const auto position_x = (GetSystemMetrics(SM_CXSCREEN) - size_.x) / 2;
    const auto position_y = (GetSystemMetrics(SM_CYSCREEN) - size_.y) / 2;
    handler_window_ = CreateWindowEx(
        WS_EX_APPWINDOW, name_, name_, drawing_style, position_x, position_y,
        window_rectangle.right - window_rectangle.left, window_rectangle.bottom - window_rectangle.top,
        nullptr, nullptr, handler_instance_, nullptr);
}

pInt64 Window::WindowProcedure(PHandlerWindow handler_window, uint32 message, pUint64 uint_param, pInt64 int_param)
{
    return Game::Instance()->input_device()->HandleInput(handler_window, message, uint_param, int_param);
}
