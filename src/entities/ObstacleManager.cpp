#include "entities/ObstacleManager.h"

namespace obstacle
{
    namespace manager
    {
        bool Collide(FullObstacle fullObstacle, ObstaclePart part, ball::Ball ball)
        {
            if (!fullObstacle.isActive)
            {
                return false;
            }

            vec::Vector2 rectPos = { fullObstacle.position.x, fullObstacle.position.y + part.offsetY };
            vec::Vector2 rectSize = { fullObstacle.width, part.height };

            return coll::RecOnRec(rectPos, rectSize, ball.pos, ball.size, ball.crashPoint);
        }

        bool Collide(FullObstacle fullObstacle, ball::Ball ball)
        {
            if (!ball.isAlive)
            {
                return false;
            }

            for (int i = 0; i < obstacleParts; i++)
            {
                if (Collide(fullObstacle, fullObstacle.parts[i], ball))
                {
                    return true;
                }
            }

            return false;
        }
    }
}