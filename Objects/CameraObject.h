#pragma once
#include "../Engine/Graphics/Camera.h"
#include "../Engine/Transform/TransformComponent.h"

namespace objects
{
    class CameraObject
    {
    public:
        void Compose(const Point& size);

        engine::transform::TransformComponent* transform();
        engine::graphics::Camera* camera();

    private:
        engine::transform::TransformComponent transform_;
        engine::graphics::Camera camera_;
    };
}
