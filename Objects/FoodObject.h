#pragma once
#include "Types.h"
#include "../Components/ModelComponent.h"
#include "../Engine/Physics/CollisionAble.h"
#include "../Engine/Update/VariableUpdateAble.h"

namespace objects
{
    class FoodObject final : public engine::physics::CollisionAble, public engine::update::VariableUpdateAble
    {
    public:
        using CollisionAble::Compose;

        void Compose(
            const float3& position, const float3& scale, const float3& box_scale,
            const std::string& model_file_path, const std::string& texture_file_path);

        void Update(float delta) override;

        void Collided(CollisionAble* other) override;

        components::ModelComponent* model() const;

        DXBox bounding_box() override;

    private:
        components::ModelComponent* model_ = nullptr;

        float3 bounding_box_scale_;
    };
}
