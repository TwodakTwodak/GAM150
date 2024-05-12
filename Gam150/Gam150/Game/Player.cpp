/*
File Name:  Player.cpp
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#include "Player.h"
#include "../Engine/Engine.h"
#include "Map.h"
#include "../Engine/Collision.h"

Player::Player(Math::vec3 start_position) : cool_timer(cool_time),
    GameObject(start_position)
{
    side_sprite.Load("Assets/Side_Player.spt");
    top_sprite.Load("Assets/Top_Player.spt");
    
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
                gravi = false;
            }
            gravi = true;
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        SetVelocity({ -max_velocity, GetVelocity().y, GetVelocity().z });
        if (!GetView()) {
            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left_Shift) && cool_timer >= cool_time) {
                dash_start_pos = GetPosition().x;
                SetVelocity({ -dash_velocity, GetVelocity().y, GetVelocity().z });
                cool_timer = 0;
                gravi = false;
            }
            gravi = true;
        }
    }
    else {
        SetVelocity({ 0, GetVelocity().y, GetVelocity().z });
    }
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
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
    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        
        if (!GetView()) {

            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left_Shift) && cool_timer >= cool_time) {
                dash_start_pos = GetPosition().z;
                SetVelocity({ GetVelocity().x, GetVelocity().y, dash_velocity });
                cool_timer = 0;
                gravi = false;
            }
            gravi = true;
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::S) && !GetView()) {
        SetVelocity({ GetVelocity().x , GetVelocity().y, -max_velocity });
        if (!GetView()) {
            if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left_Shift) && cool_timer >= cool_time) {
                dash_start_pos = GetPosition().z;
                SetVelocity({ GetVelocity().x, GetVelocity().y, -dash_velocity });
                cool_timer = 0;
                gravi = false;
            }
            gravi = true;
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
    if (gravi == true) {
        UpdateVelocity({ 0 , -Map::gravity * dt, 0 });
    }
}

void Player::Update(double dt) {
    gravity(dt);
    move(dt);
    GameObject::Update(dt);
}

void Player::Collision(GameObject* compare, Collision_Type type)
{
    if (type == Block) {
        Collision_Floor(compare);
    }
    else if (type == Move) {
        Collision_Box(compare);
    }
}

void Player::Collision_Floor(GameObject* compare)
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

void Player::Collision_Box(GameObject* compare)
{
    collision->GetDistance(compare);
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
    UpdatePosition({ 0, collision->distance.y, 0 });
    compare->UpdatePosition({ -collision->distance.x, 0, -collision->distance.z });
}
