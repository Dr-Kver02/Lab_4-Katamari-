#include "Buffers.h"

using namespace engine::graphics;

void Buffers::Create(const RenderPipeline* pipeline)
{
    auto* device = pipeline->device();
    device->CreateBuffer(
        &vertex_buffer_params_.buffer_descriptor, &vertex_buffer_params_.subresource_data, &vertex_buffer_);
    device->CreateBuffer(
        &index_buffer_params_.buffer_descriptor, &index_buffer_params_.subresource_data, &index_buffer_);
    device->CreateBuffer(
        &transform_buffer_params_.buffer_descriptor, &transform_buffer_params_.subresource_data, &transform_buffer_);
}

BufferParams& Buffers::vertex_buffer_params()
{
    return vertex_buffer_params_;
}

BufferParams& Buffers::index_buffer_params()
{
    return index_buffer_params_;
}

BufferParams& Buffers::transform_buffer_params()
{
    return transform_buffer_params_;
}

DXBuffer* Buffers::vertex_buffer() const
{
    return vertex_buffer_;
}

DXBuffer* const* Buffers::vertex_buffer_pointer() const
{
    return &vertex_buffer_;
}

DXBuffer* Buffers::index_buffer() const
{
    return index_buffer_;
}

DXBuffer* Buffers::transform_buffer() const
{
    return transform_buffer_;
}

DXBuffer* const* Buffers::transform_buffer_pointer() const
{
    return &transform_buffer_;
}
