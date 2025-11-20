#include "entities/Ball.h"

#include "audio/AudioManager.h"

namespace ball
{
	static const vec::Vector2 DEFAULT_POSITIONS = { 0.2f, 0.5f };
	static const vec::Vector2 DEFAULT_SIZE = { 0.025f, 0.025f };

	static const float GRAVITY = 2.25f;
	static const float JUMP_FORCE = 0.85f;

	void Init(Ball& ball)
	{
		Reset(ball);
	}

	void Update(Ball& ball)
	{
		if (!ball.isAlive || !ball.isActive)
		{
			return;
		}

		ball.velocity.y -= GRAVITY * rend::deltaTime;

		ball.position += ball.velocity * rend::deltaTime;

		if (ball.position.y + ball.size.y > 1.0f)
		{
			ball.position.y = 1.0f - ball.size.y;
			ball.velocity = 0.0f;
		}

		if (ball.position.y - ball.size.y < 0.0f)
		{
			audioManager::PlaySfx(audioManager::SfxID::SFX_HIT_PLAYER);

			ball.position.y = ball.size.y;
			Die(ball);
		}
	}

	void Draw(Ball& ball)
	{
		if (!ball.isActive)
		{
			return;
		}

		drw::Circle(ball.position, ball.size, ball.color);
	}

	void Reset(Ball& ball)
	{
		ball = Ball();

		ball.isActive = true;
		ball.isAlive = true;

		ball.position = DEFAULT_POSITIONS;
		ball.size = DEFAULT_SIZE;

		ball.score = 0;

		ball.color = FUSCHIA_B;
	}

	void Jump(Ball& ball)
	{
		if (!ball.isAlive || !ball.isActive)
		{
			return;
		}

		ball.velocity.y = JUMP_FORCE;
	}

	void Die(Ball& ball)
	{
		ball.isAlive = false;
		ball.velocity = 0.0f;
		ball.color = GREY_B;
	}
}