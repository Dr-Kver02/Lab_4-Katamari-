#include "SphereComponent.h"

using namespace components;

SphereComponent::SphereComponent()
{
    constexpr float thau = 6.28318530718f;
    
    for (auto j = 0; j <= 20; j++)
    {
        const auto height = static_cast<float>(j) / 20.0f;
        const auto t = sqrtf(height * (1.0f - height));
 
        for (auto i = 0; i < 20; i++)
        {
            float sin, cos;
 
            DirectX::XMScalarSinCos(&sin, &cos, thau * static_cast<float>(i) / 20.0f);
 
            const auto position = float3(cos * t, height - 0.5f, sin * t);
 
            points_[j * 40 + i * 2] = float4(position.x, position.y, position.z, 1.0f);
            points_[j * 40 + i * 2 + 1] = float4(position.x + .5f, position.y + .5f, position.z + .5f, 1.0f);
        }
    }

    for (auto j = 0; j < 20; j++)
        for (auto i = 0; i < 20; i++)
        {
            const int32 index = j * 20 + i;
 
            indexes_[6 * index    ] = index;
            indexes_[6 * index + 1] = index + 20 - 1;
            indexes_[6 * index + 2] = index + 20;
            indexes_[6 * index + 3] = index + 20;
            indexes_[6 * index + 4] = index + 1;
            indexes_[6 * index + 5] = index;
        }

    index_count_ = 2400;

    buffers_.vertex_buffer_params().buffer_descriptor.ByteWidth = sizeof(float4) * 840;
    buffers_.vertex_buffer_params().subresource_data.pSysMem = points_;

    buffers_.index_buffer_params().buffer_descriptor.ByteWidth = sizeof(int32) * 2400;
    buffers_.index_buffer_params().subresource_data.pSysMem = indexes_;

    shaders_.vertex_shader_params().path = new char16[]{L"./Shaders/Shader.hlsl"};
    shaders_.pixel_shader_params().path = new char16[]{L"./Shaders/Shader.hlsl"};
}
