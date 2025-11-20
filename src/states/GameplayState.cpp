#include "states/GameplayState.h"

#include "BorjaLib.h"

#include "game/Game.h"
#include "entities/Ball.h"
#include "entities/ObstacleManager.h"
#include "interface/Button.h"
#include "audio/AudioManager.h"

namespace gameplayState
{
	static ball::Ball ballOne;
	static ball::Ball ballTwo;
	static obstacle::FullObstacle obstacles[obstacle::maxFullObstacles];

	static btn::Button pauseButton;
	static btn::Button retryButton;
	static btn::Button returnButton;
	static btn::Button exitPauseButton;

	static bool isPaused;

	static void Input();

	void Init()
	{
		ball::Init(ballOne);
		ball::Init(ballTwo);
		obstacle::Init(obstacles);

		pauseButton = button::GetTemplate();
		pauseButton.pos = { 0.5f, 0.9f };
		pauseButton.textData.text = "Pause";
		btn::Init(pauseButton);

		retryButton = button::GetTemplate();
		retryButton.pos = { 0.5f, 0.7f };
		retryButton.textData.text = "Retry";
		btn::Init(retryButton);

		returnButton = button::GetTemplate();
		returnButton.pos = { 0.5f, 0.6f };
		returnButton.textData.text = "Return";
		btn::Init(returnButton);

		exitPauseButton = button::GetTemplate();
		exitPauseButton.pos = { 0.5f, 0.5f };
		exitPauseButton.textData.text = "Exit to Menu";
		btn::Init(exitPauseButton);
	}

	void Update()
	{
		Input();

		if (isPaused)
		{
			btn::UpdateInput(retryButton);
			btn::UpdateInput(returnButton);
			btn::UpdateInput(exitPauseButton);

			if (retryButton.signal)
			{
				audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);

				Reset();
				audioManager::StopMusic(audioManager::MusicID::MUSIC_GAMEPLAY);
				audioManager::PlayMusic(audioManager::MusicID::MUSIC_GAMEPLAY);
			}

			if (returnButton.signal)
			{
				audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);

				isPaused = false;
				audioManager::PauseMusic(audioManager::MusicID::MUSIC_GAMEPLAY, isPaused);
			}

			if (exitPauseButton.signal)
			{
				audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);

				isPaused = false;
				flappyBird::currentState = flappyBird::GameState::MAIN_MENU;
				audioManager::StopMusic(audioManager::MusicID::MUSIC_GAMEPLAY);
				audioManager::PlayMusic(audioManager::MusicID::MUSIC_MENU);
			}
		}
		else
		{
			btn::UpdateInput(pauseButton);

			if (pauseButton.signal)
			{
				audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);
				audioManager::PlaySfx(audioManager::SfxID::SFX_PANEL);

				isPaused = true;
				audioManager::PauseMusic(audioManager::MusicID::MUSIC_GAMEPLAY, isPaused);
			}

			ball::Update(ballOne);

			if (flappyBird::isMultiplayer)
			{
				ball::Update(ballTwo);
			}

			obstacle::Update(obstacles);

			for (int i = 0; i < obstacle::maxFullObstacles; i++)
			{
				if (obstacle::manager::Collide(obstacles[i], ballOne))
				{
					audioManager::PlaySfx(audioManager::SfxID::SFX_HIT_PLAYER);

					ball::Die(ballOne);
				}

				if (flappyBird::isMultiplayer && obstacle::manager::Collide(obstacles[i], ballTwo))
				{
					audioManager::PlaySfx(audioManager::SfxID::SFX_HIT_PLAYER);

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
		
		ballOne.position = { 0.25f, 0.5f };
		ballTwo.position = { 0.15f, 0.5f };
		
		ballOne.color = RED_B;
		ballTwo.color = BLUE_B;
	}

	bool GetState()
	{
		return isPaused;
	}

	static void Input()
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			audioManager::PlaySfx(audioManager::SfxID::SFX_PANEL);

			isPaused = !isPaused;
			audioManager::PauseMusic(audioManager::MusicID::MUSIC_GAMEPLAY, isPaused);
		}

		if (!isPaused)
		{
			if (IsKeyPressed(KEY_UP) && ballOne.isAlive)
			{
				ball::Jump(ballOne);
				audioManager::PlaySfx(audioManager::SfxID::SFX_JUMP_PLAYER);
			}

			if (IsKeyPressed(KEY_W) && flappyBird::isMultiplayer && ballTwo.isAlive)
			{
				ball::Jump(ballTwo);
				audioManager::PlaySfx(audioManager::SfxID::SFX_JUMP_PLAYER);
			}
		}
	}
}