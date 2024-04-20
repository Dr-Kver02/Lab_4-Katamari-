#include "SquareComponent.h"

using namespace components;
using namespace engine::graphics;

SquareComponent::SquareComponent() : RenderComponent()
{
    points_[0] = float4(0.1f, 0.1f, 0.0f, 1.0f);
    points_[1] = float4(1.0f, 1.0f, 0.0f, 1.0f);
    points_[2] = float4(-0.1f, -0.1f, 0.0f, 1.0f);
    points_[3] = float4(0.0f, 0.0f, 1.0f, 1.0f);
    points_[4] = float4(0.1f, -0.1f, 0.0f, 1.0f);
    points_[5] = float4(0.0f, 1.0f, 0.0f, 1.0f);
    points_[6] = float4(-0.1f, 0.1f, 0.0f, 1.0f);
    points_[7] = float4(1.0f, 0.0f, 1.0f, 1.0f);

    indexes_[0] = 0;
    indexes_[1] = 1;
    indexes_[2] = 2;
    indexes_[3] = 1;
    indexes_[4] = 0;
    indexes_[5] = 3;

    index_count_ = 6;

    buffers_.vertex_buffer_params().buffer_descriptor.ByteWidth = sizeof(float4) * 8;
    buffers_.vertex_buffer_params().subresource_data.pSysMem = points_;

    buffers_.index_buffer_params().buffer_descriptor.ByteWidth = sizeof(int32) * 6;
    buffers_.index_buffer_params().subresource_data.pSysMem = indexes_;

    shaders_.vertex_shader_params().path = new char16[]{L"./Shaders/Shader.hlsl"};
    shaders_.pixel_shader_params().path = new char16[]{L"./Shaders/Shader.hlsl"};
}
