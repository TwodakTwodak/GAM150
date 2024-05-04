#include "GameObjectManager.h"

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

void CS230::GameObjectManager::ChangeAll(bool change_view)
{
	for (CS230::GameObject* object : objects) {
		object->SetView(main_view);
	}
	Reorder(main_view);
}

void CS230::GameObjectManager::Reorder(bool change_view)
{
	if (change_view) {
		std::sort(objects.begin(), objects.end(), &side_compare);
	}
	else {
		std::sort(objects.begin(), objects.end(), &top_compare);
	}
}

bool CS230::GameObjectManager::side_compare(GameObject* object1, GameObject* object2)
{
	if (object1->GetPosition().y > object2->GetPosition().y) {
		return true;
	}
	return false;
}

bool CS230::GameObjectManager::top_compare(GameObject* object1, GameObject* object2)
{
	if (object1->GetPosition().z > object2->GetPosition().z) {
		return true;
	}
	return false;
}
