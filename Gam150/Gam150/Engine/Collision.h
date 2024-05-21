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

namespace CS230 {
    class GameObject;
}

namespace Gam150 {
    class Collision : public CS230::Component {
    public:
        Collision(CS230::GameObject* clone);
        virtual bool CollisionDetect(CS230::GameObject* compare);
        double GetDistanceX(CS230::GameObject* compare);
        double GetDistanceY(CS230::GameObject* compare);
        double GetDistanceZ(CS230::GameObject* compare);
        Math::vec3 GetDistance(CS230::GameObject* compare);
        void CollisionDraw();
        double* bigger(double* com1, double* com2);
        Math::vec3 distance;
        virtual bool IsCollidingWith(CS230::GameObject* other_object) = 0;
    private:
        CS230::GameObject* gameobject;
    };

}

namespace CS230 {
    /*
    class Collision : public Component {
    public:
        enum class CollisionShape {
            Rect,
            Circle
        };
        virtual CollisionShape Shape() = 0;
        virtual bool IsCollidingWith(GameObject* other_object) = 0;
        virtual void Draw(Math::TransformationMatrix display_matrix) = 0;
    };*/
    class RectCollision : public Gam150::Collision {
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