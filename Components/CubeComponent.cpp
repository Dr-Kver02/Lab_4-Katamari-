#include "CubeComponent.h"

using namespace components;

CubeComponent::CubeComponent()
{
    points_[0] = float4(0.1f, 0.1f, 0.1f, 1.0f);
    points_[1] = float4(1.0f, 0.0f, 0.0f, 1.0f);
    points_[2] = float4(-0.1f, -0.1f, 0.1f, 1.0f);
    points_[3] = float4(0.0f, 1.0f, 0.0f, 1.0f);
    points_[4] = float4(0.1f, -0.1f, 0.1f, 1.0f);
    points_[5] = float4(0.0f, 0.0f, 1.0f, 1.0f);
    points_[6] = float4(-0.1f, 0.1f, 0.1f, 1.0f);
    points_[7] = float4(1.0f, 1.0f, 0.0f, 1.0f);
    points_[8] = float4(0.1f, 0.1f, -0.1f, 1.0f);
    points_[9] = float4(1.0f, 0.0f, 1.0f, 1.0f);
    points_[10] = float4(-0.1f, -0.1f, -0.1f, 1.0f);
    points_[11] = float4(0.0f, 1.0f, 1.0f, 1.0f);
    points_[12] = float4(0.1f, -0.1f, -0.1f, 1.0f);
    points_[13] = float4(1.0f, 1.0f, 1.0f, 1.0f);
    points_[14] = float4(-0.1f, 0.1f, -0.1f, 1.0f);
    points_[15] = float4(0.2f, 0.2f, 0.2f, 1.0f);

    indexes_[0] = 0;
    indexes_[1] = 1;
    indexes_[2] = 2;
    indexes_[3] = 1;
    indexes_[4] = 0;
    indexes_[5] = 3;
    
    indexes_[6] = 0;
    indexes_[7] = 4;
    indexes_[8] = 7;
    indexes_[9] = 3;
    indexes_[10] = 0;
    indexes_[11] = 7;
    
    indexes_[12] = 4;
    indexes_[13] = 2;
    indexes_[14] = 6;
    indexes_[15] = 2;
    indexes_[16] = 4;
    indexes_[17] = 0;
    
    indexes_[18] = 3;
    indexes_[19] = 5;
    indexes_[20] = 1;
    indexes_[21] = 5;
    indexes_[22] = 3;
    indexes_[23] = 7;
    
    indexes_[24] = 5;
    indexes_[25] = 2;
    indexes_[26] = 1;
    indexes_[27] = 2;
    indexes_[28] = 5;
    indexes_[29] = 6;
    
    indexes_[30] = 7;
    indexes_[31] = 6;
    indexes_[32] = 5;
    indexes_[33] = 6;
    indexes_[34] = 7;
    indexes_[35] = 4;

    index_count_ = 36;

    buffers_.vertex_buffer_params().buffer_descriptor.ByteWidth = sizeof(float4) * 16;
    buffers_.vertex_buffer_params().subresource_data.pSysMem = points_;

    buffers_.index_buffer_params().buffer_descriptor.ByteWidth = sizeof(int32) * 36;
    buffers_.index_buffer_params().subresource_data.pSysMem = indexes_;

    shaders_.vertex_shader_params().path = new char16[]{L"./Shaders/Shader.hlsl"};
    shaders_.pixel_shader_params().path = new char16[]{L"./Shaders/Shader.hlsl"};
}
