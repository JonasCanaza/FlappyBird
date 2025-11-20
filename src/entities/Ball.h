#pragma once

#include "BorjaLib.h"

namespace ball
{
	struct Ball
	{
		bool isActive = false;
		bool isAlive = false;

		vec::Vector2 position = {};
		vec::Vector2 velocity = {};
		vec::Vector2 size = {};
		vec::Vector2 crashPoint = {};

		bColor color;
	};

	void Init(Ball& ball);
	void Update(Ball& ball);
	void Draw(Ball& ball);

	void Reset(Ball& ball);
	void Jump(Ball& ball);
	void Die(Ball& ball);
}