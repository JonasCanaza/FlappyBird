#pragma once

#include "Obstacle.h"
#include "Ball.h"

namespace obstacle
{
	namespace manager
	{
		bool Collide(Obstacle& obstacle, ball::Ball& ball);
		bool Collide(Obstacle obstacles[], ball::Ball& ball);
	}
}