#include "MeshComponent.h"

#include "../Lib/assimp/Importer.hpp"
#include "../Lib/assimp/scene.h"
#include "../Lib/assimp/Vertex.h"

using namespace components;

MeshComponent::MeshComponent(const aiMesh* mesh)
{
    for (uint32 i = 0; i < mesh->mNumVertices; i++)
    {
        float4 pos(mesh->mVertices[i].x, pos.y = mesh->mVertices[i].y, mesh->mVertices[i].z, 0);
        points_.push_back(pos);

        if (mesh->mTextureCoords[0])
        {
            float4 tex(tex.x = mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y, 0, 0);
            points_.push_back(tex);
        }
        else points_.push_back(float4());
    }

    for (uint32 i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace face = mesh->mFaces[i];

        for (uint32 j = 0; j < face.mNumIndices; j++)
            indexes_.push_back(face.mIndices[j]);
    }

    index_count_ = static_cast<uint32>(indexes_.size());

    buffers_.vertex_buffer_params().buffer_descriptor.ByteWidth = sizeof(float4) * static_cast<uint32>(points_.size());
    buffers_.vertex_buffer_params().subresource_data.pSysMem = points_.data();

    buffers_.index_buffer_params().buffer_descriptor.ByteWidth = sizeof(int32) * static_cast<uint32>(indexes_.size());
    buffers_.index_buffer_params().subresource_data.pSysMem = indexes_.data();

    shaders_.vertex_shader_params().path = new char16[]{L"./Shaders/Shader.hlsl"};
    shaders_.pixel_shader_params().path = new char16[]{L"./Shaders/Shader.hlsl"};
}
