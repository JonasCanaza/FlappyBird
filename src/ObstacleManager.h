#pragma once

#include "Obstacle.h"
#include "Ball.h"

namespace obstcl
{
	namespace mngr
	{
		bool Collide(Obstacle& obstacle, bll::Ball& ball);
		bool Collide(Obstacle obstacles[], bll::Ball& ball);
	}
}