#pragma once

#include "BorjaLib.h"

namespace obstacle
{
	const int obstaclesAmount = 2;
	const int maxObstacles = 1;

	struct Obstacle
	{
		bool isActive = false;

		vec::Vector2 pos = { 0.0f,1.25f };

		vec::Vector2 vel = { 0.0f,0.0f };

		vec::Vector2 size = { 0.05f,0.25f };

		bColor color = DARKGREEN_B;
	};

	struct FullObstacle
	{
		bool isActive = false;

		vec::Vector2 pos = { 1.25f,0.5f };

		vec::Vector2 vel = { -0.75f,0.0f };

		vec::Vector2 size = { 0.05f,1.0f };

		Obstacle obstacles[obstaclesAmount] = {};
	};

	void Init(Obstacle& obstacle);
	void Init(Obstacle obstacles[]);

	void Init(FullObstacle& fullObstacle);
	void Init(FullObstacle fullObstacles[]);

	void Reset(Obstacle& obstacle);
	void Reset(Obstacle obstacles[]);

	void Reset(FullObstacle& fullObstacle);
	void Reset(FullObstacle fullObstacles[]);

	void Update(Obstacle& obstacle);
	void Update(Obstacle obstacles[]);

	void Update(FullObstacle& fullObstacle);
	void Update(FullObstacle fullObstacles[]);
	
	void Draw(Obstacle& obstacle);
	void Draw(Obstacle obstacles[]);
	
	void Draw(FullObstacle fullObstacle);
	void Draw(FullObstacle fullObstacles[]);
}