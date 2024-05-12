#include "../Engine/Engine.h"
#include "States.h"
#include "Editor.h"
#include "Crates.h"
#include "Button.h"
#include "../Engine/FileIO.h"
#include "../Engine/Window.h"


int editor_save_number = 0;

Editor::Editor() { }

void Editor::Load() {
	if (room_object_memory[room]!=0)
	{
		int max_temp = room_object_memory[room] + room_object_memory[room - 1];
		int temp_load_object_number = room_object_memory[room - 1];
		std::cout << room << std::endl;
		std::cout << room_object_memory[room] << std::endl;
		while (temp_load_object_number < max_temp)
		{
			if (GetRoomEditor(temp_load_object_number) == room)//check room
			{
				if (GetTypeEditor(temp_load_object_number) == "box")//check type
				{
					gameobjectmanager.Add(new Crates(GetPosition(temp_load_object_number)));
				}
				if (GetTypeEditor(temp_load_object_number) == "button")//check type
				{
					gameobjectmanager.Add(new Button(GetPosition(temp_load_object_number)));
				}
			}
			temp_load_object_number++;
		}
	}
	
	
	//load from the previous save
	if (went_map)
	{
		//draw, clear
		Engine::GetWindow().EditorWindow();
		went_map = false;
	}
	
	gameobjectmanager.Reorder(gameobjectmanager.main_view);
}

void Editor::Update([[maybe_unused]] double dt) {
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::F)) {
		gameobjectmanager.ChangeAll();
	}
	gameobjectmanager.UpdateAll(dt);
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up) && object_place == 0) {
		room++;
		if (max_room < room)
		{
			max_room = room;
		}
		Unload();
		Load();
	}
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)&& object_place==0) {
		room--;
		Unload();
		Load();
	}
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::O)) {
		Engine::GetGameStateManager().ClearNextGameState();
		Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Map));
		went_map = true;
	}
	if (!adding_object&& object_place == 0)
	{
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::C))//make crats
		{
			gameobjectmanager.Add(new Crates({ GetMousePosition().x , Engine::GetWindow().GetSize().y - GetMousePosition().y , Engine::GetWindow().GetSize().y - GetMousePosition().y}));
			adding_object = true;
			object_place = 1;
			move_check = false;
			type = "box";
			room_object_memory[room]++;
		}
		if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::B))//make button
		{
			gameobjectmanager.Add(new Button({ GetMousePosition().x , Engine::GetWindow().GetSize().y-GetMousePosition().y ,Engine::GetWindow().GetSize().y - GetMousePosition().y }));
			adding_object = true;
			object_place = 1;
			move_check = false;
			type = "button";
			room_object_memory[room]++;
		}
	}
	else
	{
		if (object_place == 1)
		{
			if (GetMousePosition().x+ gameobjectmanager.ReturnLastInteraction()->GetScale().x > Engine::GetWindow().GetSize().x / 2)
			{
				gameobjectmanager.ReturnLastInteraction()->SetPosition({ Engine::GetWindow().GetSize().x / 2 - gameobjectmanager.ReturnLastInteraction()->GetScale().x, Engine::GetWindow().GetSize().y - GetMousePosition().y ,Engine::GetWindow().GetSize().y - GetMousePosition().y });
			}
			else
			{
				gameobjectmanager.ReturnLastInteraction()->SetPosition({ GetMousePosition().x, Engine::GetWindow().GetSize().y - GetMousePosition().y ,Engine::GetWindow().GetSize().y - GetMousePosition().y });
			}
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				object_place = 2;
			}
		}
		else if (object_place == 2)
		{
			if (adding_object)
			{
				gameobjectmanager.ReturnLastInteraction()->SetPosition({ gameobjectmanager.ReturnLastInteraction()->GetPosition().x, Engine::GetWindow().GetSize().y - GetMousePosition().y ,gameobjectmanager.ReturnLastInteraction()->GetPosition().z });
			}
			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				adding_object = false;
			}
			if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::U))//move change
			{
				if (cant_move)
				{
					cant_move = false;
					move_check = true;
				}
				else
				{
					cant_move = true;
					move_check = true;
				}
			}

			if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::E) && room >= max_room&&!adding_object)//press E to end checking
			{
				object_place = 0;
				//save
				SetNumber(editor_save_number);
				SetRoom(editor_save_number, room);
				SetType(editor_save_number, type);
				SetPosition(editor_save_number, { gameobjectmanager.ReturnLastInteraction()->GetPosition().x, gameobjectmanager.ReturnLastInteraction()->GetPosition().y, gameobjectmanager.ReturnLastInteraction()->GetPosition().z });
				if (cant_move)
				{
					SetInformation(editor_save_number, "cant");
				}
				else
				{
					SetInformation(editor_save_number, "move");
				}
				
				SetSize(editor_save_number, { 200, 200, 200 });
				editor_save_number++;
				FileOutputEditor("Assets/editor.txt");
			}
		}
		
		
	}
	
}

void Editor::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	gameobjectmanager.DrawAllEditor(Math::TransformationMatrix());
	DrawLine(Engine::GetWindow().GetSize().x / 2, 0, Engine::GetWindow().GetSize().x / 2, Engine::GetWindow().GetSize().y, WHITE);
}

void Editor::Unload() {
	gameobjectmanager.Unload();
	
}