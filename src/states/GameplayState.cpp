#include "states/GameplayState.h"

#include "BorjaLib.h"

#include "game/Game.h"
#include "entities/Ball.h"
#include "entities/ObstacleManager.h"

namespace gameplayState
{
	static ball::Ball ballOne;
	static ball::Ball ballTwo;
	static obstacle::FullObstacle obstacles[obstacle::maxObstacles];

	static btn::Button pauseButton;
	static btn::Button retryButton;
	static btn::Button returnButton;
	static btn::Button exitPauseButton;

	static bool isPaused;

	void Init()
	{
		ball::Init(ballOne);
		ball::Init(ballTwo);
		obstacle::Init(obstacles);

		btn::Button templateButton;
		templateButton.size = { 0.450f, 0.085f };
		templateButton.textData.fontSize = 0.075f;
		templateButton.useSprite = false;
		templateButton.activeColor = SEMITRANSPARENT_B;
		templateButton.mainColor = SEMITRANSPARENT_B;
		templateButton.hoveredColor = SEMITRANSPARENT_B;

		pauseButton = templateButton;
		pauseButton.pos = { 0.5f, 0.9f };
		pauseButton.textData.text = "Pause";
		btn::Init(pauseButton);

		retryButton = templateButton;
		retryButton.pos = { 0.5f, 0.7f };
		retryButton.textData.text = "Retry";
		btn::Init(retryButton);

		returnButton = templateButton;
		returnButton.pos = { 0.5f, 0.6f };
		returnButton.textData.text = "Return";
		btn::Init(returnButton);

		exitPauseButton = templateButton;
		exitPauseButton.pos = { 0.5f, 0.5f };
		exitPauseButton.textData.text = "Exit to Menu";
		btn::Init(exitPauseButton);
	}

	void Update()
	{
		if (isPaused)
		{
			btn::UpdateInput(retryButton);
			btn::UpdateInput(returnButton);
			btn::UpdateInput(exitPauseButton);

			if (retryButton.signal)
			{
				Reset();
			}

			if (returnButton.signal || ctrl::IsKeyPressed(ctrl::Key::ESCAPE))
			{
				isPaused = false;
			}

			if (exitPauseButton.signal)
			{
				isPaused = false;
				flappyBird::currentState = flappyBird::GameState::MAIN_MENU;
			}
		}
		else
		{
			btn::UpdateInput(pauseButton);

			if (pauseButton.signal || ctrl::IsKeyPressed(ctrl::Key::ESCAPE))
			{
				isPaused = true;
			}

			ball::UpdateInput(ballOne);
			ball::Update(ballOne);

			if (flappyBird::isMultiplayer)
			{
				ball::UpdateInput(ballTwo);
				ball::Update(ballTwo);
			}

			obstacle::Update(obstacles);

			for (int o = 0; o < obstacle::maxObstacles; o++)
			{
				if (obstacle::manager::Collide(obstacles[o].obstacles, ballOne))
				{
					ball::Die(ballOne);
				}

				if (flappyBird::isMultiplayer && obstacle::manager::Collide(obstacles[o].obstacles, ballTwo))
				{
					ball::Die(ballTwo);
				}
			}
		}
	}

	void Draw()
	{
		ball::Draw(ballOne);

		if (flappyBird::isMultiplayer)
		{
			ball::Draw(ballTwo);
		}

		obstacle::Draw(obstacles);

		btn::Draw(pauseButton);

		if (isPaused)
		{
			drw::Rectangle(vec::Vector4(0.0f, 0.0f, 1.0f, 1.0f), SEMITRANSPARENT_B);
			btn::Draw(retryButton);
			btn::Draw(returnButton);
			btn::Draw(exitPauseButton);
		}
	}

	void Reset()
	{
		isPaused = false;

		ball::Reset(ballOne);
		ball::Reset(ballTwo);
		obstacle::Reset(obstacles);
		
		ballOne.pos = { 0.25f, 0.5f };
		ballTwo.pos = { 0.15f, 0.5f };
		
		ballOne.color = RED_B;
		ballTwo.color = BLUE_B;
		
		ballOne.jumpKey = ctrl::Key::UP;
		ballTwo.jumpKey = ctrl::Key::W;
	}

	bool GetState()
	{
		return isPaused;
	}
}