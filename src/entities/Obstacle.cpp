#include "entities/Obstacle.h"

namespace obstacle
{
    static drw::SpriteData obstacleSprite;

    static const vec::Vector2 DEFAULT_POSITIONS = { 1.1f, 0.5f };
    static const vec::Vector2 DEFAULT_SPEED = { -0.5f, 0.0f };
    static const float DEFAULT_WIDTH = 0.15f;

    static const float DEFAULT_GAP_SIZE = 0.35f;
    static const float MIN_GAP_CENTER = 0.3f;
    static const float MAX_GAP_CENTER = 0.7f;
    static const float OBSTACLE_GAP = 0.6f;

    enum ObstaclePartIndex
    {
        TOP_PART,
        BOTTOM_PART
    };

    void InitTextures()
    {
        obstacleSprite.file = "res/sprites/obstacle/Obstacle.png";
        obstacleSprite.id = drw::InitSpriteData(obstacleSprite);
    }

    void Init(FullObstacle& fullObstacle)
    {
        fullObstacle.position = DEFAULT_POSITIONS;
        fullObstacle.velocity = DEFAULT_SPEED;
        fullObstacle.width = DEFAULT_WIDTH;
        fullObstacle.gapSize = DEFAULT_GAP_SIZE;

        Reset(fullObstacle);
    }

    void Init(FullObstacle fullObstacles[])
    {
        for (int i = 0; i < maxFullObstacles; i++)
        {
            Init(fullObstacles[i]);

            fullObstacles[i].position.x = DEFAULT_POSITIONS.x + (static_cast<float>(i) * OBSTACLE_GAP);
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
            fullObstacle.position.x = DEFAULT_POSITIONS.x;

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

            drw::Sprite(drw::spriteDataList[obstacleSprite.id], partPos, partSize);
        }
    }

    void Draw(FullObstacle fullObstacles[])
    {
        for (int i = 0; i < maxFullObstacles; i++)
        {
            Draw(fullObstacles[i]);
        }
    }

    void CloseTextures()
    {
        drw::DeInitSpriteData(obstacleSprite);
    }

    void Reset(FullObstacle& fullObstacle)
    {
        fullObstacle.position.y = DEFAULT_POSITIONS.y;
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

            fullObstacles[i].position.x = DEFAULT_POSITIONS.x + (static_cast<float>(i) * OBSTACLE_GAP);
        }
    }
}
