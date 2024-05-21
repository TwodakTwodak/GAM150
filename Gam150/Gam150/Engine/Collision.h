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
#include "ComponentManager.h"
namespace Math {
    class TransformationMatrix;
}

namespace Gam150 {
    class GameObject;
    class Collision : public Component {
    public:
        virtual bool CollisionDetect(Gam150::GameObject* compare);
        double GetDistanceX(Gam150::GameObject* compare);
        double GetDistanceY(Gam150::GameObject* compare);
        double GetDistanceZ(Gam150::GameObject* compare);
        Math::vec3 GetDistance(Gam150::GameObject* compare);
        void CollisionDraw();
        double* bigger(double* com1, double* com2);
        Math::vec3 distance;
        virtual bool IsCollidingWith(Gam150::GameObject* other_object) = 0;
        virtual void Draw(Math::TransformationMatrix display_matrix) = 0;
    private:
        GameObject* gameobject;
    };

    class RectCollision : public Collision {
    public:
        RectCollision(Math::irect boundary, GameObject* object);
        bool IsCollidingWith(GameObject* other_object) override;
        void Draw(Math::TransformationMatrix display_matrix);
        Math::rect WorldBoundary();
    private:
        GameObject* object;
        Math::irect boundary;
    };

}