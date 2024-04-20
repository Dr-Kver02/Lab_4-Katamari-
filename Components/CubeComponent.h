#pragma once
#include "../Engine/Graphics/RenderComponent.h"
#include "../Lib/Types.h"

namespace components
{
    class CubeComponent : public engine::graphics::RenderComponent
    {
    public:
        CubeComponent();

    private:
        float4 points_[8 * 2]{};
        int32 indexes_[3 * 12]{};
    };
}
