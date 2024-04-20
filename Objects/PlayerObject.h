#pragma once
#include <string>

#include "../Components/ModelComponent.h"
#include "../Engine/Physics/CollisionAble.h"
#include "../Engine/Transform/TransformComponent.h"

namespace objects
{
    class PlayerObject final : public engine::graphics::RenderAble, public engine::physics::CollisionAble
    {
    public:
        void Compose(const float3& position, const float3& scale, const float3& box_scale, const float3& box_increasing,  const float3& scale_increasing, 
                     const std::string& model_file_path, const std::string& texture_file_path);
        void Compose(engine::graphics::RenderPipeline* pipeline) override;
        
        void Render(const float4x4& camera, float delta) override;

        void Collided(CollisionAble* other) override;

        engine::transform::TransformComponent* transform_ball();
        engine::transform::TransformComponent* transform_model();
        DXBox bounding_box() override;

    private:
        engine::transform::TransformComponent transform_ball_;
        engine::transform::TransformComponent transform_model_;
        components::ModelComponent model_;

        float3 bounding_box_scale_;
        float3 box_increasing_;
        float3 scale_increasing_;
    };
}
