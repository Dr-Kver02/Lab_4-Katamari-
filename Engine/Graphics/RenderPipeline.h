#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <vector>

#include "RenderAble.h"
#include "../../Lib/Types.h"

namespace engine
{
    namespace graphics
    {
        class RenderAble;

        class RenderPipeline final
        {
        public:
            void Compose(PHandlerWindow handler_window, const Point& size);
            void Render(const float4x4& camera, float delta);
            void Destroy() const;

            void Add(RenderAble* render_able);

            DXDevice* device() const;
            DXDeviceContext* device_context() const;

        private:
            void ComposeDeviceAndSwapChain(PHandlerWindow handler_window);
            void ComposeRenderTargetView();
            void ComposeDepthStencilBuffer(const Point& size);

            Point size_{};
            DXViewport viewport_{};
            Microsoft::WRL::ComPtr<DXDevice> device_;
            DXDeviceContext* device_context_ = nullptr;
            DXSwapChain* swap_chain_ = nullptr;
            DXRenderTargetView* render_target_view_ = nullptr;
            DXDepthStencilView* depth_stencil_view_ = nullptr;
            DXTexture2D* depth_stencil_buffer_ = nullptr;
            std::vector<RenderAble*> render_ables_{};
        };
    }
}
