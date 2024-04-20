#include "VariableUpdate.h"

using namespace engine::update;

void VariableUpdate::Compose(FixedUpdate* fixed_update)
{
    fixed_update_ = fixed_update;
}

void VariableUpdate::Update() const
{
    const auto delta = static_cast<float>(fixed_update_->timer().delta());
    for (auto* update_able : variable_update_ables_) update_able->Update(delta);
}

void VariableUpdate::Add(VariableUpdateAble* variable_update_able)
{
    variable_update_ables_.push_back(variable_update_able);
    variable_update_able->Compose(this);
}
