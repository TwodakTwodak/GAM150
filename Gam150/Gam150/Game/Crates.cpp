/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Crates.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Crates.h"

Crates::Crates(Math::vec3 start_position) : 
    CS230::GameObject(start_position) 
{
    side_sprite.Load("Assets/Crates1.spt");
    top_sprite.Load("Assets/Crates1.spt");
}
