#pragma once

#include "../../Lib/Types.h"
#include "../Transform/TransformComponent.h"

namespace engine
{
    namespace physics
    {
        class Collision;

        class CollisionAble
        {
        public:
            virtual ~CollisionAble() = default;
            virtual void Compose(Collision* collision);
            virtual void Collided(CollisionAble* other);

            virtual DXBox bounding_box() = 0;
            transform::TransformComponent* transform() const;

        protected:
            Collision* collision_ = nullptr;
            transform::TransformComponent* transform_ = nullptr;
        };
    }
}
