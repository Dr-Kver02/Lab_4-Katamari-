#include "CameraController.h"

#include "../Game.h"

using namespace controllers;

void CameraController::Compose(objects::CameraObject* camera_object, engine::input::Device* device)
{
    camera_object_ = camera_object;
    device_ = device;
    device_->mouse_event.AddRaw(this, &CameraController::OnMouseEvent);
    device_->keyboard_event.AddRaw(this, &CameraController::OnKeyboardEvent);
}

void CameraController::OnKeyboardEvent(const engine::input::keyboard::Event& args)
{
    if (args.code != engine::input::keyboard::Keys::Tab || args.button != engine::input::keyboard::Buttons::Down)
        return;
    if (camera_object_->camera()->is_perspective())
        camera_object_->camera()->UpdateProjectionMatrixOrthographic();
    else
        camera_object_->camera()->UpdateProjectionMatrixPerspective();
}
