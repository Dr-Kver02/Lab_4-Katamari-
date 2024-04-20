#pragma once
#include "../Engine/Input/Device.h"
#include "../Engine/Update/VariableUpdateAble.h"
#include "../Objects/CameraObject.h"

namespace controllers
{
    class CameraController : public engine::update::VariableUpdateAble
    {
    public:
        void Compose(objects::CameraObject* camera_object, engine::input::Device* device);

    protected:
        virtual void OnMouseEvent(const engine::input::mouse::Event& args) = 0;
        virtual void OnKeyboardEvent(const engine::input::keyboard::Event& args);

        objects::CameraObject* camera_object_ = nullptr;
        engine::input::Device* device_ = nullptr;
    };
}
