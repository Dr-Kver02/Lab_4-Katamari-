#pragma once
#include <vector>

#include "FixedUpdate.h"
#include "VariableUpdateAble.h"

namespace engine
{
    namespace update
    {
        class VariableUpdate
        {
        public:
            void Compose(FixedUpdate* fixed_update);
            void Update() const;

            void Add(VariableUpdateAble* variable_update_able);

        private:
            FixedUpdate* fixed_update_ = nullptr;

            std::vector<VariableUpdateAble*> variable_update_ables_{};
        };
    }
}
