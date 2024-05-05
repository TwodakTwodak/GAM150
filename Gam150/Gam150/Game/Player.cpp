#include "Player.h"
#include "../Engine/Engine.h"
#include "Map.h"

Player::Player(Math::vec3 start_position) :
	GameObject(start_position)
{
	side_sprite.Load("Assets/Ship.spt");
    top_sprite.Load("Assets/Meteor.spt");
}

void Player::update_x_velocity(double dt)
{
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        UpdateVelocity({ xz_acceleration * dt , 0, 0 });
        if (GetVelocity().x > max_velocity) {
            SetVelocity({ max_velocity , GetVelocity().y, GetVelocity().z });
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        UpdateVelocity({ -xz_acceleration * dt , 0, 0 });
        if (GetVelocity().x < -max_velocity) {
            SetVelocity({ -max_velocity , GetVelocity().y, GetVelocity().z });
        }
    }
    else {
        if (GetVelocity().x > xz_drag * dt) {
            UpdateVelocity({ -xz_drag * dt , 0, 0 });
        }
        else if (GetVelocity().x < -xz_drag * dt) {
            UpdateVelocity({ xz_drag * dt , 0, 0 });
        }
        else {
            SetVelocity({ 0 , GetVelocity().y, GetVelocity().z });
        }
    }
}

//jump
void Player::update_y_velocity(double dt)
{
    //jump
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
        SetVelocity({ GetVelocity().x , jump_velocity, GetVelocity().z });
    }
    if(Engine::GetInput().KeyJustReleased(CS230::Input::Keys::W)){
        SetVelocity({ GetVelocity().x , 0, GetVelocity().z });
    }
    if (GetVelocity().y != 0) {
        if (GetPosition().y <= Map::floor) {
            SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
            SetPosition({ GetPosition().x, Map::floor, GetPosition().z });
        }
        UpdateVelocity({ 0 , -Map::gravity * dt, 0 });
    }
}

void Player::update_z_velocity(double dt)
{
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        UpdateVelocity({ 0, 0, xz_acceleration * dt });
        if (GetVelocity().z > max_velocity) {
            SetVelocity({ GetVelocity().x , GetVelocity().y, max_velocity });
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::S)) {
        UpdateVelocity({ 0, 0, -xz_acceleration * dt });
        if (GetVelocity().z < -max_velocity) {
            SetVelocity({ GetVelocity().x , GetVelocity().y, -max_velocity });
        }
    }
    else {
        if (GetVelocity().z > xz_drag * dt) {
            UpdateVelocity({ 0, 0, -xz_drag * dt });
        }
        else if (GetVelocity().z < -xz_drag * dt) {
            UpdateVelocity({ 0, 0, xz_drag * dt });
        }
        else {
            SetVelocity({ GetVelocity().x , GetVelocity().y, 0});
        }
    }
}

void Player::change_view(double dt)
{
    if (GetView()) {
        //update_y_velocity(dt);
    }
    else {
        update_z_velocity(dt);
    }
}

void Player::Update(double dt) {
    change_view(dt);
    check_view();
	GameObject::Update(dt);
    update_x_velocity(dt);
}
