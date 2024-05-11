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
        double GetDistanceX(CS230::GameObject* compare);
        double GetDistanceY(CS230::GameObject* compare);
        double GetDistanceZ(CS230::GameObject* compare);
        Math::vec3 GetDistance(CS230::GameObject* compare);
        void CollisionDraw();
        double* bigger(double* com1, double* com2);
        Math::vec3 distance;
    private:
        CS230::GameObject* gameobject;
    };
}