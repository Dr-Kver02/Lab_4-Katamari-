#include "CameraControllerRadial.h"

using namespace controllers;
using namespace DirectX::SimpleMath;

void CameraControllerRadial::SetFollowing(engine::transform::TransformComponent* following, const float3& offset)
{
    following_ = following;
    offset_ = offset;
    auto rotation_euler =
        float4x4::CreateLookAt(following_->local_position() + offset_, following_->local_position(), float3::Up).
        ToEuler();
    rotation_euler.x *= -1;
    rotation_euler.z = 0;
    rotation_ = Quaternion::CreateFromYawPitchRoll(rotation_euler);
}

void CameraControllerRadial::Update(float delta)
{
    auto* camera_transform = camera_object_->transform();
    const auto euler = rotation_.ToEuler();
    const auto offset = float3::Transform(offset_, float4x4::CreateRotationY(-euler.y));

    camera_transform->local_position() = following_->local_position() + offset;
    camera_transform->local_rotation() = Quaternion::CreateFromYawPitchRoll(-euler.y, euler.x, 0);
    camera_transform->UpdateWorldMatrix();
    camera_object_->camera()->UpdateViewMatrix();
}

void CameraControllerRadial::OnMouseEvent(const engine::input::mouse::Event& args)
{
    if (device_->IsKeyDown(engine::input::keyboard::Keys::LeftShift)) return;
    rotation_ *= Quaternion::CreateFromAxisAngle(float3::Up, static_cast<float>(args.translation.x) * 0.003f);
}
