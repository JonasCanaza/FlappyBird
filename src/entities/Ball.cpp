#include "entities/Ball.h"

#include "audio/AudioManager.h"

namespace ball
{
	static drw::SpriteData playerOneSprite;
	static drw::SpriteData playerTwoSprite;

	static const vec::Vector2 DEFAULT_POSITIONS = { 0.2f, 0.5f };
	static const vec::Vector2 DEFAULT_SIZE = { 0.025f, 0.025f };

	static const float GRAVITY = 2.25f;
	static const float JUMP_FORCE = 0.85f;

	void InitTextures()
	{
		playerOneSprite.size = { DEFAULT_SIZE.x * 2.0f, DEFAULT_SIZE.y * 2.0f };
		playerOneSprite.file = "res/sprites/player/PlayerRed.png";
		playerOneSprite.id = drw::InitSpriteData(playerOneSprite);

		playerTwoSprite.size = { DEFAULT_SIZE.x * 2.0f, DEFAULT_SIZE.y * 2.0f };
		playerTwoSprite.file = "res/sprites/player/PlayerGreen.png";
		playerTwoSprite.id = drw::InitSpriteData(playerTwoSprite);
	}

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

	void Draw(Ball& ball, Player number)
	{
		if (!ball.isActive)
		{
			return;
		}

		switch (number)
		{
		case ball::One:

			drw::Sprite(drw::spriteDataList[playerOneSprite.id], ball.position, playerOneSprite.size);

			break;
		case ball::Two:

			drw::Sprite(drw::spriteDataList[playerTwoSprite.id], ball.position, playerTwoSprite.size);

			break;
		default:

			// THERE ARE NO MORE PLAYERS

			break;
		}
	}

	void CloseTextures()
	{
		drw::DeInitSpriteData(playerOneSprite);
		drw::DeInitSpriteData(playerTwoSprite);
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