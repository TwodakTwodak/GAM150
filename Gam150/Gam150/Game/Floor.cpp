/*
File Name:  Player.cpp
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#include "Floor.h"

Floor::Floor(Math::vec3 start_position)
{
    collision_type = Block;
    AddGOComponentSide(new Gam150::Sprite("Assets/Side_Floor.spt", "Assets/Top_Floor.spt", this));
}
