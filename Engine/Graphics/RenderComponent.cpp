#include "RenderComponent.h"

#include <d3dcompiler.h>
#include <iostream>
#include <WICTextureLoader.h>

using namespace engine::graphics;

RenderComponent::RenderComponent()
{
    render_params_.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    auto& vertex_shader_params = shaders_.vertex_shader_params();
    vertex_shader_params.entrypoint = new char8[]{"VSMain"};
    vertex_shader_params.target = new char8[]{"vs_5_0"};
    vertex_shader_params.flags1 = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

    auto& pixel_shader_params = shaders_.pixel_shader_params();
    pixel_shader_params.entrypoint = new char8[]{"PSMain"};
    pixel_shader_params.target = new char8[]{"ps_5_0"};
    pixel_shader_params.flags1 = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

    auto& input_layout_params = shaders_.input_layout_params();
    input_layout_params.input_element_descriptors = new DXInputElementDescriptor[2];
    input_layout_params.input_element_descriptors[0] = DXInputElementDescriptor{
        "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
        0, D3D11_INPUT_PER_VERTEX_DATA, 0
    };
    input_layout_params.input_element_descriptors[1] = DXInputElementDescriptor{
        "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
        D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0
    };
    input_layout_params.elements_number = 2;

    auto& vertex_buffer_params = buffers_.vertex_buffer_params();
    vertex_buffer_params.buffer_descriptor.Usage = D3D11_USAGE_DEFAULT;
    vertex_buffer_params.buffer_descriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_buffer_params.buffer_descriptor.CPUAccessFlags = 0;
    vertex_buffer_params.buffer_descriptor.MiscFlags = 0;
    vertex_buffer_params.buffer_descriptor.StructureByteStride = 0;
    vertex_buffer_params.subresource_data.SysMemPitch = 0;
    vertex_buffer_params.subresource_data.SysMemSlicePitch = 0;

    auto& index_buffer_params = buffers_.index_buffer_params();
    index_buffer_params.buffer_descriptor.Usage = D3D11_USAGE_DEFAULT;
    index_buffer_params.buffer_descriptor.BindFlags = D3D11_BIND_INDEX_BUFFER;
    index_buffer_params.buffer_descriptor.CPUAccessFlags = 0;
    index_buffer_params.buffer_descriptor.MiscFlags = 0;
    index_buffer_params.buffer_descriptor.StructureByteStride = 0;
    index_buffer_params.subresource_data.SysMemPitch = 0;
    index_buffer_params.subresource_data.SysMemSlicePitch = 0;

    auto& transform_buffer_params = buffers_.transform_buffer_params();
    transform_buffer_params.buffer_descriptor.Usage = D3D11_USAGE_DYNAMIC;
    transform_buffer_params.buffer_descriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    transform_buffer_params.buffer_descriptor.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    transform_buffer_params.buffer_descriptor.MiscFlags = 0;
    transform_buffer_params.buffer_descriptor.StructureByteStride = 0;
    transform_buffer_params.buffer_descriptor.ByteWidth = sizeof(float4x4);

    auto& rasterizer_state_params = rasterizer_state_.rasterizer_state_params();
    rasterizer_state_params.rasterizer_descriptor.CullMode = D3D11_CULL_NONE;
    rasterizer_state_params.rasterizer_descriptor.FillMode = D3D11_FILL_SOLID;

    sample_descriptor.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sample_descriptor.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sample_descriptor.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sample_descriptor.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sample_descriptor.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sample_descriptor.MinLOD = 0;
    sample_descriptor.MaxLOD = D3D11_FLOAT32_MAX;
}

void RenderComponent::Compose(transform::TransformComponent* transform)
{
    transform_ = transform;
    buffers_.transform_buffer_params().subresource_data.pSysMem = &transform_->world_matrix();
}

void RenderComponent::Compose(const std::string& texture_file_path)
{
    texture_file_path_ = texture_file_path;
}

void RenderComponent::Compose(RenderPipeline* pipeline)
{
    RenderAble::Compose(pipeline);
    shaders_.Create(pipeline);
    buffers_.Create(pipeline);
    rasterizer_state_.Create(pipeline);
    pipeline_->device()->CreateSamplerState(&sample_descriptor, &sampler_state_);
    const std::wstring wide_string(texture_file_path_.begin(), texture_file_path_.end());
    DirectX::CreateWICTextureFromFile(
        pipeline_->device(), wide_string.data(), nullptr, &texture_);
}

void RenderComponent::Render(const float4x4& camera, float delta)
{
    constexpr uint32 strides[] = {32};
    constexpr uint32 offsets[] = {0};

    auto* context = pipeline_->device_context();
    context->RSSetState(rasterizer_state_.rasterizer_state());

    context->IASetInputLayout(shaders_.input_layout());
    context->IASetPrimitiveTopology(render_params_.primitive_topology);
    context->IASetIndexBuffer(buffers_.index_buffer(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetVertexBuffers(0, 1, buffers_.vertex_buffer_pointer(), strides, offsets);

    context->PSSetSamplers(0, 1, &sampler_state_);
    context->PSSetShaderResources(0, 1, &texture_);

    UpdateTransformBuffer(context, camera);

    context->VSSetShader(shaders_.vertex_shader(), nullptr, 0);
    context->PSSetShader(shaders_.pixel_shader(), nullptr, 0);

    context->DrawIndexed(index_count_, 0, 0);
}

void RenderComponent::UpdateTransformBuffer(DXDeviceContext* context, const float4x4& camera) const
{
    const auto matrix = transform_->world_matrix() * camera;
    DXMappedSubresource subresource = {};
    context->Map(buffers_.transform_buffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);
    auto* data = static_cast<float*>(subresource.pData);
    memcpy(data, &matrix, sizeof(float4x4));
    context->Unmap(buffers_.transform_buffer(), 0);
    context->VSSetConstantBuffers(0, 1, buffers_.transform_buffer_pointer());
}
