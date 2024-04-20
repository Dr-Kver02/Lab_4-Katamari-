#include "FoodSpawnerObject.h"

#include <chrono>

#include "FoodObject.h"
#include "../Engine/Physics/Collision.h"

using namespace objects;
using namespace DirectX::SimpleMath;

void FoodSpawnerObject::Compose(
    std::string file_paths[], float probabilities[], float2 area, int32 amount)
{
    srand(static_cast<uint32>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

    for (int32 i = 0; i < amount; i++)
    {
        auto food = FoodObject();
        auto probability = static_cast<float>(rand()) / RAND_MAX;
        int32 j = 0;
        while (probability > probabilities[j]) probability -= probabilities[j++];
        auto position = float3((static_cast<float>(rand()) / RAND_MAX - 0.5f) * area.x, 0,
                               (static_cast<float>(rand()) / RAND_MAX - 0.5f) * area.y);
        const auto rotation = Quaternion::CreateFromYawPitchRoll(static_cast<float>(rand()) / RAND_MAX * 6.28f, 0, 0);
        food.Compose(position, float3(0.002f), float3(0.2f),
                     file_paths[j * 2], file_paths[j * 2 + 1]);
        food.transform()->local_rotation() = rotation;
        food.transform()->UpdateWorldMatrix();
        food_objects_.push_back(std::move(food));
    }
}

void FoodSpawnerObject::Compose(engine::graphics::RenderPipeline* pipeline)
{
    RenderAble::Compose(pipeline);
    for (auto& food : food_objects_) food.model()->Compose(pipeline_);
}

void FoodSpawnerObject::Compose(engine::physics::Collision* collision)
{
    for (auto& food : food_objects_) collision->Add(&food);
}

void FoodSpawnerObject::Update(float delta)
{
    for (auto& food : food_objects_) food.Update(delta);
}

void FoodSpawnerObject::Render(const float4x4& camera, float delta)
{
    for (auto& food : food_objects_) food.model()->Render(camera, delta);
}
