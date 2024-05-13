#include "GameObjectManager.h"

void CS230::GameObjectManager::Add(GameObject* object)
{
	collision_objects.push_back(object);
	draw_objects.push_back(object);
	new_object = true;
}

void CS230::GameObjectManager::Unload()
{
	for (CS230::GameObject* object : collision_objects) {
		delete object;
	}
	collision_objects.clear();
	draw_objects.clear();
	box_length = { 0,0 };
	button_length = { 0,0 };
	floor_length = { 0,0 };
}

void CS230::GameObjectManager::UpdateAll(double dt)
{
	ChangeAll();
	for (CS230::GameObject* object : collision_objects) {
		object->Update(dt);
	}
	CollisionBox();
	CollisionPlayer();
}

void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (CS230::GameObject* object : draw_objects) {
		object->Draw(camera_matrix);
	}
}

void CS230::GameObjectManager::CollisionPlayer()
{
	for (int i = box_length.x; i < box_length.y; ++i) {
		collision_objects[0]->Collision(collision_objects[i], collision_objects[i]->GetType());
	}
	for (int i = floor_length.x - 1; i < collision_objects.size(); ++i) {
		collision_objects[0]->Collision(collision_objects[i], collision_objects[i]->GetType());
	}
}

void CS230::GameObjectManager::CollisionBox()
{
	for (int i = 1; i < box_length.y; ++i) {
		for (int j = button_length.x - 2; j < collision_objects.size(); ++j) {
			collision_objects[i]->Collision(collision_objects[j], collision_objects[j]->GetType());
		}
	}
}

void CS230::GameObjectManager::ChangeAll()
{
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Space)) {
		main_view = static_cast<View>(!static_cast<bool>(main_view));
		for (CS230::GameObject* object : draw_objects) {
			object->SetView(main_view);
		}
		Reorder(main_view);
	}

	if (new_object) {
		Reorder(main_view);
		new_object = false;
	}
}

void CS230::GameObjectManager::Reorder(bool change_view)
{
	if (change_view) {
		std::sort(draw_objects.begin(), draw_objects.end(), &GameObjectManager::side_compare);
	}
	else {
		std::sort(draw_objects.begin(), draw_objects.end(), &GameObjectManager::top_compare);
	}
}
//need fix!
bool CS230::GameObjectManager::side_compare(GameObject* object1, GameObject* object2)
{
	if (object1->GetPosition().z > object2->GetPosition().z) {
		return true;
	}
	return false;
}

bool CS230::GameObjectManager::top_compare(GameObject* object1, GameObject* object2)
{
	if (object1->GetPosition().y < object2->GetPosition().y) {
		return true;
	}
	return false;
}
