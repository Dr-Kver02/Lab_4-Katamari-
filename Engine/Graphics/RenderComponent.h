#pragma once
#include <string>

#include "Buffers.h"
#include "RasterizerState.h"
#include "RenderPipeline.h"
#include "Shaders.h"
#include "../Transform/TransformComponent.h"
#include "../../Lib/Types.h"

namespace engine
{
    namespace graphics
    {
        struct RenderParams
        {
            DXPrimitiveTopology primitive_topology;
        };

        class RenderComponent : public RenderAble
        {
        public:
            RenderComponent();

            void Compose(transform::TransformComponent* transform);
            void Compose(const std::string& texture_file_path);
            void Compose(RenderPipeline* pipeline) override;
            void Render(const float4x4& camera, float delta) override;

        protected:
            void UpdateTransformBuffer(DXDeviceContext* context, const float4x4& camera) const;

            transform::TransformComponent* transform_ = nullptr;

            RenderParams render_params_{};
            Shaders shaders_;
            Buffers buffers_;
            RasterizerState rasterizer_state_;

            CD3D11_SAMPLER_DESC sample_descriptor{};
            DXSamplerState* sampler_state_ = nullptr;

            DXShaderResourceView* texture_ = nullptr;
            std::string texture_file_path_;

            uint32 index_count_ = 0;
        };
    }
}
