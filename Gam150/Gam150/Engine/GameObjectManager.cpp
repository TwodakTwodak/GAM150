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
}

void CS230::GameObjectManager::UpdateAll(double dt)
{
	ChangeAll();
	for (CS230::GameObject* object : collision_objects) {
		object->Update(dt);
	}
	CollisionPlayer();
}

void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (CS230::GameObject* object : draw_objects) {
		object->Draw(camera_matrix);
	}
}
void CS230::GameObjectManager::DrawAllEditor(Math::TransformationMatrix camera_matrix)
{
	for (CS230::GameObject* object : draw_objects) {
		object->DrawEditor(camera_matrix);
	}
}
void CS230::GameObjectManager::CollisionPlayer()
{
	for (int i = 0; i < collision_objects.size() - 1; ++i) {
		collision_objects[0]->Collision(collision_objects[i + 1]);
	}
}

void CS230::GameObjectManager::ChangeAll()
{
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::F)) {
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
CS230::GameObject* CS230::GameObjectManager::ReturnLastInteraction()
{
	return collision_objects[collision_objects.size() - 1];
}
CS230::GameObject* CS230::GameObjectManager::ReturnSelected(Math::vec3 location)
{
	int i = 0;
	for (CS230::GameObject* object : collision_objects) {
		if ((object->GetPosition().x<location.x && object->GetPosition().x + object->GetScale().x > location.x) &&
			(object->GetPosition().y<location.y && object->GetPosition().y + object->GetScale().y > location.y) &&
			(object->GetPosition().z<location.z && object->GetPosition().z + object->GetScale().z > location.z))
		{
			return collision_objects[i];
		}
		i++;
	}
	return nullptr;
}//make seperate collision latter
//check nullptr