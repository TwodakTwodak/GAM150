/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    Gam150 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Collision.h"
#include "GameObject.h"

Gam150::GameObject::GameObject() :
    GameObject({0, 0, 0}, 0, { 1, 1, 1 })
{
}

Gam150::GameObject::GameObject(Math::vec3 position) :
    GameObject(position, 0, { 1, 1, 1 })
{}

Gam150::GameObject::GameObject(Math::vec3 position, double rotation, Math::vec3 scale) :
    velocity({ 0, 0, 0 }),
    position(position),
    scale(scale),
    rotation(rotation),
    current_state(&state_none)
{}

Gam150::GameObject::~GameObject()
{
    //delete collision;
}

void Gam150::GameObject::Update(double dt) {
    check_view();
    view_sprite->Update(dt);
    current_state->Update(this, dt);
    if (velocity.x != 0 || velocity.y != 0 || velocity.z != 0) {
        UpdatePosition(velocity * dt);
    }
    collision_cube.bottom_behind = {
        position.x,
        position.y,
        position.z
    };
    collision_cube.top_front = {
        position.x + side_sprite.texture->GetSize().x,
        position.y + side_sprite.texture->GetSize().y,
        position.z + top_sprite.texture->GetSize().y
    };

    current_state->CheckExit(this);
}

void Gam150::GameObject::change_state(State* new_state) {
    current_state = new_state;
    current_state->Enter(this);
}

//
void Gam150::GameObject::Draw(Math::TransformationMatrix camera_matrix) {
    //collision->CollisionDraw();
    view_sprite->Draw(camera_matrix * GetMatrix());
}

void Gam150::GameObject::check_view()
{
    if (!matrix_outdated) {
        if (current_view) {
            view_sprite = &side_sprite;
            view_position = &(position.y);
            view_scale = &(scale.y);
        }
        else {
            view_sprite = &top_sprite;
            view_position = &(position.z);
            view_scale = &(scale.z);
        }
    }
}

void Gam150::GameObject::Collision(GameObject* compare, Collision_Type type) { }

const Math::TransformationMatrix& Gam150::GameObject::GetMatrix() {
    //this make problem!!!
    if (!matrix_outdated) {
        object_matrix = Math::TranslationMatrix(Math::vec2({position.x, *view_position })) * Math::ScaleMatrix({scale.x, *view_scale });
        matrix_outdated = true;
    }
    return object_matrix;
}

const Math::vec3& Gam150::GameObject::GetPosition() const
{
    return position;
}

const Math::vec3& Gam150::GameObject::GetVelocity() const
{
    return velocity;
}

const Math::vec3& Gam150::GameObject::GetScale() const
{
    return scale;
}

View Gam150::GameObject::GetView() const
{
    return current_view;
}

double Gam150::GameObject::GetRotation() const
{
    return rotation;
}



void Gam150::GameObject::SetPosition(Math::vec3 new_position) {
    matrix_outdated = false;
    position = new_position;
}

void Gam150::GameObject::UpdatePosition(Math::vec3 delta) {
    matrix_outdated = false;
    position += delta;
}

void Gam150::GameObject::SetVelocity(Math::vec3 new_velocity)
{
    matrix_outdated = false;
    velocity = new_velocity;
}

void Gam150::GameObject::UpdateVelocity(Math::vec3 delta)
{
    matrix_outdated = false;
    velocity += delta;
}

void Gam150::GameObject::SetScale(Math::vec3 new_scale)
{
    matrix_outdated = false;
    scale = new_scale;
}

void Gam150::GameObject::UpdateScale(Math::vec3 delta)
{
    matrix_outdated = false;
    scale += delta;
}

void Gam150::GameObject::SetRotation(double new_rotation) {
    rotation = new_rotation;
}

void Gam150::GameObject::UpdateRotation(double delta)
{
    rotation += delta;
}

void Gam150::GameObject::SetView(View view)
{
    matrix_outdated = false;
    current_view = view;
}

Collision_Type Gam150::GameObject::GetType() const
{
    return collision_type;
}

bool Gam150::GameObject::IsCollidingWith(GameObject* other_object) {
    Gam150::Collision* collider = GetGOComponent<Gam150::Collision>();
    return collider != nullptr && collider->IsCollidingWith(other_object);
}

bool Gam150::GameObject::CanCollideWith(GameObjectTypes other_object_type) {
    return false;
}
