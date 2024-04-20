#pragma once
#include <vector>

#include "FixedUpdateAble.h"
#include "../../Lib/TimeAccumulator.h"

namespace engine
{
    namespace update
    {
        class FixedUpdate final
        {
        public:
            void Compose(float delta);
            void Update();

            void Add(FixedUpdateAble* fixed_update_able);

            Lib::TimeAccumulator& timer();
            float delta() const;

        private:
            Lib::TimeAccumulator timer_;
            std::vector<FixedUpdateAble*> fixed_update_ables_{};
            float delta_ = 0;
        };
    }
}
