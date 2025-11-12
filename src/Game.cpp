#include "Game.h"

#include "BorjaLib.h"

#include "Ball.h"
#include "ObstacleManager.h"
#include "BackgroundManager.h"

namespace flappyBird
{
	static bool isMultiplayer;

	void Play()
	{
		bool isPaused = false;
		isMultiplayer = false;

		ctrl::Key pauseKey = ctrl::Key::ESCAPE;

		enum class GameState
		{
			MAIN_MENU,
			GAMEPLAY,
			CREDITS
		};

		bool isRunning = true;
		bLib::Init("Flappy Bird");
		GameState currentState = GameState::MAIN_MENU;

		float gameTimer = 0.0f;

		//Menu
		btn::Button singlePlayer;
		btn::Button twoPlayers;
		btn::Button creditsButton;
		btn::Button exitButton;

		// Credits
		btn::Button backButton;
		drw::TextData creditsTextData;

		// Gameplay
		btn::Button pauseButton;
		drw::TextData scoreTextData;

		ball::Ball ball;
		ball::Init(ball);

		obstacle::FullObstacle obstacles[obstacle::maxObstacles];
		obstacle::Init(obstacles);

		// Pause
		btn::Button retryButton;
		btn::Button returnButton;
		btn::Button exitPauseButton;

		//Version Overlay
		drw::TextData versionTextData;

		// Inicializacion

		btn::Button templateButton;
		templateButton.size = { 0.450f, 0.085f };
		templateButton.textData.fontSize = 0.075f;
		templateButton.useSprite = false;
		templateButton.activeColor = SEMITRANSPARENT_B;
		templateButton.mainColor = SEMITRANSPARENT_B;
		templateButton.hoveredColor = SEMITRANSPARENT_B;


		//Menu
		singlePlayer = templateButton;
		singlePlayer.pos = { 0.5f, 0.5f };
		singlePlayer.textData.text = "Single Player";
		btn::Init(singlePlayer);

		twoPlayers = templateButton;
		twoPlayers.pos = { 0.5f, 0.4f };
		twoPlayers.textData.text = "Two Players";
		btn::Init(twoPlayers);

		creditsButton = templateButton;
		creditsButton.pos = { 0.5f, 0.3f };
		creditsButton.textData.text = "Credits";
		btn::Init(creditsButton);

		exitButton = templateButton;
		exitButton.pos = { 0.5f, 0.2f };
		exitButton.textData.text = "Exit";
		btn::Init(exitButton);

		//Credits
		backButton = templateButton;
		backButton.pos = { 0.5f, 0.3f };
		backButton.textData.text = "Back";
		btn::Init(backButton);

		creditsTextData.fontSize = 0.05f;
		creditsTextData.text = "Made by Borja Lia and Jonas Canaza";

		//Gameplay
		pauseButton = templateButton;
		pauseButton.pos = { 0.5f, 0.9f };
		pauseButton.textData.text = "Pause";
		btn::Init(pauseButton);

		scoreTextData.fontSize = 0.1f;

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

		versionTextData.fontSize = 0.05f;
		versionTextData.text = "v0.3";
		versionTextData.color = SEMITRANSPARENT_B;

		// Background

		backgroundManager::Init();

		while (isRunning)
		{
			isRunning = !rend::ShouldExit();

			//Update
			bLib::UpdateStart();

			switch (currentState)
			{
			case GameState::MAIN_MENU:

				btn::UpdateInput(singlePlayer);
				btn::UpdateInput(twoPlayers);
				btn::UpdateInput(creditsButton);
				btn::UpdateInput(exitButton);

				if (singlePlayer.signal || twoPlayers.signal)
				{
					if (singlePlayer.signal)
					{
						isMultiplayer = false;
					}
					else
					{
						isMultiplayer = true;
					}

					currentState = GameState::GAMEPLAY;
					isPaused = false;
					gameTimer = 0.0f;
					ball::Reset(ball);
					obstacle::Reset(obstacles);
				}

				if (creditsButton.signal)
				{
					currentState = GameState::CREDITS;
				}

				if (exitButton.signal)
				{
					isRunning = false;
				}

				break;
			case GameState::GAMEPLAY:

				if (isPaused)
				{
					btn::UpdateInput(retryButton);
					btn::UpdateInput(returnButton);
					btn::UpdateInput(exitPauseButton);

					if (retryButton.signal)
					{
						isPaused = false;
						gameTimer = 0.0f;
						ball::Reset(ball);
						obstacle::Reset(obstacles);
					}

					if (returnButton.signal || ctrl::IsKeyPressed(pauseKey))
					{
						isPaused = false;
					}

					if (exitPauseButton.signal)
					{
						currentState = GameState::MAIN_MENU;
					}

					break;
				}
				else
				{
					backgroundManager::Update();
				}

				gameTimer += rend::deltaTime;

				btn::UpdateInput(pauseButton);

				if (pauseButton.signal || ctrl::IsKeyPressed(pauseKey))
				{
					isPaused = true;
				}

				ball::UpdateInput(ball);

				obstacle::Update(obstacles);

				ball::Update(ball);

				for (int o = 0; o < obstacle::maxObstacles; o++)
				{
					if (obstacle::manager::Collide(obstacles[o].obstacles, ball))
					{
						ball::Die(ball);
					}
				}

				break;
			case GameState::CREDITS:

				btn::UpdateInput(backButton);

				if (backButton.signal)
				{
					currentState = GameState::MAIN_MENU;
				}

				break;
			}

			bLib::UpdateEnd();

			//Draw
			drw::Begin();
			drw::Clear(DARKGREY_B);

			switch (currentState)
			{
			case GameState::MAIN_MENU:

				btn::Draw(singlePlayer);
				btn::Draw(twoPlayers);
				btn::Draw(creditsButton);
				btn::Draw(exitButton);
				drw::Text(versionTextData.text.c_str(), versionTextData, { 0.97f, 0.045f }, versionTextData.fontSize, { 0,0 }, WHITE_B);

				break;
			case GameState::GAMEPLAY:

				backgroundManager::Draw();

				obstacle::Draw(obstacles);

				ball::Draw(ball);

				btn::Draw(pauseButton);

				if (isPaused)
				{
					drw::Rectangle(vec::Vector4(0.0f, 0.0f, 1.0f, 1.0f), SEMITRANSPARENT_B);
					btn::Draw(retryButton);
					btn::Draw(returnButton);
					btn::Draw(exitPauseButton);

					scoreTextData.text = std::to_string(gameTimer);
				}
				else
				{
					scoreTextData.text = std::to_string(gameTimer);
				}

				break;
			case GameState::CREDITS:

				btn::Draw(backButton);
				drw::Text(creditsTextData.text.c_str(), creditsTextData, { 0.5f, 0.6f }, creditsTextData.fontSize, { 0,0 }, WHITE_B);
				drw::Text(versionTextData.text.c_str(), versionTextData, { 0.97f, 0.045f }, versionTextData.fontSize, { 0,0 }, WHITE_B);

				break;
			}

			drw::End();
		}

		rend::Close();
	}
}