/*
File Name:  Player.cpp
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#include "Float_Floor.h"

Float_Floor::Float_Floor(Math::vec3 start_position) : Gam150::GameObject(start_position)
{
    collision_type = Block;
    AddGOComponentSide(new Gam150::Sprite("Assets/Side_Float_Floor.spt", "Assets/Top_Float_Floor.spt", this));
}
