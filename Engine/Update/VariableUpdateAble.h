#pragma once

namespace engine
{
    namespace update
    {
        class VariableUpdate;

        class VariableUpdateAble
        {
        public:
            virtual ~VariableUpdateAble() = default;
            virtual void Compose(VariableUpdate* variable_update);
            virtual void Update(float delta) = 0;

        protected:
            VariableUpdate* variable_update_ = nullptr;
        };
    }
}
