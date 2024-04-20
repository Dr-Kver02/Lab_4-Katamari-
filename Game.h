#pragma once
#include "Engine/Graphics/Camera.h"
#include "Engine/Graphics/RenderPipeline.h"
#include "Engine/Input/DevicePC.h"
#include "Engine/Physics/Collision.h"
#include "Engine/Physics/Movement.h"
#include "Engine/Graphics/Window.h"
#include "Engine/Update/FixedUpdate.h"
#include "Engine/Update/VariableUpdate.h"

class Game final
{
public:
    static Game* Instance();

    void Compose(const char16* name, Point size, float fixed_delta, engine::graphics::Camera* camera);
    void Run();
    void Destroy() const;

    engine::graphics::Window* window() const { return window_; }
    engine::update::FixedUpdate* fixed_update() const { return fixed_update_; }
    engine::update::VariableUpdate* variable_update() const;
    engine::graphics::RenderPipeline* render_pipeline() const { return pipeline_; }
    engine::input::Device* input_device() const { return input_device_; }
    engine::physics::Collision* physics_collision() const { return physics_collision_; }
    engine::physics::Movement* physics_movement() const { return physics_movement_; }
    engine::graphics::Camera* camera() const;

private:
    void Input();

    engine::graphics::Window* window_ = new engine::graphics::Window();
    engine::update::FixedUpdate* fixed_update_ = new engine::update::FixedUpdate();
    engine::update::VariableUpdate* variable_update_ = new engine::update::VariableUpdate();
    engine::graphics::RenderPipeline* pipeline_ = new engine::graphics::RenderPipeline();
    engine::input::Device* input_device_ = new engine::input::DevicePC();
    engine::physics::Collision* physics_collision_ = new engine::physics::Collision();
    engine::physics::Movement* physics_movement_ = new engine::physics::Movement();
    engine::graphics::Camera* camera_ = nullptr;

    bool is_finished_ = false;
};
