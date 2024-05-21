/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    


Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include <vector>
#include "GameObject.h"

namespace Math { class TransformationMatrix; }

namespace Gam150 {
    class GameObjectManager {
    public:
        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void DrawAll(Math::TransformationMatrix camera_matrix);
        void CollisionPlayer();
        void CollisionBox();

        void ChangeAll();
        void Reorder(bool change_view);
        static bool side_compare(GameObject* object1, GameObject* object2);
        static bool top_compare(GameObject* object1, GameObject* object2);
        bool new_object = false;

        View main_view = View::Side;

        Math::ivec2 box_length;
        Math::ivec2 button_length;
        Math::ivec2 floor_length;

        //should move later!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::vector<GameObject*> collision_objects;


    private:
        std::vector<GameObject*> draw_objects;
    };
}
