#include "Movement.h"

using namespace engine::physics;

void Movement::Compose(update::FixedUpdate* fixed)
{
    fixed_ = fixed;
}

void Movement::FixedUpdate()
{
    const auto delta = fixed_->delta();
    for (auto* movement_able : movement_ables_)
        movement_able->bounding_box().Center = movement_able->bounding_box().Center
            + float3(movement_able->velocity()) * delta;
}

void Movement::Add(MovementAble* movement_able)
{
    movement_ables_.push_back(movement_able);
    movement_able->Compose(this);
}
