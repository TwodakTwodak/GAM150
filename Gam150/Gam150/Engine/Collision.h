/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Collision.h
Project:    Gam150 Engine
Author:     Huiuk Jang
Created:    May 4, 2024
*/

#pragma once

#include "Engine.h"
#include "Cube.h"

namespace CS230 { class GameObject; }

namespace Gam150 {
    class Collision {
    public:
        Collision(CS230::GameObject* clone);
        bool CollisionDetect(CS230::GameObject* compare);
        void CollisionDraw();
    private:
        Math::vec3 distance;
        CS230::GameObject* gameobject;
    };
}