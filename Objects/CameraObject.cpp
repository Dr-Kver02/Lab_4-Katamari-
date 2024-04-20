#include "CameraObject.h"

using namespace objects;

void CameraObject::Compose(const Point& size)
{
    transform_.local_position().z = -1;
    transform_.UpdateWorldMatrix();
    camera_.perspective_params().aspect_ratio = static_cast<float>(size.x) / static_cast<float>(size.y);
    camera_.Compose(&transform_);
    camera_.Compose();
}

engine::transform::TransformComponent* CameraObject::transform()
{
    return &transform_;
}

engine::graphics::Camera* CameraObject::camera()
{
    return &camera_;
}
