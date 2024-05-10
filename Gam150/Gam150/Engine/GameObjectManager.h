/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include <vector>
#include "GameObject.h"

namespace Math { class TransformationMatrix; }

namespace CS230 {
    class GameObjectManager {
    public:
        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void DrawAll(Math::TransformationMatrix camera_matrix);
        void CollisionAll();

        void ChangeAll();
        void Reorder(bool change_view);
        static bool side_compare(GameObject* object1, GameObject* object2);
        static bool top_compare(GameObject* object1, GameObject* object2);
        bool new_object = false;

        View main_view = View::Side;
    private:
        std::vector<GameObject*> collision_objects;
        std::vector<GameObject*> draw_objects;
    };
}
