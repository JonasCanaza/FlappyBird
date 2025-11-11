#include "ObstacleManager.h"

namespace obstcl
{
	namespace mngr
	{
		bool Collide(Obstacle& obstacle, bll::Ball& ball)
		{
			if (!obstacle.isActive)
			{
				return false;
			}

			if (coll::RecOnRec(obstacle.pos, obstacle.size, ball.pos, ball.size, ball.crashPoint))
			{
				return true;
			}

			return false;
		}

		bool Collide(Obstacle obstacles[], bll::Ball& ball)
		{
			if (!ball.isAlive)
			{
				return false;
			}

			for (int o = 0; o < obstcl::obstaclesAmount; o++)
			{
				if (Collide(obstacles[o], ball))
				{
					return true;
				}
			}

			return false;
		}
	}
}