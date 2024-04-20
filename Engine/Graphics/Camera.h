#pragma once

#include "../../Lib/Types.h"
#include "../Transform/TransformComponent.h"

namespace engine
{
    namespace graphics
    {
        struct CameraPerspectiveParams
        {
            float field_of_view;
            float aspect_ratio;
            float near_z;
            float far_z;
        };

        struct CameraOrthographicParams
        {
            float width;
            float height;
            float near_z;
            float far_z;
        };

        class Camera final
        {
        public:
            Camera();

            void Compose();
            void Compose(transform::TransformComponent* transform);
            void UpdateViewMatrix();
            void UpdateProjectionMatrixPerspective();
            void UpdateProjectionMatrixOrthographic();

            CameraPerspectiveParams& perspective_params();
            CameraOrthographicParams& orthographic_params();

            float4x4& view_matrix();
            float4x4& projection_matrix();

            bool is_perspective() const;

        private:
            transform::TransformComponent* transform_ = nullptr;

            CameraPerspectiveParams perspective_params_{};
            CameraOrthographicParams orthographic_params_{};

            float4x4 view_matrix_;
            float4x4 projection_matrix_;

            bool is_perspective_ = false;
        };
    }
}
