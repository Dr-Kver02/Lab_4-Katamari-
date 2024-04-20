#include "PlayerObject.h"

#include "FoodObject.h"

using namespace objects;

void PlayerObject::Compose(
    const float3& position, const float3& scale, const float3& box_scale, const float3& box_increasing, const float3& scale_increasing,
    const std::string& model_file_path, const std::string& texture_file_path)
{
    transform_ = new engine::transform::TransformComponent();
    transform_->local_position() = position;
    transform_->UpdateWorldMatrix();

    transform_ball_ = engine::transform::TransformComponent();
    transform_ball_.Compose(transform_);
    transform_ball_.UpdateWorldMatrix();
    
    transform_model_ = engine::transform::TransformComponent();
    transform_model_.local_scale() = scale;
    transform_model_.Compose(&transform_ball_);
    transform_model_.UpdateWorldMatrix();

    bounding_box_scale_ = box_scale / 2;
    box_increasing_ = box_increasing;
    scale_increasing_ = scale_increasing;

    model_ = components::ModelComponent();
    model_.Compose(model_file_path, texture_file_path);
    model_.Compose(&transform_model_);
}

void PlayerObject::Compose(engine::graphics::RenderPipeline* pipeline)
{
    RenderAble::Compose(pipeline);
    model_.Compose(pipeline_);
}

void PlayerObject::Render(const float4x4& camera, float delta)
{
    model_.Render(camera, delta);
}

void PlayerObject::Collided(CollisionAble* other)
{
    const auto* food = dynamic_cast<FoodObject*>(other);
    if (food== nullptr) return;
    bounding_box_scale_ += box_increasing_;
    transform_model_.local_scale() += scale_increasing_;
    transform_model_.UpdateWorldMatrix();
}

engine::transform::TransformComponent* PlayerObject::transform_ball()
{
    return &transform_ball_;
}

engine::transform::TransformComponent* PlayerObject::transform_model()
{
    return &transform_model_;
}

DXBox PlayerObject::bounding_box()
{
    float3 scale, position;
    DirectX::SimpleMath::Quaternion rotation;
    transform_->world_matrix().Decompose(scale, rotation, position);
    return DXBox(position, bounding_box_scale_);
}
