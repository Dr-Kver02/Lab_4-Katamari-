#pragma once

#include "../../Lib/Types.h"

namespace engine
{
    namespace transform
    {
        class TransformComponent
        {
        public:
            TransformComponent();

            void Compose(TransformComponent* parent);
            void UpdateWorldMatrix();

            TransformComponent* parent() const;

            float3& local_position();
            DirectX::SimpleMath::Quaternion& local_rotation();
            float3& local_scale();

            float4x4& world_matrix();

        private:
            TransformComponent* parent_ = nullptr;

            float3 local_position_;
            DirectX::SimpleMath::Quaternion local_rotation_;
            float3 local_scale_;

            float4x4 world_matrix_;
        };
    }
}
