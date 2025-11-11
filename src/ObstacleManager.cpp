#include "ObstacleManager.h"

namespace obstacle
{
	namespace manager
	{
		bool Collide(Obstacle& obstacle, ball::Ball& ball)
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

		bool Collide(Obstacle obstacles[], ball::Ball& ball)
		{
			if (!ball.isAlive)
			{
				return false;
			}

			for (int o = 0; o < obstacle::obstaclesAmount; o++)
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