#pragma once

#include "BorjaLib.h"

namespace ball
{
	enum Player
	{
		One,
		Two
	};

	struct Ball
	{
		bool isActive = false;
		bool isAlive = false;

		vec::Vector2 position = {};
		vec::Vector2 velocity = {};
		vec::Vector2 size = {};
		vec::Vector2 crashPoint = {};

		int score = 0;

		bColor color;
	};

	void InitTextures();
	void Init(Ball& ball);
	void Update(Ball& ball);
	void Draw(Ball& ball, Player number);
	void CloseTextures();

	void Reset(Ball& ball);
	void Jump(Ball& ball);
	void Die(Ball& ball);
}