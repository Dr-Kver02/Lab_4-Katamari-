#pragma once
#include <string>

#include "MeshComponent.h"
#include "../Lib/assimp/Importer.hpp"
#include "../Lib/assimp/mesh.h"

namespace components
{
    class ModelComponent : public engine::graphics::RenderAble
    {
    public:
        void Compose(const std::string& model_file_path, const std::string& texture_file_path);
        void Compose(engine::graphics::RenderPipeline* pipeline) override;
        void Compose(engine::transform::TransformComponent* transform);

        void Render(const float4x4& camera, float delta) override;

    private:
        void ProcessNode(const aiNode* node, const aiScene* scene, const std::string& texture_file_path);

        std::vector<MeshComponent> meshes_{};
    };
}
