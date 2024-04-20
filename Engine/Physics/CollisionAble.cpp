#include "CollisionAble.h"

using namespace engine::physics;

void CollisionAble::Compose(Collision* collision)
{
    collision_ = collision;
}

void CollisionAble::Collided(CollisionAble* other)
{
}

engine::transform::TransformComponent* CollisionAble::transform() const
{
    return transform_;
}
