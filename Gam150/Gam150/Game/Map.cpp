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
#include "Button.h"
#include "../Engine/FileIO.h"
#include "../Engine/Window.h"

Player* player_ptr = nullptr;

Map::Map() { }

void Map::Load() {
	if (went_editor)
	{
		Engine::GetWindow().MapWindow();
		went_editor = false;
	}
	
	player_ptr = new Player({ 300, floor, 300 });
	gameobjectmanager.Add(player_ptr);
	if (room_object_memory[room] == 0)
	{
		while (GetRoom(load_object_number) <= room && GetRoom(load_object_number) != 0)
		{
			if (GetRoom(load_object_number) == room)//check room
			{
				if (GetType(load_object_number) == "box")//check type
				{
					gameobjectmanager.Add(new Crates(GetPosition(load_object_number)));
				}
				if (GetType(load_object_number) == "button")//check type
				{
					gameobjectmanager.Add(new Button(GetPosition(load_object_number)));
				}
			}
			load_object_number++;
		}
		room_object_memory[room] = load_object_number - room_object_memory[room - 1];
	}
	else
	{
		int max_temp = room_object_memory[room] + room_object_memory[room - 1];
		int temp_load_object_number = room_object_memory[room - 1];

		while (temp_load_object_number < max_temp)
		{
			if (GetRoom(temp_load_object_number) == room)//check room
			{
				if (GetType(temp_load_object_number) == "box")//check type
				{
					gameobjectmanager.Add(new Crates(GetPosition(temp_load_object_number)));
				}
				if (GetType(temp_load_object_number) == "button")//check type
				{
					gameobjectmanager.Add(new Button(GetPosition(temp_load_object_number)));
				}
			}
			temp_load_object_number++;
		}
	}

	gameobjectmanager.Reorder(gameobjectmanager.main_view);
}

void Map::Update([[maybe_unused]] double dt) {
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::F)) {
		gameobjectmanager.ChangeAll();
	}
	gameobjectmanager.UpdateAll(dt);
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
		room++;
		Unload();
		Load();
	}
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)) {
		room--;
		Unload();
		Load();
	}
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::P)) {
		Engine::GetGameStateManager().ClearNextGameState();
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Editor));
		went_editor = true;
	}
}

void Map::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	gameobjectmanager.DrawAll(Math::TransformationMatrix());
}

void Map::Unload() {
	gameobjectmanager.Unload();
	player_ptr = nullptr;
}