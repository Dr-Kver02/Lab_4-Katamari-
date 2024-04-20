#include "Shaders.h"

#include <d3dcompiler.h>

using namespace engine::graphics;

void Shaders::Create(const RenderPipeline* pipeline)
{
    auto* vertex_shader_byte_code = CreateVertexShader(pipeline);
    CreatePixelShader(pipeline);
    CreateInputLayout(pipeline, vertex_shader_byte_code);
}

ShaderCompileParams& Shaders::vertex_shader_params()
{
    return vertex_shader_params_;
}

ShaderCompileParams& Shaders::pixel_shader_params()
{
    return pixel_shader_params_;
}

InputLayoutParams& Shaders::input_layout_params()
{
    return input_layout_params_;
}

DXVertexShader* Shaders::vertex_shader() const
{
    return vertex_shader_;
}

DXPixelShader* Shaders::pixel_shader() const
{
    return pixel_shader_;
}

DXInputLayout* Shaders::input_layout() const
{
    return input_layout_;
}

DXBlob* Shaders::CreateVertexShader(const RenderPipeline* pipeline)
{
    DXBlob* error;
    DXBlob* vertex_shader_byte_code;
    kCompileShader(&vertex_shader_byte_code, &error, vertex_shader_params_);
    pipeline->device()->CreateVertexShader(
        vertex_shader_byte_code->GetBufferPointer(), vertex_shader_byte_code->GetBufferSize(),
        nullptr, &vertex_shader_);
    return vertex_shader_byte_code;
}

DXBlob* Shaders::CreatePixelShader(const RenderPipeline* pipeline)
{
    DXBlob* error;
    DXBlob* pixel_shader_byte_code;
    kCompileShader(&pixel_shader_byte_code, &error, pixel_shader_params_);
    pipeline->device()->CreatePixelShader(
        pixel_shader_byte_code->GetBufferPointer(), pixel_shader_byte_code->GetBufferSize(),
        nullptr, &pixel_shader_);
    return pixel_shader_byte_code;
}

void Shaders::CreateInputLayout(const RenderPipeline* pipeline, DXBlob* vertex_shader_byte_code)
{
    pipeline->device()->CreateInputLayout(
        input_layout_params_.input_element_descriptors, input_layout_params_.elements_number,
        vertex_shader_byte_code->GetBufferPointer(),
        vertex_shader_byte_code->GetBufferSize(), &input_layout_);
}

void Shaders::kCompileShader(DXBlob** shader_byte_code, DXBlob** error, const ShaderCompileParams& params)
{
    D3DCompileFromFile(
        params.path, params.defines, params.include, params.entrypoint, params.target,
        params.flags1, params.flags2, shader_byte_code, error);
}
