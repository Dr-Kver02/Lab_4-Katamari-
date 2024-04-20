#pragma once
#include "RenderPipeline.h"
#include "../../Lib/Types.h"

namespace engine
{
    namespace graphics
    {
        struct BufferParams
        {
            DXBufferDescriptor buffer_descriptor;
            DXSubresourceData subresource_data;
        };

        class Buffers
        {
        public:
            void Create(const RenderPipeline* pipeline);

            BufferParams& vertex_buffer_params();
            BufferParams& index_buffer_params();
            BufferParams& transform_buffer_params();
            DXBuffer* vertex_buffer() const;
            DXBuffer* const* vertex_buffer_pointer() const;
            DXBuffer* index_buffer() const;
            DXBuffer* transform_buffer() const;
            DXBuffer* const* transform_buffer_pointer() const;

        private:
            BufferParams vertex_buffer_params_{};
            BufferParams index_buffer_params_{};
            BufferParams transform_buffer_params_{};
            DXBuffer* vertex_buffer_ = nullptr;
            DXBuffer* index_buffer_ = nullptr;
            DXBuffer* transform_buffer_ = nullptr;
        };
    }
}
