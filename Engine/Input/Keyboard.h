#pragma once

#include "../../Lib/Types.h"

namespace engine
{
    namespace input
    {
        namespace keyboard
        {
            enum struct Buttons : uint16
            {
                None = 0,
                Down = 1,
                Up = 1 << 1
            };

            enum struct Keys : uint16
            {
                None = 0,

                // Mouse
                MouseLeftButton = 500,
                MouseRightButton = 501,
                MouseWheelButton = 502,
                MouseButtonX1 = 503,
                MouseButtonX2 = 504,
                MouseButtonX3 = 505,
                MouseWheelUp = 506,
                MouseWheelDown = 507,

                // Letters
                A = 65,
                B = 66,
                C = 67,
                D = 68,
                E = 69,
                F = 70,
                G = 71,
                H = 72,
                I = 73,
                J = 74,
                K = 75,
                L = 76,
                M = 77,
                N = 78,
                O = 79,
                P = 80,
                Q = 81,
                R = 82,
                S = 83,
                T = 84,
                U = 85,
                V = 86,
                W = 87,
                X = 88,
                Y = 89,
                Z = 90,

                //Fs
                F1 = 112,
                F2 = 113,
                F3 = 114,
                F4 = 115,
                F5 = 116,
                F6 = 117,
                F7 = 118,
                F8 = 119,
                F9 = 120,
                F10 = 121,
                F11 = 122,
                F12 = 123,
                F13 = 124,
                F14 = 125,
                F15 = 126,
                F16 = 127,
                F17 = 128,
                F18 = 129,
                F19 = 130,
                F20 = 131,
                F21 = 132,
                F22 = 133,
                F23 = 134,
                F24 = 135,

                // Digits
                D0 = 48,
                D1 = 49,
                D2 = 50,
                D3 = 51,
                D4 = 52,
                D5 = 53,
                D6 = 54,
                D7 = 55,
                D8 = 56,
                D9 = 57,

                // NumPad
                NumPad0 = 96,
                NumPad1 = 97,
                NumPad2 = 98,
                NumPad3 = 99,
                NumPad4 = 100,
                NumPad5 = 101,
                NumPad6 = 102,
                NumPad7 = 103,
                NumPad8 = 104,
                NumPad9 = 105,

                // Math signs
                Multiply = 106,
                Add = 107,
                Separator = 108,
                Subtract = 109,
                Decimal = 110,
                Divide = 111,

                // Arrows
                LeftArrow = 37,
                UpArrow = 38,
                RightArrow = 39,
                DownArrow = 40,

                // Supports
                LeftWindows = 91,
                RightWindows = 92,
                LeftShift = 160,
                RightShift = 161,
                LeftControl = 162,
                RightControl = 163,
                LeftAlt = 164,
                RightAlt = 165,

                // Spaces
                Tab = 9,
                Enter = 13,
                Space = 32,

                Escape = 27
            };

            struct Event
            {
                Keys code;
                Buttons button;

                Event() : code(Keys::None), button(Buttons::None)
                {
                }

                Event(Keys code, Buttons button) : code(code), button(button)
                {
                }
            };
        }
    }
}
