/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Collision.cpp
Project:    Gam150 Engine
Author:     Huiuk Jang
Created:    May 4, 2024
*/

#include "Collision.h"

namespace Gam150 {
	bool Collision::CollisionCheck(Math::cube c1, Math::cube c2)
	{
		//check collision for x axis
		CollisionAxis({ c1.top_front.x, c1.bottom_behind.x }, { c2.top_front.x, c2.bottom_behind.x });
		//check collision for y axis
		CollisionAxis({ c1.top_front.y, c1.bottom_behind.y }, { c2.top_front.y, c2.bottom_behind.y });
		//check collision for z axis
		CollisionAxis({ c1.top_front.z, c1.bottom_behind.z }, { c2.top_front.z, c2.bottom_behind.z });


		if (collision_cube.Size().x != 0 && collision_cube.Size().y != 0 && collision_cube.Size().z != 0) {
			return true;
		}
		else {
			return false;
		}
	}

	void Collision::CollisionAxis(Math::vec2 a, Math::vec2 b)
	{
		//c1.top_front.? = a.x
		//c1.bottom_behind.? = a.y
		//c2.top_front.? = b.x
		//c2.bottom_behind.? = b.y
		if ((a.x - b.y) > 0) {
			collision_cube.top_front.x = a.x;
			collision_cube.bottom_behind.x = b.y;
		}
		else if ((b.x - a.y) > 0) {
			collision_cube.top_front.x = b.x;
			collision_cube.bottom_behind.x = a.y;
		}
		else {
			collision_cube.bottom_behind.x = 0;
			collision_cube.top_front.x = 0;
		}
	}

	Math::vec3 Collision::GetDistance()
	{
		return collision_cube.Size();
	}
}