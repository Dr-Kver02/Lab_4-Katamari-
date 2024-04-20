#pragma once
#include "RenderPipeline.h"
#include "../../Lib/Types.h"

namespace engine
{
    namespace graphics
    {
        struct RasterizerStateParams
        {
            DXRasterizerDescriptor rasterizer_descriptor;
        };

        class RasterizerState
        {
        public:
            void Create(const RenderPipeline* pipeline);

            RasterizerStateParams& rasterizer_state_params();
            DXRasterizerState* rasterizer_state() const;

        private:
            RasterizerStateParams rasterizer_state_params_{};
            DXRasterizerState* rasterizer_state_ = nullptr;
        };
    }
}
