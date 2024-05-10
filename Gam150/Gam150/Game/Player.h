/*
File Name:  Player.h
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/
#pragma once

#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/GameObject.h"

class Player : public CS230::GameObject {
public:
	Player(Math::vec3 start_position);
	void Update(double dt) override;
	const Math::vec3& GetPosition() const { return GameObject::GetPosition(); };

private:
	static constexpr double xz_acceleration = 300;
	static constexpr double xz_drag = 450;
	static constexpr double max_velocity = 200;
	static constexpr double jump_velocity = 650;
	bool jump_able = false;

	void move(double dt);
	void jump(double dt);
	void dash(double dt);
};