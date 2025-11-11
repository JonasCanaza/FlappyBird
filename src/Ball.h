#pragma once

#include "BorjaLib.h"

namespace bll
{
	struct Ball
	{
		bool isActive = false;

		bool isAlive = false;

		vec::Vector2 pos = { 0.2f,0.5f };

		vec::Vector2 vel = { 0.0f,0.0f };

		float jumpForce = 0.75f;
		float moveForce = 0.5f;

		vec::Vector2 size = { 0.025f,0.025f };

		vec::Vector2 crashPoint = { 0.0f,0.0f };

		bColor color = MAROON_B;

		ctrl::ButtonMouse jumpButton = ctrl::ButtonMouse::LMB;

		ctrl::Key upKey = ctrl::Key::UP;
		ctrl::Key downKey = ctrl::Key::DOWN;
	};

	void Init(Ball& ball);

	void Reset(Ball& ball);

	void UpdateInput(Ball& ball);

	void Update(Ball& ball);

	void Draw(Ball& ball);

	void Die(Ball& ball);
}