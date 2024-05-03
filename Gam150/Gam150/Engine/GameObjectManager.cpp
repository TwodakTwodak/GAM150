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
