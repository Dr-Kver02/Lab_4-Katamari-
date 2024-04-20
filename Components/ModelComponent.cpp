#include "ModelComponent.h"

#include "../Lib/assimp/scene.h"

#include "../Lib/assimp/postprocess.h"

using namespace components;

void ModelComponent::Compose(const std::string& model_file_path, const std::string& texture_file_path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(model_file_path, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
    ProcessNode(scene->mRootNode, scene, texture_file_path);
}

void ModelComponent::Compose(engine::graphics::RenderPipeline* pipeline)
{
    RenderAble::Compose(pipeline);
    for (auto& mesh : meshes_) mesh.Compose(pipeline_);
}

void ModelComponent::Compose(engine::transform::TransformComponent* transform)
{
    for (auto& mesh : meshes_) mesh.Compose(transform);
}

void ModelComponent::Render(const float4x4& camera, float delta)
{
    for (auto& mesh : meshes_) mesh.Render(camera, delta);
}

void ModelComponent::ProcessNode(const aiNode* node, const aiScene* scene, const std::string& texture_file_path)
{
    for (uint32 i = 0; i < node->mNumMeshes; i++)
    {
        MeshComponent mesh(scene->mMeshes[node->mMeshes[i]]);
        mesh.Compose(texture_file_path);
        meshes_.push_back(std::move(mesh));
    }

    for (uint32 i = 0; i < node->mNumChildren; i++)
        ProcessNode(node->mChildren[i], scene, texture_file_path);
}
