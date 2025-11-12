#include "Obstacle.h"

namespace obstacle
{
	void Init(Obstacle& obstacle)
	{
		obstacle = Obstacle();
		Reset(obstacle);
	}

	void Init(Obstacle obstacles[])
	{
		for (int o = 0; o < obstaclesAmount; o++)
		{
			Init(obstacles[o]);
		}
	}

	void Init(FullObstacle& fullObstacle)
	{
		fullObstacle = FullObstacle();
		Reset(fullObstacle);
	}

	void Init(FullObstacle fullObstacles[])
	{
		for (int o = 0; o < maxObstacles; o++)
		{
			Init(fullObstacles[o]);
		}
	}

	void Reset(Obstacle& obstacle)
	{
		obstacle = Obstacle();
		obstacle.pos.x = 1.0f + (obstacle.size.x / 2.0f);
		obstacle.pos.y = mth::GetRandomf((obstacle.size.y / 2.0f), 1.0f - (obstacle.size.y / 2.0f));
		obstacle.isActive = true;
	}

	void Reset(Obstacle obstacles[])
	{
		for (int o = 0; o < obstaclesAmount; o++)
		{
			Reset(obstacles[o]);
		}
	}

	void Reset(FullObstacle& fullObstacle)
	{
		fullObstacle = FullObstacle();
		fullObstacle.pos.x = 1.0f + (fullObstacle.size.x / 2.0f);
		fullObstacle.pos.y = 0.5f;
		fullObstacle.isActive = true;

		for (int o = 0; o < obstaclesAmount; o++)
		{
			Reset(fullObstacle.obstacles[o]);
		}

		//temp solution

		vec::Vector2 playerSpacePos = { 0.0f, 0.0f };
		vec::Vector2 playerSpaceSize = { 0.0f, 0.0f };

		playerSpacePos.y = mth::GetRandomf(0.3f,0.7f);
		playerSpaceSize.y = 0.35f;

		fullObstacle.obstacles[0].pos.y = (playerSpacePos.y - playerSpaceSize.y / 2.0f) / 2.0f;
		fullObstacle.obstacles[0].size.y = 2.0f * fullObstacle.obstacles[0].pos.y;
		fullObstacle.obstacles[0].color = RED_B;

		fullObstacle.obstacles[1].pos.y = (playerSpacePos.y + playerSpaceSize.y / 2.0f) + (1.0f - (playerSpacePos.y + playerSpaceSize.y / 2.0f))/2.0f;
		fullObstacle.obstacles[1].size.y = 2.0f * (1.0f - fullObstacle.obstacles[1].pos.y);

		fullObstacle.obstacles[2].pos.y = playerSpacePos.y;
		fullObstacle.obstacles[2].size.y = playerSpaceSize.y;
		fullObstacle.obstacles[2].color = BLUE_B;
	}

	void Reset(FullObstacle fullObstacles[])
	{
		for (int o = 0; o < maxObstacles; o++)
		{
			Reset(fullObstacles[o]);
		}
	}

	void Update(Obstacle& obstacle)
	{
		if (!obstacle.isActive)
		{
			return;
		}

		obstacle.pos += obstacle.vel * rend::deltaTime;

		if (obstacle.pos.x + (obstacle.size.x / 2.0f) < 0.0f)
		{
			Reset(obstacle);
		}
	}

	void Update(Obstacle obstacles[])
	{
		for (int o = 0; o < obstaclesAmount; o++)
		{
			Update(obstacles[o]);
		}
	}

	void Update(FullObstacle& fullObstacle)
	{
		if (!fullObstacle.isActive)
		{
			return;
		}

		fullObstacle.pos += fullObstacle.vel * rend::deltaTime;

		for (int o = 0; o < obstaclesAmount; o++)
		{
			fullObstacle.obstacles[o].pos += fullObstacle.vel * rend::deltaTime;
			Update(fullObstacle.obstacles[o]);
		}

		if (fullObstacle.pos.x + (fullObstacle.size.x / 2.0f) < 0.0f)
		{
			Reset(fullObstacle);
		}
	}

	void Update(FullObstacle fullObstacles[])
	{
		for (int o = 0; o < maxObstacles; o++)
		{
			Update(fullObstacles[o]);
		}
	}

	void Draw(Obstacle& obstacle)
	{
		if (!obstacle.isActive)
		{
			return;
		}

		drw::Rectangle(obstacle.pos, obstacle.size, obstacle.color);
	}

	void Draw(Obstacle obstacles[])
	{
		for (int o = 0; o < obstaclesAmount; o++)
		{
			Draw(obstacles[o]);
		}
	}

	void Draw(FullObstacle fullObstacle)
	{
		Draw(fullObstacle.obstacles);
	}

	void Draw(FullObstacle fullObstacles[])
	{
		for (int o = 0; o < maxObstacles; o++)
		{
			Draw(fullObstacles[o]);
		}
	}
}
