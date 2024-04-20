#include "RenderPipeline.h"

using namespace engine::graphics;

void RenderPipeline::Compose(PHandlerWindow handler_window, const Point& size)
{
	size_ = size;
	viewport_.Width = static_cast<float>(size.x);
	viewport_.Height = static_cast<float>(size.y);
	viewport_.TopLeftX = 0;
	viewport_.TopLeftY = 0;
	viewport_.MinDepth = 0;
	viewport_.MaxDepth = 1;

	ComposeDeviceAndSwapChain(handler_window);
	ComposeRenderTargetView();
	ComposeDepthStencilBuffer(size);
}

void RenderPipeline::Render(const float4x4& camera, float delta)
{
	device_context_->ClearState();
	constexpr float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	device_context_->RSSetViewports(1, &viewport_);
	device_context_->ClearRenderTargetView(render_target_view_, color);
	device_context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	device_context_->OMSetRenderTargets(1, &render_target_view_, depth_stencil_view_);

	ID3D11BlendState* bs;
	D3D11_BLEND_DESC b;
	b.AlphaToCoverageEnable = false;
	b.IndependentBlendEnable = false;
	b.RenderTarget[0].BlendEnable = true;
	b.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	b.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	b.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	b.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	b.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	b.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	b.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	device_->CreateBlendState(&b, &bs);

	float f[4] = { 1, 1, 1, 1 };
	device_context_->OMSetBlendState(bs, f, 0xffffffff);

	for (auto* pRenderAble : render_ables_) pRenderAble->Render(camera, delta);

	swap_chain_->Present(1, DXGI_PRESENT_DO_NOT_WAIT);
}

void RenderPipeline::Destroy() const
{
	render_target_view_->Release();
	swap_chain_->Release();
	device_context_->Release();
	device_->Release();
}

void RenderPipeline::Add(RenderAble* render_able)
{
	render_ables_.push_back(render_able);
	render_able->Compose(this);
}

DXDevice* RenderPipeline::device() const
{
	return device_.Get();
}

DXDeviceContext* RenderPipeline::device_context() const
{
	return device_context_;
}

void RenderPipeline::ComposeDeviceAndSwapChain(PHandlerWindow handler_window)
{
	constexpr D3D_FEATURE_LEVEL feature_level[] = { D3D_FEATURE_LEVEL_11_1 };

	DXGI_SWAP_CHAIN_DESC swap_chain_descriptor;
	swap_chain_descriptor.BufferCount = 2;
	swap_chain_descriptor.BufferDesc.Width = size_.x;
	swap_chain_descriptor.BufferDesc.Height = size_.y;
	swap_chain_descriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_descriptor.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_descriptor.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_descriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain_descriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swap_chain_descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_descriptor.OutputWindow = handler_window;
	swap_chain_descriptor.Windowed = true;
	swap_chain_descriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swap_chain_descriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swap_chain_descriptor.SampleDesc.Count = 1;
	swap_chain_descriptor.SampleDesc.Quality = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		feature_level, 1, D3D11_SDK_VERSION, &swap_chain_descriptor,
		&swap_chain_, &device_, nullptr, &device_context_);
}

void RenderPipeline::ComposeRenderTargetView()
{
	ID3D11Texture2D* background_texture;
	swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&background_texture));
	device_->CreateRenderTargetView(background_texture, nullptr, &render_target_view_);
}

void RenderPipeline::ComposeDepthStencilBuffer(const Point& size)
{
	DXTexture2DDescriptor depth_stencil_descriptor;
	depth_stencil_descriptor.Width = size.x;
	depth_stencil_descriptor.Height = size.y;
	depth_stencil_descriptor.MipLevels = 1;
	depth_stencil_descriptor.ArraySize = 1;
	depth_stencil_descriptor.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_descriptor.SampleDesc.Count = 1;
	depth_stencil_descriptor.SampleDesc.Quality = 0;
	depth_stencil_descriptor.Usage = D3D11_USAGE_DEFAULT;
	depth_stencil_descriptor.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depth_stencil_descriptor.CPUAccessFlags = 0;
	depth_stencil_descriptor.MiscFlags = 0;

	device_->CreateTexture2D(&depth_stencil_descriptor, nullptr, &depth_stencil_buffer_);
	device_->CreateDepthStencilView(depth_stencil_buffer_, nullptr, &depth_stencil_view_);
	device_context_->OMSetRenderTargets(1, &render_target_view_, depth_stencil_view_);
}
