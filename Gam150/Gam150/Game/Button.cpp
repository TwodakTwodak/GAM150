/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Button.cpp
Project:    



Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Button.h"

Button::Button(Math::vec3 start_position) :
    Gam150::GameObject(start_position)
{
    collision_type = Detect;
    AddGOComponentSide(new Gam150::Sprite("Assets/Side_Button.spt", "Assets/Top_Button.spt", this));
}

void Button::Update(double dt)
{
    if (press) {
        Engine::GetLogger().LogEvent("Collision");
    }
    GameObject::Update(dt);
}


