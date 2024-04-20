#include "RasterizerState.h"

using namespace engine::graphics;

void RasterizerState::Create(const RenderPipeline* pipeline)
{
    pipeline->device()->CreateRasterizerState(
        &rasterizer_state_params_.rasterizer_descriptor, &rasterizer_state_);
}

RasterizerStateParams& RasterizerState::rasterizer_state_params()
{
    return rasterizer_state_params_;
}

DXRasterizerState* RasterizerState::rasterizer_state() const
{
    return rasterizer_state_;
}
