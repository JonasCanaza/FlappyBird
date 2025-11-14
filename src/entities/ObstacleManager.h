#pragma once

#include "entities/Obstacle.h"
#include "entities/Ball.h"

namespace obstacle
{
	namespace manager
	{
		bool Collide(Obstacle& obstacle, ball::Ball& ball);
		bool Collide(Obstacle obstacles[], ball::Ball& ball);
	}
}