#include "GameObjectManager.h"

void CS230::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
	new_object = true;
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
	ChangeAll();
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

void CS230::GameObjectManager::CollisionAll()
{
	for (int i = 0; i < objects.size() - 1; ++i) {
		objects[0]->Collision(objects[i + 1]);
	}
}

void CS230::GameObjectManager::ChangeAll()
{
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::F)) {
		main_view = static_cast<View>(!static_cast<bool>(main_view));
		for (CS230::GameObject* object : objects) {
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
