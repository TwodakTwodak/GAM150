#include "GameObjectManager.h"
#include <iostream>

void CS230::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
}

void CS230::GameObjectManager::Unload()
{
	for (CS230::GameObject* object : objects) {
		delete object;
	}
	objects.clear();
}

void CS230::GameObjectManager::UpdateAll(double dt)
{
	for (CS230::GameObject* object : objects) {
		object->Update(dt);
	}
}

void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (CS230::GameObject* object : objects) {
		object->Draw(camera_matrix);
	}
}

void CS230::GameObjectManager::DrawAllEditor(Math::TransformationMatrix camera_matrix)
{
	for (CS230::GameObject* object : objects) {
		object->DrawEditor(camera_matrix);
	}
}

void CS230::GameObjectManager::CollisionAll()
{
	//for (int i = 0; i < objects.size() - 1; ++i) {
	//	if (Gam150::Collision::CollisionCheck( , )) {

	//	}
	//}
}

void CS230::GameObjectManager::ChangeAll()
{
	main_view = static_cast<View>(!static_cast<bool>(main_view));
	for (CS230::GameObject* object : objects) {
		object->SetView(main_view);
	}
	Reorder(main_view);
}

void CS230::GameObjectManager::Reorder(bool change_view)
{
	if (change_view) {
		std::sort(objects.begin(), objects.end(), &GameObjectManager::side_compare);
	}
	else {
		std::sort(objects.begin(), objects.end(), &GameObjectManager::top_compare);
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
	return objects[objects.size() - 1];
}

CS230::GameObject* CS230::GameObjectManager::ReturnSelected(Math::vec3 location)
{
	int i = 0;
	for (CS230::GameObject* object : objects) {
		if ((object->GetPosition().x<location.x && object->GetPosition().x + object->GetScale().x > location.x) &&
			(object->GetPosition().y<location.y && object->GetPosition().y + object->GetScale().y > location.y) &&
			(object->GetPosition().z<location.z && object->GetPosition().z + object->GetScale().z > location.z))
		{
			return objects[i];
		}
		i++;
	}
	return nullptr;
}//make seperate collision latter
//check nullptr

