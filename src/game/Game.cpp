#include "game/Game.h"

#include "BorjaLib.h"

#include "states/MenuState.h"
#include "states/GameplayState.h"
#include "states/CreditsState.h"
#include "background/BackgroundManager.h"
#include "interface/Button.h"

namespace flappyBird
{
	GameState currentState;
	bool isRunning;
	bool isMultiplayer;

	static void Init();

	void Play()
	{
		Init();

		while (isRunning)
		{
			isRunning = !rend::ShouldExit();

			//Update
			bLib::UpdateStart();

			if (!gameplayState::GetState())
			{
				backgroundManager::Update();
			}

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

		menuState::Init();
		gameplayState::Init();
		creditsState::Init();
	}
}