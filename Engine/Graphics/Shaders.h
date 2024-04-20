#pragma once
#include "RenderPipeline.h"
#include "../../Lib/Types.h"

namespace engine
{
    namespace graphics
    {
        struct ShaderCompileParams
        {
            char16* path;
            DXShaderMacros* defines;
            DXIncludes* include;
            char8* entrypoint;
            char8* target;
            uint32 flags1;
            uint32 flags2;
        };

        struct InputLayoutParams
        {
            DXInputElementDescriptor* input_element_descriptors;
            uint32 elements_number;
        };

        class Shaders
        {
        public:
            void Create(const RenderPipeline* pipeline);

            ShaderCompileParams& vertex_shader_params();
            ShaderCompileParams& pixel_shader_params();
            InputLayoutParams& input_layout_params();
            DXVertexShader* vertex_shader() const;
            DXPixelShader* pixel_shader() const;
            DXInputLayout* input_layout() const;

        private:
            DXBlob* CreateVertexShader(const RenderPipeline* pipeline);
            DXBlob* CreatePixelShader(const RenderPipeline* pipeline);
            void CreateInputLayout(const RenderPipeline* pipeline, DXBlob* vertex_shader_byte_code);

            static void kCompileShader(DXBlob** shader_byte_code, DXBlob** error, const ShaderCompileParams& params);

            ShaderCompileParams vertex_shader_params_{};
            ShaderCompileParams pixel_shader_params_{};
            InputLayoutParams input_layout_params_{};
            DXVertexShader* vertex_shader_ = nullptr;
            DXPixelShader* pixel_shader_ = nullptr;
            DXInputLayout* input_layout_ = nullptr;
        };
    }
}
