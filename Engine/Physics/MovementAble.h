#pragma once

#include "../../Lib/Types.h"

namespace engine
{
    namespace physics
    {
        class Movement;

        class MovementAble
        {
        public:
            virtual ~MovementAble() = default;
            virtual void Compose(Movement* movement);

            virtual DXBox& bounding_box() = 0;
            virtual float2& velocity() = 0;
        };
    }
}
