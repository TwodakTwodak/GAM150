/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "GameObject.h"
#include "Matrix.h"
#include <iostream>

CS230::GameObject::GameObject() :
    GameObject({0, 0, 0}, 0, { 1, 1, 1 })
{
}

CS230::GameObject::GameObject(Math::vec3 position) :
    GameObject(position, 0, { 1, 1, 1 })
{}

CS230::GameObject::GameObject(Math::vec3 position, double rotation, Math::vec3 scale) :
    velocity({ 0, 0, 0 }),
    position(position),
    scale(scale),
    rotation(rotation),
    current_state(&state_none)
{}

void CS230::GameObject::Update(double dt) {
    check_view();
    view_sprite->Update(dt);
    current_state->Update(this, dt);
    if (velocity.x != 0 || velocity.y != 0 || velocity.z != 0) {
        UpdatePosition(velocity * dt);
    }
    current_state->CheckExit(this);
}

void CS230::GameObject::change_state(State* new_state) {
    current_state = new_state;
    current_state->Enter(this);
}

//
void CS230::GameObject::Draw(Math::TransformationMatrix camera_matrix) {
    view_sprite->Draw(camera_matrix * GetMatrix());
}

void CS230::GameObject::DrawEditor(Math::TransformationMatrix camera_matrix) {
    side_sprite.Draw(camera_matrix * GetMatrixEditorSide());
    top_sprite.Draw(camera_matrix * GetMatrixEditorTop());
}

void CS230::GameObject::check_view()
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

const Math::TransformationMatrix& CS230::GameObject::GetMatrix() {
    //this make problem!!!
    if (!matrix_outdated) {
        object_matrix = Math::TranslationMatrix(Math::vec2({position.x, *view_position })) * Math::ScaleMatrix({scale.x, *view_scale });
        matrix_outdated = true;
    }
    return object_matrix;
}
const Math::TransformationMatrix& CS230::GameObject::GetMatrixEditorSide() {
    //this make problem!!!
    object_matrix = Math::TranslationMatrix(Math::vec2({ position.x , position.z })) * Math::ScaleMatrix({ scale.x, scale.z });
    return object_matrix;
}
const Math::TransformationMatrix& CS230::GameObject::GetMatrixEditorTop() {
    //this make problem!!!
    object_matrix = Math::TranslationMatrix(Math::vec2({ position.x + Engine::GetWindow().GetSize().x / 2, position.y })) * Math::ScaleMatrix({ scale.x, scale.y });
    return object_matrix;
}
const Math::vec3& CS230::GameObject::GetPosition() const
{
    return position;
}

const Math::vec3& CS230::GameObject::GetVelocity() const
{
    return velocity;
}

const Math::vec3& CS230::GameObject::GetScale() const
{
    return scale;
}

View CS230::GameObject::GetView() const
{
    return current_view;
}



void CS230::GameObject::SetPosition(Math::vec3 new_position) {
    matrix_outdated = false;
    position = new_position;
}

void CS230::GameObject::UpdatePosition(Math::vec3 delta) {
    matrix_outdated = false;
    position += delta;
}

void CS230::GameObject::SetVelocity(Math::vec3 new_velocity)
{
    matrix_outdated = false;
    velocity = new_velocity;
}

void CS230::GameObject::UpdateVelocity(Math::vec3 delta)
{
    matrix_outdated = false;
    velocity += delta;
}

void CS230::GameObject::SetScale(Math::vec3 new_scale)
{
    matrix_outdated = false;
    scale = new_scale;
}

void CS230::GameObject::UpdateScale(Math::vec3 delta)
{
    matrix_outdated = false;
    scale += delta;
}

void CS230::GameObject::SetView(View view)
{
    matrix_outdated = false;
    current_view = view;
}