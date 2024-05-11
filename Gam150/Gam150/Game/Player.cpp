#include "Player.h"
#include "../Engine/Engine.h"
#include "Map.h"
#include "../Engine/Collision.h"

Player::Player(Math::vec3 start_position) : cool_timer(cool_time),
    GameObject(start_position)
{
    side_sprite.Load("Assets/Ship.spt");
    top_sprite.Load("Assets/Ship.spt");
    
}

void Player::move(double dt) {
    if (cool_timer >= 0) {
        cool_timer += dt;
    }
   
    Engine::GetLogger().LogError("time: " + std::to_string(cool_timer));
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        SetVelocity({ max_velocity, GetVelocity().y, GetVelocity().z });

        if (!GetView()) {
            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left_Shift) && cool_timer >= cool_time) {
                dash_start_pos = GetPosition().x;
                SetVelocity({ dash_velocity, GetVelocity().y, GetVelocity().z });
                cool_timer = 0;
            }
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        SetVelocity({ -max_velocity, GetVelocity().y, GetVelocity().z });

        if (!GetView()) {
            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left_Shift) && cool_timer >= cool_time) {
                dash_start_pos = GetPosition().x;
                SetVelocity({ -dash_velocity, GetVelocity().y, GetVelocity().z });
                cool_timer = 0;
            }
        }
    }
    else {
        SetVelocity({ 0, GetVelocity().y, GetVelocity().z });
    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        if (GetView()) {
            if (!jumping && !falling) {
                jumping = true;
                SetVelocity({ GetVelocity().x, jump_velocity, GetVelocity().z });
            }
            else if (jumping && Engine::GetInput().KeyJustReleased(CS230::Input::Keys::W)) {
                SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
            }
        }
        else {
            SetVelocity({ GetVelocity().x , GetVelocity().y, max_velocity });
        }
        if (!GetView()) {

            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left_Shift) && cool_timer >= cool_time) {
                dash_start_pos = GetPosition().z;
                SetVelocity({ GetVelocity().x, GetVelocity().y, dash_velocity });
                cool_timer = 0;
            }
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::S) && !GetView()) {
        SetVelocity({ GetVelocity().x , GetVelocity().y, -max_velocity });
        if (!GetView()) {
            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left_Shift) && cool_timer >= cool_time) {
                dash_start_pos = GetPosition().z;
                SetVelocity({ GetVelocity().x, GetVelocity().y, -dash_velocity });
                cool_timer = 0;
            }
        }
    }
    else {
        SetVelocity({ GetVelocity().x, GetVelocity().y, 0 });
    }

    if (GetVelocity().y < 0) {
        falling = true;
    }
}


void Player::gravity(double dt)
{
    if (GetPosition().y > Map::floor) {
        UpdateVelocity({ 0 , -Map::gravity * dt, 0 });
    }
    if (GetPosition().y <= Map::floor && falling) {
        SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
        SetPosition({ GetPosition().x, Map::floor, GetPosition().z });
        jumping = false;
        falling = false;
    }
}

void Player::Update(double dt) {
    check_view();
    gravity(dt);
    move(dt);
    GameObject::Update(dt);
}

void Player::Collision(GameObject* compare)
{
    UpdatePosition(collision->GetDistance(compare));

    if (collision->distance.y != 0) {
        SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
        if (collision->distance.y > 0) {
            falling = false;
        }
        else {
            falling = true;
        }
        jumping = false;
    }
}
