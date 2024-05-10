/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Collision.cpp
Project:    Gam150 Engine
Author:     Huiuk Jang
Created:    May 4, 2024
*/

#include "Engine.h"
#include "Collision.h"
#include "GameObject.h"

namespace Gam150 {
	Collision::Collision(CS230::GameObject* clone) : gameobject(clone) { }

	bool Collision::CollisionDetect(CS230::GameObject* compare)
	{
		if (((gameobject->collision_cube.bottom_behind.x <= compare->collision_cube.top_front.x) && (gameobject->collision_cube.top_front.x >= compare->collision_cube.bottom_behind.x))
			&& (gameobject->collision_cube.bottom_behind.y <= compare->collision_cube.top_front.y) && (gameobject->collision_cube.top_front.y >= compare->collision_cube.bottom_behind.y)
			&& (gameobject->collision_cube.bottom_behind.z <= compare->collision_cube.top_front.z) && (gameobject->collision_cube.top_front.z >= compare->collision_cube.bottom_behind.z)
			) {
			return true;
		}
		return false;
	}

    double Collision::GetDistanceX(CS230::GameObject* compare)
    {
		if (CollisionDetect(compare))
		{
			if (gameobject->collision_cube.top_front.x < compare->collision_cube.top_front.x)
			{
				return (compare->collision_cube.bottom_behind.x - gameobject->collision_cube.top_front.x);
			}
			else
			{
				return -(gameobject->collision_cube.bottom_behind.x - compare->collision_cube.top_front.x);
			}
		}
		else
		{
			return NULL;
		}
	}

	double Collision::GetDistanceY(CS230::GameObject* compare)
	{
		if (CollisionDetect(compare))
		{
			if (gameobject->collision_cube.top_front.y < compare->collision_cube.top_front.y)
			{
				return -(gameobject->collision_cube.top_front.y - compare->collision_cube.bottom_behind.y);
			}
			else
			{
				return (compare->collision_cube.top_front.y - gameobject->collision_cube.bottom_behind.y);
			}
		}
		else
		{
			return NULL;
		}
	}

	double Collision::GetDistanceZ(CS230::GameObject* compare)
	{
		if (CollisionDetect(compare))
		{
			if (gameobject->collision_cube.top_front.z < compare->collision_cube.top_front.z)
			{
				return -(gameobject->collision_cube.top_front.z - compare->collision_cube.bottom_behind.z);
			}
			else
			{
				return (compare->collision_cube.top_front.z - gameobject->collision_cube.bottom_behind.z);
			}
		}
		else
		{
			return NULL;
		}
	}

	void Collision::CollisionDraw()
	{
        int width, height;
        if (gameobject->GetView()) {
            width = std::abs(gameobject->collision_cube.top_front.x - gameobject->collision_cube.bottom_behind.x);
            height = std::abs(gameobject->collision_cube.top_front.y - gameobject->collision_cube.bottom_behind.y);
            DrawRectangleLines(
                gameobject->collision_cube.bottom_behind.x,
                Engine::GetWindow().GetSize().y - gameobject->collision_cube.bottom_behind.y - height,
                width,
                height,
                WHITE);
        }
        else {
            width = std::abs(gameobject->collision_cube.top_front.x - gameobject->collision_cube.bottom_behind.x);
            height = std::abs(gameobject->collision_cube.top_front.z - gameobject->collision_cube.bottom_behind.z);
            DrawRectangleLines(
                gameobject->collision_cube.bottom_behind.x,
                Engine::GetWindow().GetSize().y - gameobject->collision_cube.bottom_behind.z - height,
                width,
                height,
                WHITE);
        }
	}

}