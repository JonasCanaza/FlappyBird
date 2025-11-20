#pragma once

#include "BorjaLib.h"

namespace obstacle
{
    const int obstacleParts = 2;
    const int maxFullObstacles = 1;

    struct ObstaclePart
    {
        float height = 0.0f;
        float offsetY = 0.0f;
        bColor color;
    };

    struct FullObstacle
    {
        bool isActive = false;

        vec::Vector2 position = {};
        vec::Vector2 velocity = {};

        float width = 0.0f;
        float gapSize = 0.0f;

        ObstaclePart parts[obstacleParts];
    };

    void Init(FullObstacle& fullObstacle);
    void Init(FullObstacle fullObstacles[]);

    void Update(FullObstacle& fullObstacle);
    void Update(FullObstacle fullObstacles[]);

    void Draw(FullObstacle& fullObstacle);
    void Draw(FullObstacle fullObstacles[]);

    void Reset(FullObstacle& fullObstacle);
    void Reset(FullObstacle fullObstacles[]);
}