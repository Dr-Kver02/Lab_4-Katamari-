#pragma once

namespace engine
{
    namespace update
    {
        class FixedUpdate;

        class FixedUpdateAble
        {
        public:
            virtual ~FixedUpdateAble() = default;
            virtual void Compose(FixedUpdate* fixed_update);
            virtual void FixedUpdate();
        };
    }
}
