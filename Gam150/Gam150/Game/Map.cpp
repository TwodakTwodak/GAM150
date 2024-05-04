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
#include "Player.h"
#include "Crates.h"

Player* player_ptr = nullptr;

Map::Map() { }

void Map::Load() {
	player_ptr = new Player({300, floor, 300});
	gameobjectmanager.Add(player_ptr);
	gameobjectmanager.Add(new Crates({ 600, floor, 200 }));
	gameobjectmanager.Add(new Crates({ 200, floor, 400 }));
	gameobjectmanager.Add(new Crates({ 400, floor, 300 }));
	gameobjectmanager.Reorder(gameobjectmanager.main_view);
}

void Map::Update([[maybe_unused]] double dt) {
	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::F)) {
		gameobjectmanager.main_view = static_cast<View>(!static_cast<bool>(gameobjectmanager.main_view));
		gameobjectmanager.ChangeAll(dt);
	}
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