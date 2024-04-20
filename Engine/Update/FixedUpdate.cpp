#include "FixedUpdate.h"

using namespace engine::update;

void FixedUpdate::Compose(float delta)
{
    timer_.Compose();
    delta_ = delta;
}

void FixedUpdate::Update()
{
    timer_.Update();
    while (timer_.accumulated() > static_cast<double>(delta_))
    {
        for (auto* fixed_update_able : fixed_update_ables_) fixed_update_able->FixedUpdate();
        timer_.accumulated() -= static_cast<double>(delta_);
    }
}

void FixedUpdate::Add(FixedUpdateAble* fixed_update_able)
{
    fixed_update_ables_.push_back(fixed_update_able);
    fixed_update_able->Compose(this);
}

Lib::TimeAccumulator& FixedUpdate::timer()
{
    return timer_;
}

float FixedUpdate::delta() const
{
    return delta_;
}
