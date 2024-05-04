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

namespace Gam150 {
	class Collision {
	public:
		bool CollisionCheck(Math::cube c1, Math::cube c2);
		//seems unefficent
		void CollisionAxis(Math::vec2 a, Math::vec2 b);
		Math::vec3 GetDistance();
	private:
		Math::cube collision_cube;
	};
}