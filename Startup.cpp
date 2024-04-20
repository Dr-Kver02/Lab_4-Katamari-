#include "Game.h"
#include "Components/ModelComponent.h"
#include "Components/SquareComponent.h"
#include "Controllers/CameraControllerRadial.h"
#include "Controllers/PlayerController.h"
#include "Objects/CameraObject.h"
#include "Objects/FoodObject.h"
#include "Objects/FoodSpawnerObject.h"
#include "Objects/PlayerObject.h"

int main()
{
    auto* game = Game::Instance();
    constexpr auto size = Point{800, 800};

    auto* camera_object = new objects::CameraObject();
    camera_object->Compose(size);

    game->Compose(L"Game", size, 0.1f, camera_object->camera());

    auto* camera_controller_radial = new controllers::CameraControllerRadial();
    camera_controller_radial->Compose(camera_object, game->input_device());
    game->variable_update()->Add(camera_controller_radial);

    auto* player = new objects::PlayerObject();
    player->Compose(float3(0, 0, -2), float3(0.05f), float3(0.3f), float3(0.02f), float3(0.005f),
                    std::string("Data\\Ball.fbx"), std::string("Data\\Ball-texture.jpg"));
    game->render_pipeline()->Add(player);
    game->physics_collision()->Add(player);

    camera_controller_radial->SetFollowing(player->transform(), float3(0, 1, 2));

    auto* player_controller = new controllers::PlayerController();
    player_controller->Compose(player, camera_object, game->input_device());
    game->variable_update()->Add(player_controller);

    std::string file_paths[] = {"Data\\MALE.fbx", "Data\\Male_texture.png", "Data\\FEMALE.fbx", "Data\\Female_texture.png"};
    float probabilities[] = {0.5f, 0.5f};

    auto* food_spawner = new objects::FoodSpawnerObject();
    food_spawner->Compose(file_paths, probabilities, float2(10, 10), 20);
    game->render_pipeline()->Add(food_spawner);
    game->variable_update()->Add(food_spawner);
    food_spawner->Compose(game->physics_collision());

    game->Run();
}
