#include "Player.h"
#include "../Engine/Engine.h"
#include "Map.h"
#include "../Engine/Collision.h"

Player::Player(Math::vec3 start_position) :
	GameObject(start_position)
{
	side_sprite.Load("Assets/Ship.spt");
    top_sprite.Load("Assets/Ship.spt");
}

void Player::move(double dt)
{
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        SetVelocity({ max_velocity , GetVelocity().y, GetVelocity().z });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        SetVelocity({ -max_velocity , GetVelocity().y, GetVelocity().z });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::W) && !GetView()) {
        SetVelocity({ GetVelocity().x , GetVelocity().y, max_velocity });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::S) && !GetView()) {
        SetVelocity({ GetVelocity().x , GetVelocity().y, -max_velocity });
    }
    else {
        SetVelocity({ 0 , GetVelocity().y, 0 });
    }
    if (GetView()) {
        jump(dt);
    }
}

void Player::jump(double dt)
{
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W) && !jump_able) {
        jump_able = true;
        SetVelocity({ GetVelocity().x , jump_velocity, GetVelocity().z });
        if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::W)) {
            SetVelocity({ GetVelocity().x , 0, GetVelocity().z });
        }
    }
    else if (jump_able) {
        if (GetPosition().y <= Map::floor) {
            SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
            jump_able = false;
            SetPosition({ GetPosition().x, Map::floor, GetPosition().z });
        }
    }
    if (GetPosition().y > Map::floor) {
        UpdateVelocity({ 0 , -Map::gravity * dt, 0 });
    }
}

void Player::Update(double dt) {
    move(dt);
    check_view();
	GameObject::Update(dt);
}

void Player::Collision(GameObject* compare)
{
    if (GetVelocity().x != 0) {
        UpdatePosition({ collision->GetDistanceX(compare), 0, 0 });
    }
    if (GetVelocity().y != 0) {
        UpdatePosition({0, collision->GetDistanceY(compare), 0 });
    }
    if (GetVelocity().z != 0) {
        UpdatePosition({ 0, 0, collision->GetDistanceZ(compare) });
    }
}
