#pragma once
#include <vector>

#include "MovementAble.h"
#include "../Update/FixedUpdateAble.h"
#include "../Update/FixedUpdate.h"

namespace engine
{
    namespace physics
    {
        class Movement final : public update::FixedUpdateAble
        {
        public:
            void Compose(update::FixedUpdate* fixed) override;
            void FixedUpdate() override;

            void Add(MovementAble* movement_able);

        private:
            std::vector<MovementAble*> movement_ables_{};
            update::FixedUpdate* fixed_ = nullptr;
        };
    }
}
