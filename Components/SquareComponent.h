#pragma once
#include "../Engine/Graphics/RenderComponent.h"

namespace components
{
    class SquareComponent final : public engine::graphics::RenderComponent
    {
    public:
        SquareComponent();

    private:
        float4 points_[4 * 2]{};
        int32 indexes_[3 * 2]{};
    };
}
