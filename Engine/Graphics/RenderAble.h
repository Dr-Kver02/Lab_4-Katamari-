#pragma once
#include "../../Lib/Types.h"

namespace engine
{
    namespace graphics
    {
        class RenderPipeline;

        class RenderAble
        {
        public:
            virtual ~RenderAble() = default;
            virtual void Compose(RenderPipeline* pipeline);
            virtual void Render(const float4x4& camera, float delta) = 0;

        protected:
            RenderPipeline* pipeline_ = nullptr;
        };
    }
}
