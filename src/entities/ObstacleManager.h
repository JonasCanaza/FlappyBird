#pragma once

#include "entities/Obstacle.h"
#include "entities/Ball.h"

namespace obstacle
{
    namespace manager
    {
        bool Collide(FullObstacle fullObstacle, ObstaclePart part, ball::Ball ball);
        bool Collide(FullObstacle fullObstacle, ball::Ball ball);
    }
}