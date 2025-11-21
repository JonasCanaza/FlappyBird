#include "game/Game.h"

#include "BorjaLib.h"

#include "states/MenuState.h"
#include "states/GameplayState.h"
#include "states/CreditsState.h"
#include "background/BackgroundManager.h"
#include "interface/Button.h"
#include "audio/AudioManager.h"
#include "entities/Ball.h"
#include "entities/Obstacle.h"

namespace flappyBird
{
	GameState currentState;
	bool isRunning;
	bool isMultiplayer;

	static void Init();

	void Play()
	{
		audioManager::Init();
		Init();

		while (isRunning)
		{
			isRunning = !rend::ShouldExit();

			//Update
			bLib::UpdateStart();

			if (!gameplayState::IsGamePaused() && gameplayState::IsGameStarted() && !gameplayState::IsGameOver())
			{
				backgroundManager::Update();
			}

			audioManager::Update();

			switch (currentState)
			{
			case GameState::MAIN_MENU:

				menuState::Update();

				break;
			case GameState::GAMEPLAY:

				gameplayState::Update();

				break;
			case GameState::CREDITS:

				creditsState::Update();

				break;
			}

			bLib::UpdateEnd();

			//Draw
			drw::Begin();
			drw::Clear(DARKGREY_B);

			backgroundManager::Draw();

			switch (currentState)
			{
			case GameState::MAIN_MENU:

				menuState::Draw();

				break;
			case GameState::GAMEPLAY:

				gameplayState::Draw();

				break;
			case GameState::CREDITS:

				creditsState::Draw();

				break;
			}

			drw::End();
		}

		gameplayState::Close();
		menuState::Close();
		backgroundManager::Close();
		audioManager::Close();
		ball::CloseTextures();
		obstacle::CloseTextures();
		rend::Close();
	}

	static void Init()
	{
		bLib::Init("Flappy Bird");

		currentState = GameState::MAIN_MENU;
		isRunning = true;
		isMultiplayer = false;

		backgroundManager::Init();
		button::Init();
		audioManager::InitSound();

		menuState::Init();
		gameplayState::Init();
		creditsState::Init();

		ball::InitTextures();
		obstacle::InitTextures();
	}
}