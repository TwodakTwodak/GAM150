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

	bool Collision::CollisionDetect(Gam150::GameObject* compare)
	{
		if (((gameobject->collision_cube.bottom_behind.x <= compare->collision_cube.top_front.x) && (gameobject->collision_cube.top_front.x >= compare->collision_cube.bottom_behind.x))
			&& (gameobject->collision_cube.bottom_behind.y <= compare->collision_cube.top_front.y) && (gameobject->collision_cube.top_front.y >= compare->collision_cube.bottom_behind.y)
			&& (gameobject->collision_cube.bottom_behind.z <= compare->collision_cube.top_front.z) && (gameobject->collision_cube.top_front.z >= compare->collision_cube.bottom_behind.z)
			) {
			return true;
		}
		return false;
	}

	double Collision::GetDistanceX(Gam150::GameObject* compare)
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

	double Collision::GetDistanceY(Gam150::GameObject* compare)
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

	double Collision::GetDistanceZ(Gam150::GameObject* compare)
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

	Math::vec3 Collision::GetDistance(Gam150::GameObject* compare)
	{
		distance.x = GetDistanceX(compare);
		distance.y = GetDistanceY(compare);
		distance.z = GetDistanceZ(compare);
		bigger(bigger(&distance.x, &distance.y), &distance.z);
		return distance;
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

	double* Collision::bigger(double* com1, double* com2) {
		if (std::abs(*com1) < std::abs(*com2)) {
			*com2 = 0;
			return com1;
		}
		else {
			*com1 = 0;
			return com2;
		}
	}

	RectCollision::RectCollision(Math::irect boundary, GameObject* object) :
		boundary(boundary),
		object(object){}

	Math::rect Gam150::RectCollision::WorldBoundary() {
		return {
			object->GetMatrix() * static_cast<Math::vec2>(boundary.point_1),
			object->GetMatrix() * static_cast<Math::vec2>(boundary.point_2)
		};
	}
	void Gam150::RectCollision::Draw(Math::TransformationMatrix display_matrix) {
		const double render_height = rlGetFramebufferHeight();

		Math::rect world_boundary = WorldBoundary();

		Math::vec2 bottom_left = display_matrix * Math::vec2{ world_boundary.Left(), world_boundary.Bottom() };
		Math::vec2 bottom_right = display_matrix * Math::vec2{ world_boundary.Right(), world_boundary.Bottom() };
		Math::vec2 top_left = display_matrix * Math::vec2{ world_boundary.Left(), world_boundary.Top() };
		Math::vec2 top_right = display_matrix * Math::vec2{ world_boundary.Right(), world_boundary.Top() };

		bottom_left.y = bottom_left.y * -1 + render_height;
		bottom_right.y = bottom_right.y * -1 + render_height;
		top_left.y = top_left.y * -1 + render_height;
		top_right.y = top_right.y * -1 + render_height;

		DrawLine(int(top_left.x), int(top_left.y), int(top_right.x), int(top_right.y), WHITE);
		DrawLine(int(bottom_right.x), int(bottom_right.y), int(top_right.x), int(top_right.y), WHITE);
		DrawLine(int(bottom_right.x), int(bottom_right.y), int(bottom_left.x), int(bottom_left.y), WHITE);
		DrawLine(int(top_left.x), int(top_left.y), int(bottom_left.x), int(bottom_left.y), WHITE);
	}

	bool Gam150::RectCollision::IsCollidingWith(GameObject* other_object) {
		Gam150::Collision* other_collider = other_object->GetGOComponent<Gam150::Collision>();


		if (other_collider == nullptr) {
			Engine::GetLogger().LogError("No collision component found");
			return false;
		}


		Math::rect rectangle_1 = WorldBoundary();
		Math::rect rectangle_2 = dynamic_cast<RectCollision*>(other_collider)->WorldBoundary();

		if (!(rectangle_1.Right() < rectangle_2.Left() || rectangle_1.Left() > rectangle_2.Right() || rectangle_1.Top() < rectangle_2.Bottom() || rectangle_1.Bottom() > rectangle_2.Top())) {
			return true;
		}
		return false;
	}
}