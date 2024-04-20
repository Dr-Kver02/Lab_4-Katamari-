#include "Game.h"

#include <chrono>

#include "Engine/Input/Keyboard.h"

using namespace engine;

Game* Game::Instance()
{
    static auto* instance = new Game();
    return instance;
}

void Game::Compose(const char16* name, Point size, float fixed_delta, graphics::Camera* camera)
{
    window_->Compose(name, size);
    input_device_->Compose(window_->handler_window());
    pipeline_->Compose(window_->handler_window(), size);
    fixed_update_->Compose(fixed_delta);
    variable_update_->Compose(fixed_update_);

    fixed_update_->Add(physics_movement_);
    fixed_update_->Add(physics_collision_);

    camera_ = camera;
}

void Game::Run()
{
    while (!is_finished_)
    {
        Input();
        fixed_update_->Update();
        variable_update_->Update();
        pipeline_->Render(
            camera_->view_matrix() * camera_->projection_matrix(),
            static_cast<float>(fixed_update_->timer().delta()));
    }
}

void Game::Destroy() const
{
    pipeline_->Destroy();
    input_device_->Destroy();
    window_->Destroy();
    delete camera_;
    delete physics_movement_;
    delete physics_collision_;
    delete variable_update_;
    delete fixed_update_;
    delete pipeline_;
    delete input_device_;
    delete window_;
}

update::VariableUpdate* Game::variable_update() const
{
    return variable_update_;
}

graphics::Camera* Game::camera() const
{
    return camera_;
}

void Game::Input()
{
    MSG msg;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (msg.message == WM_QUIT) is_finished_ = true;
    if (input_device_->IsKeyDown(input::keyboard::Keys::Escape)) is_finished_ = true;
}
