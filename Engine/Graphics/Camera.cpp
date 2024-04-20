#include "Camera.h"

using namespace engine::graphics;

Camera::Camera()
{
    perspective_params_.field_of_view = 3.14f / 2;
    perspective_params_.aspect_ratio = 1;
    perspective_params_.near_z = 0.01f;
    perspective_params_.far_z = 1000;

    orthographic_params_.width = 8;
    orthographic_params_.height = 8;
    orthographic_params_.near_z = 0.01f;
    orthographic_params_.far_z = 1000;
}

void Camera::Compose()
{
    UpdateViewMatrix();
    UpdateProjectionMatrixPerspective();
}

void Camera::Compose(transform::TransformComponent* transform)
{
    transform_ = transform;
}

void Camera::UpdateViewMatrix()
{
    const auto rotation = transform_->local_rotation();
    const auto target = float3::Transform(float3::Forward, rotation) + transform_->local_position();
    const auto up_direction = float3::Transform(float3::Up, rotation);
    view_matrix_ = float4x4::CreateLookAt(transform_->local_position(), target, up_direction);
}

void Camera::UpdateProjectionMatrixPerspective()
{
    projection_matrix_ = float4x4::CreatePerspectiveFieldOfView(
        perspective_params_.field_of_view, perspective_params_.aspect_ratio,
        perspective_params_.near_z, perspective_params_.far_z);
    is_perspective_ = true;
}

void Camera::UpdateProjectionMatrixOrthographic()
{
    projection_matrix_ = float4x4::CreateOrthographic(
        orthographic_params_.width, orthographic_params_.height,
        perspective_params_.near_z, perspective_params_.far_z);
    is_perspective_ = false;
}

CameraPerspectiveParams& Camera::perspective_params()
{
    return perspective_params_;
}

CameraOrthographicParams& Camera::orthographic_params()
{
    return orthographic_params_;
}

float4x4& Camera::view_matrix()
{
    return view_matrix_;
}

float4x4& Camera::projection_matrix()
{
    return projection_matrix_;
}

bool Camera::is_perspective() const
{
    return is_perspective_;
}
