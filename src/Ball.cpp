#include "BorjaLib.h"

#include "Ball.h"

//TEMPORALMENTE AQUI
static const float gravity = 1.8f;

namespace ball
{
	void Init(Ball& ball)
	{
		ball = Ball();
		Reset(ball);
	}

	void Reset(Ball& ball)
	{
		ball = Ball();
		ball.isActive = true;
		ball.isAlive = true;
	}

	void UpdateInput(Ball& ball)
	{
		if (!ball.isAlive || !ball.isActive)
		{
			return;
		}

		if (ctrl::IsKeyPressed(ball.jumpKey))
		{
			ball.vel.y = ball.jumpForce;
		}
	}

	void Update(Ball& ball)
	{
		if (!ball.isAlive || !ball.isActive)
		{
			return;
		}

		ball.vel.y -= gravity * rend::deltaTime;

		ball.pos += ball.vel * rend::deltaTime;

		if (ball.pos.y + ball.size.y > 1.0f)
		{
			ball.pos.y = 1.0f - ball.size.y;
			ball.vel = 0.0f;
		}

		if (ball.pos.y - ball.size.y < 0.0f)
		{
			ball.pos.y = ball.size.y;
			Die(ball);
		}
	}

	void Draw(Ball& ball)
	{
		if (!ball.isActive)
		{
			return;
		}

		drw::Circle(ball.pos, ball.size, ball.color);

		if (!ball.isAlive)
		{
			drw::Circle(ball.crashPoint, ball.size * (1.0f/3.0f), MAGENTA_B);
		}
	}

	void Die(Ball& ball)
	{
		ball.isAlive = false;
		ball.vel = 0.0f;
		ball.color = GREY_B;
	}
}