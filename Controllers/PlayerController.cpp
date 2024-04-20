#include "PlayerController.h"

using namespace controllers;
using namespace DirectX::SimpleMath;

void PlayerController::Compose(
    objects::PlayerObject* player_object, objects::CameraObject* camera, engine::input::Device* device)
{
    player_object_ = player_object;
    camera_ = camera;
    device_ = device;
}

void PlayerController::Update(float delta)
{
    auto* transform = player_object_->transform();
    auto* transform_ball = player_object_->transform_ball();
    auto& local_rotation = transform_ball->local_rotation();

    float3 forward = transform->local_position() - camera_->transform()->local_position();
    forward.y = 0;
    forward.Normalize();
    const float3 left = float3::Transform(forward, float4x4::CreateRotationY(1.57f));

    float3 translation;

    if (device_->IsKeyDown(engine::input::keyboard::Keys::W))
    {
        translation += forward;
        local_rotation *= Quaternion::CreateFromAxisAngle(left, 4.0f * delta);
    }
    if (device_->IsKeyDown(engine::input::keyboard::Keys::S))
    {
        translation += -forward;
        local_rotation *= Quaternion::CreateFromAxisAngle(-left, 4.0f * delta);
    }
    if (device_->IsKeyDown(engine::input::keyboard::Keys::A))
    {
        translation += left;
        local_rotation *= Quaternion::CreateFromAxisAngle(-forward, 4.0f * delta);
    }
    if (device_->IsKeyDown(engine::input::keyboard::Keys::D))
    {
        translation += -left;
        local_rotation *= Quaternion::CreateFromAxisAngle(forward, 4.0f * delta);
    }

    translation.Normalize();
    transform->local_position() += translation * 1.0f * delta;

    transform->UpdateWorldMatrix();
    transform_ball->UpdateWorldMatrix();
    player_object_->transform_model()->UpdateWorldMatrix();
}
