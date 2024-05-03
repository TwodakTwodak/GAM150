/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Upadted:    March 14, 2024
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Map.h"

Map::Map() { }

void Map::Load() {
	player_ptr = new Player{{300, floor, 300}};
	gameobjectmanager.Add(player_ptr);
}

void Map::Update([[maybe_unused]] double dt) {
	gameobjectmanager.UpdateAll(dt);
}

void Map::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	gameobjectmanager.DrawAll(Math::TransformationMatrix());

}

void Map::Unload() {
	gameobjectmanager.Unload();
	player_ptr = nullptr;
}