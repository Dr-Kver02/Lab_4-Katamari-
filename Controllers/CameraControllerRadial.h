#pragma once
#include "CameraController.h"
#include "../Engine/Input/Device.h"
#include "../Engine/Transform/TransformComponent.h"
#include "../Lib/Types.h"

namespace controllers
{
    class CameraControllerRadial final : public CameraController
    {
    public:
        using CameraController::Compose;

        void SetFollowing(engine::transform::TransformComponent* following, const float3& offset);

        void Update(float delta) override;

    protected:
        void OnMouseEvent(const engine::input::mouse::Event& args) override;

    private:
        engine::transform::TransformComponent* following_ = nullptr;
        float3 offset_;
        DirectX::SimpleMath::Quaternion rotation_;
    };
}
