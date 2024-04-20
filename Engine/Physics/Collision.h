#pragma once
#include <vector>

#include "CollisionAble.h"
#include "../Transform/TransformComponent.h"
#include "../Update/FixedUpdateAble.h"

namespace engine
{
    namespace physics
    {
        class Collision final : public update::FixedUpdateAble
        {
        public:
            void FixedUpdate() override;

            void Add(CollisionAble* collision_able);
            void Remove(const CollisionAble* collision_able);

            bool CastRay(
                const float3& position, const float3& direction, transform::TransformComponent** intersected) const;

        private:
            static void DetectCollision(CollisionAble* collision_able_1, CollisionAble* collision_able_2);

            std::vector<CollisionAble*> collision_ables_{};
        };
    }
}
