#pragma once
#include "../Engine/Update/VariableUpdateAble.h"
#include "../Engine/Input/Device.h"
#include "../Objects/CameraObject.h"
#include "../Objects/PlayerObject.h"

namespace controllers
{
    class PlayerController final : public engine::update::VariableUpdateAble
    {
    public:
        void Compose(objects::PlayerObject* player_object, objects::CameraObject* camera, engine::input::Device* device);

        void Update(float delta) override;

    private:
        objects::PlayerObject* player_object_ = nullptr;
        objects::CameraObject* camera_ = nullptr;
        engine::input::Device* device_ = nullptr;
    };
}
