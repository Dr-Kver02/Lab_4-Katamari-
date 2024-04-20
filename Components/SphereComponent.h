#pragma once
#include "../Engine/Graphics/RenderComponent.h"

namespace components
{
    class SphereComponent : public engine::graphics::RenderComponent
    {
    public:
        SphereComponent();

    private:
        float4 points_[21 * 20 * 2]{};
        int32 indexes_[20 * 20 * 6]{};
    };
}
