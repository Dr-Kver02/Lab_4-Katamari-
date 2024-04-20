#include "FoodObject.h"

#include "PlayerObject.h"
#include "../Engine/Physics/Collision.h"

using namespace objects;
using namespace DirectX::SimpleMath;

void FoodObject::Compose(
    const float3& position, const float3& scale, const float3& box_scale,
    const std::string& model_file_path, const std::string& texture_file_path)
{
    transform_ = new engine::transform::TransformComponent();
    transform_->local_position() = position;
    transform_->local_scale() = scale;
    transform_->UpdateWorldMatrix();
    bounding_box_scale_ = box_scale / 2;
    model_ = new components::ModelComponent();
    model_->Compose(model_file_path, texture_file_path);
    model_->Compose(transform_);
}

void FoodObject::Update(float delta)
{
    transform_->UpdateWorldMatrix();
}

void FoodObject::Collided(CollisionAble* other)
{
    auto* player = dynamic_cast<PlayerObject*>(other);
    if (player == nullptr)return;
    transform_->Compose(player->transform_ball());
    transform_->world_matrix() *= player->transform_ball()->world_matrix().Invert();
    transform_->world_matrix().Decompose(
        transform_->local_scale(), transform_->local_rotation(), transform_->local_position());
    collision_->Remove(this);
}

components::ModelComponent* FoodObject::model() const
{
    return model_;
}

DXBox FoodObject::bounding_box()
{
    float3 scale, position;
    DirectX::SimpleMath::Quaternion rotation;
    transform_->world_matrix().Decompose(scale, rotation, position);
    return DXBox(position, bounding_box_scale_);
}
