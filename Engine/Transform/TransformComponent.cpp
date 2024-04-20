#include "TransformComponent.h"

using namespace engine::transform;

TransformComponent::TransformComponent()
{
    local_scale_ = float3(1);
    UpdateWorldMatrix();
}

void TransformComponent::Compose(TransformComponent* parent)
{
    parent_ = parent;
}

void TransformComponent::UpdateWorldMatrix()
{
    world_matrix_ =
        float4x4::CreateScale(local_scale_)
        * float4x4::CreateFromQuaternion(local_rotation_)
        * float4x4::CreateTranslation(local_position_)
        * (parent_ == nullptr ? float4x4::Identity : parent_->world_matrix_);
}

TransformComponent* TransformComponent::parent() const
{
    return parent_;
}

float4x4& TransformComponent::world_matrix()
{
    return world_matrix_;
}

float3& TransformComponent::local_position()
{
    return local_position_;
}

DirectX::SimpleMath::Quaternion& TransformComponent::local_rotation()
{
    return local_rotation_;
}

float3& TransformComponent::local_scale()
{
    return local_scale_;
}
