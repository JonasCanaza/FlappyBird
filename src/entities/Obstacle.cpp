#include "entities/Obstacle.h"

namespace obstacle
{
    static const vec::Vector2 DEFAULT_POSITIONS = { 1.1f, 0.5f };
    static const vec::Vector2 DEFAULT_SPEED = { -0.5f, 0.0f };
    static const float DEFAULT_WIDTH = 0.15f;

    static const float DEFAULT_GAP_SIZE = 0.35f;
    static const float MIN_GAP_CENTER = 0.3f;
    static const float MAX_GAP_CENTER = 0.7f;

    enum ObstaclePartIndex
    {
        TOP_PART,
        BOTTOM_PART
    };

    void Init(FullObstacle& fullObstacle)
    {
        fullObstacle = FullObstacle();
        Reset(fullObstacle);
    }

    void Init(FullObstacle fullObstacles[])
    {
        for (int i = 0; i < maxFullObstacles; i++)
        {
            Init(fullObstacles[i]);
        }
    }

    void Update(FullObstacle& fullObstacle)
    {
        if (!fullObstacle.isActive)
        {
            return;
        }

        fullObstacle.position += fullObstacle.velocity * rend::deltaTime;

        if (fullObstacle.position.x + fullObstacle.width / 2.0f < 0.0f)
        {
            Reset(fullObstacle);
        }
    }

    void Update(FullObstacle fullObstacles[])
    {
        for (int i = 0; i < maxFullObstacles; i++)
        {
            Update(fullObstacles[i]);
        }
    }

    void Draw(FullObstacle& fullObstacle)
    {
        if (!fullObstacle.isActive)
        {
            return;
        }

        for (int i = 0; i < obstacleParts; i++)
        {
            ObstaclePart& part = fullObstacle.parts[i];

            vec::Vector2 partPos = { fullObstacle.position.x, fullObstacle.position.y + part.offsetY };
            vec::Vector2 partSize = { fullObstacle.width, part.height };

            drw::Rectangle(partPos, partSize, part.color);
        }
    }

    void Draw(FullObstacle fullObstacles[])
    {
        for (int i = 0; i < maxFullObstacles; i++)
        {
            Draw(fullObstacles[i]);
        }
    }

    void Reset(FullObstacle& fullObstacle)
    {
        fullObstacle = FullObstacle();

        fullObstacle.position = DEFAULT_POSITIONS;
        fullObstacle.velocity = DEFAULT_SPEED;
        fullObstacle.width = DEFAULT_WIDTH;
        fullObstacle.gapSize = DEFAULT_GAP_SIZE;

        float gapCenter = mth::GetRandomf(MIN_GAP_CENTER, MAX_GAP_CENTER);
        float halfGap = DEFAULT_GAP_SIZE / 2.0f;

        float topEnd = gapCenter - halfGap;
        float bottomStart = gapCenter + halfGap;

        fullObstacle.parts[TOP_PART].height = topEnd;
        fullObstacle.parts[TOP_PART].offsetY = -(1.0f - topEnd) / 2.0f;
        fullObstacle.parts[TOP_PART].color = RED_B;

        fullObstacle.parts[BOTTOM_PART].height = 1.0f - bottomStart;
        fullObstacle.parts[BOTTOM_PART].offsetY = (1.0f - fullObstacle.parts[BOTTOM_PART].height) / 2.0f;
        fullObstacle.parts[BOTTOM_PART].color = RED_B;

        fullObstacle.isActive = true;

        fullObstacle.scoredByPlayerOne = false;
        fullObstacle.scoredByPlayerTwo = false;
    }

    void Reset(FullObstacle fullObstacles[])
    {
        for (int i = 0; i < maxFullObstacles; i++)
        {
            Reset(fullObstacles[i]);
        }
    }
}
