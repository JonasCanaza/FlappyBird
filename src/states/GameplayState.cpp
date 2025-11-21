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

	static const vec::Vector2 P1_START_POS = { 0.25f, 0.5f };
	static const vec::Vector2 P2_START_POS = { 0.15f, 0.5f };

	// BUTTONS

	static btn::Button pauseButton;
	static btn::Button retryButton;
	static btn::Button returnButton;
	static btn::Button exitButton;

	static const vec::Vector2 PAUSE_BUTTON_POS = { 0.5f, 0.9f };
	static const vec::Vector2 RETRY_BUTTON_POS = { 0.5f, 0.7f };
	static const vec::Vector2 RETURN_BUTTON_POS = { 0.5f, 0.6f };
	static const vec::Vector2 EXIT_BUTTON_POS = { 0.5f, 0.5f };

	// TEMPORARY BACKGROUND

	static const vec::Vector4 TRANSPARENT_BACKGROUND = { 0.0f, 0.0f, 1.0f, 1.0f };

	// SCORES TEXT

	static const vec::Vector2 PLAYER_ONE_TEXT_POS = { 0.8f, 0.9f };
	static const vec::Vector2 PLAYER_TWO_TEXT_POS = { 0.2f, 0.9f };
	static const float SCORE_TEXT_SIZE = 0.075f;

	// DESCRIPTIONS

	static drw::SpriteData howToPlayAlone;
	static drw::SpriteData howToPlayMultiplayer;
	static const vec::Vector2 DESCRIPTIONS_POS = { 0.5f, 0.5f };
	static const vec::Vector2 DESCRIPTIONS_SIZE = { 1.0f, 1.0f };

	// GAME OVER TEXT

	static const vec::Vector2 GAME_OVER_TITLE_POS = { 0.5f, 0.5f };
	static const vec::Vector2 GAME_OVER_SCORE_P1_POS = { 0.5f, 0.40f };
	static const vec::Vector2 GAME_OVER_SCORE_P2_POS = { 0.5f, 0.30f };
	static const float GAME_OVER_TITLE_SIZE = 0.15f;
	static const float GAME_OVER_SCORE_SIZE = 0.10f;

	// RESET TEXT

	static const vec::Vector2 RESET_TEXT_POS = { 0.5f, 0.1f };
	static const float RESET_TEXT_SIZE = 0.075f;

	static bool isPaused;
	static bool gameStarted;
	static bool isGameOver;

	static void Input();

	static void InitPauseButton();
	static void UpdatePauseButton();
	static void DrawPauseButton();

	static void InitButtons();
	static void UpdateButtons();
	static void DrawButtons();

	static void UpdateScores();
	static void DrawScores();

	static void InitDescriptions();
	static void DrawDescriptions();

	static void CheckCollisions();

	static bool ArePlayersDead();
	static void DrawGameOver();

	void Init()
	{
		ball::Init(ballOne);
		ball::Init(ballTwo);
		obstacle::Init(obstacles);

		InitPauseButton();
		InitButtons();

		InitDescriptions();

		isPaused = false;
		gameStarted = false;
		isGameOver = false;
	}

	void Update()
	{
		Input();

		if (isPaused)
		{
			UpdateButtons();
		}
		else
		{
			if (gameStarted && !isGameOver)
			{
				UpdatePauseButton();

				ball::Update(ballOne);

				if (flappyBird::isMultiplayer)
				{
					ball::Update(ballTwo);
				}

				obstacle::Update(obstacles);

				UpdateScores();
				CheckCollisions();

				if (ArePlayersDead())
				{
					isGameOver = true;
				}
			}
		}
	}

	void Draw()
	{
		if (ballOne.isAlive)
		{
			ball::Draw(ballOne, ball::Player::One);
		}

		if (flappyBird::isMultiplayer && ballTwo.isAlive)
		{
			ball::Draw(ballTwo, ball::Player::Two);
		}

		obstacle::Draw(obstacles);

		if (!isGameOver)
		{
			DrawScores();
		}

		if (gameStarted && !isGameOver)
		{
			DrawPauseButton();
		}

		if (isPaused)
		{
			drw::Rectangle(TRANSPARENT_BACKGROUND, SEMITRANSPARENT_B);
			DrawButtons();
		}

		if (!gameStarted)
		{
			drw::Rectangle(TRANSPARENT_BACKGROUND, SEMITRANSPARENT_B);
			DrawDescriptions();
		}

		if (isGameOver)
		{
			drw::Rectangle(TRANSPARENT_BACKGROUND, SEMITRANSPARENT_B);
			DrawGameOver();
		}
	}

	void Close()
	{
		drw::DeInitSpriteData(howToPlayAlone);
		drw::DeInitSpriteData(howToPlayMultiplayer);
	}

	void Reset()
	{
		isPaused = false;
		gameStarted = false;
		isGameOver = false;

		ball::Reset(ballOne);
		ball::Reset(ballTwo);
		obstacle::Reset(obstacles);
		
		ballOne.position = P1_START_POS;
		ballTwo.position = P2_START_POS;
		
		ballOne.color = RED_B;
		ballTwo.color = BLUE_B;
	}

	bool IsGamePaused()
	{
		return isPaused;
	}

	bool IsGameStarted()
	{
		return gameStarted;
	}

	bool IsGameOver()
	{
		return isGameOver;
	}

	static void Input()
	{
		if (IsKeyPressed(KEY_ESCAPE) && gameStarted && !isGameOver)
		{
			audioManager::PlaySfx(audioManager::SfxID::SFX_PANEL);

			isPaused = !isPaused;
			audioManager::PauseMusic(audioManager::MusicID::MUSIC_GAMEPLAY, isPaused);
		}

		if (!gameStarted)
		{
			if (!flappyBird::isMultiplayer)
			{
				if (IsKeyPressed(KEY_UP))
				{
					gameStarted = true;
				}
			}
			else
			{
				if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
				{
					gameStarted = true;
				}
			}
		}
		else
		{
			if (isGameOver)
			{
				if (!flappyBird::isMultiplayer)
				{
					if (IsKeyPressed(KEY_UP))
					{
						Reset();
					}
				}
				else
				{
					if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
					{
						Reset();
					}
				}
			}
		}

		if (!isPaused && gameStarted)
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

	static void InitPauseButton()
	{
		pauseButton = button::GetTemplate();
		pauseButton.pos = PAUSE_BUTTON_POS;
		pauseButton.textData.text = "Pause";
		pauseButton.mainTextureID = button::GetNormalTextureID();
		pauseButton.hoveredTextureID = button::GetHoverTextureID();
		pauseButton.useSprite = true;
		btn::Init(pauseButton);
	}

	static void UpdatePauseButton()
	{
		btn::UpdateInput(pauseButton);

		if (pauseButton.signal)
		{
			audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);
			audioManager::PlaySfx(audioManager::SfxID::SFX_PANEL);

			isPaused = true;
			audioManager::PauseMusic(audioManager::MusicID::MUSIC_GAMEPLAY, isPaused);
		}
	}

	static void DrawPauseButton()
	{
		btn::Draw(pauseButton);
	}

	static void InitButtons()
	{
		retryButton = button::GetTemplate();
		retryButton.pos = RETRY_BUTTON_POS;
		retryButton.textData.text = "Retry";
		retryButton.mainTextureID = button::GetNormalTextureID();
		retryButton.hoveredTextureID = button::GetHoverTextureID();
		retryButton.useSprite = true;
		btn::Init(retryButton);

		returnButton = button::GetTemplate();
		returnButton.pos = RETURN_BUTTON_POS;
		returnButton.textData.text = "Return";
		returnButton.mainTextureID = button::GetNormalTextureID();
		returnButton.hoveredTextureID = button::GetHoverTextureID();
		returnButton.useSprite = true;
		btn::Init(returnButton);

		exitButton = button::GetTemplate();
		exitButton.pos = EXIT_BUTTON_POS;
		exitButton.textData.text = "Exit to Menu";
		exitButton.mainTextureID = button::GetNormalTextureID();
		exitButton.hoveredTextureID = button::GetHoverTextureID();
		exitButton.useSprite = true;
		btn::Init(exitButton);
	}

	static void UpdateButtons()
	{
		btn::UpdateInput(retryButton);
		btn::UpdateInput(returnButton);
		btn::UpdateInput(exitButton);

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

		if (exitButton.signal)
		{
			audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);

			isPaused = false;
			gameStarted = false;
			flappyBird::currentState = flappyBird::GameState::MAIN_MENU;
			audioManager::StopMusic(audioManager::MusicID::MUSIC_GAMEPLAY);
			audioManager::PlayMusic(audioManager::MusicID::MUSIC_MENU);
		}
	}

	static void DrawButtons()
	{
		btn::Draw(retryButton);
		btn::Draw(returnButton);
		btn::Draw(exitButton);
	}

	static void UpdateScores()
	{
		for (int i = 0; i < obstacle::maxFullObstacles; i++)
		{
			float obstacleRight = obstacles[i].position.x + obstacles[i].width / 2.0f;

			if (!obstacles[i].scoredByPlayerOne && ballOne.position.x > obstacleRight && ballOne.isAlive)
			{
				audioManager::PlaySfx(audioManager::SfxID::SFX_SCORE_PLAYER);

				obstacles[i].scoredByPlayerOne = true;
				ballOne.score++;
			}

			if (flappyBird::isMultiplayer && !obstacles[i].scoredByPlayerTwo && ballTwo.position.x > obstacleRight && ballTwo.isAlive)
			{
				audioManager::PlaySfx(audioManager::SfxID::SFX_SCORE_PLAYER);

				obstacles[i].scoredByPlayerTwo = true;
				ballTwo.score++;
			}
		}

	}
	
	static void DrawScores()
	{
		drw::Text(("P1   Score: " + std::to_string(ballOne.score)).c_str(),
			PLAYER_ONE_TEXT_POS,
			SCORE_TEXT_SIZE,
			{ 0.0f, 0.0f },
			RED_B);

		if (flappyBird::isMultiplayer)
		{
			drw::Text(("P2   Score: " + std::to_string(ballTwo.score)).c_str(),
				PLAYER_TWO_TEXT_POS,
				SCORE_TEXT_SIZE,
				{ 0.0f, 0.0f },
				GREEN_B);
		}
	}

	static void InitDescriptions()
	{
		howToPlayAlone.file = "res/sprites/descriptions/HowToPlayAlone.png";
		howToPlayAlone.size = DESCRIPTIONS_SIZE;
		howToPlayAlone.id = drw::InitSpriteData(howToPlayAlone);

		howToPlayMultiplayer.file = "res/sprites/descriptions/HowToPlayMultiplayer.png";
		howToPlayMultiplayer.size = DESCRIPTIONS_SIZE;
		howToPlayMultiplayer.id = drw::InitSpriteData(howToPlayMultiplayer);
	}

	static void DrawDescriptions()
	{
		if (!flappyBird::isMultiplayer)
		{
			drw::Sprite(drw::spriteDataList[howToPlayAlone.id], DESCRIPTIONS_POS, howToPlayAlone.size);
		}
		else
		{
			drw::Sprite(drw::spriteDataList[howToPlayMultiplayer.id], DESCRIPTIONS_POS, howToPlayMultiplayer.size);
		}
	}

	static void CheckCollisions()
	{
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

	static bool ArePlayersDead()
	{
		if (!ballOne.isAlive)
		{
			if (!flappyBird::isMultiplayer)
			{
				return true;
			}

			if (!ballTwo.isAlive)
			{
				return true;
			}
		}

		return false;
	}

	static void DrawGameOver()
	{
		drw::Text("GAME   OVER", GAME_OVER_TITLE_POS, GAME_OVER_TITLE_SIZE, { 0.0f, 0.0f }, WHITE_B);

		drw::Text(("P1   Score: " + std::to_string(ballOne.score)).c_str(),
			GAME_OVER_SCORE_P1_POS,
			GAME_OVER_SCORE_SIZE,
			{ 0.0f, 0.0f },
			RED_B);

		if (flappyBird::isMultiplayer)
		{
			drw::Text(("P2   Score: " + std::to_string(ballTwo.score)).c_str(),
				GAME_OVER_SCORE_P2_POS,
				GAME_OVER_SCORE_SIZE,
				{ 0.0f, 0.0f },
				GREEN_B);
		}

		if (!flappyBird::isMultiplayer)
		{
			drw::Text("Press Up Arrow to reset", RESET_TEXT_POS, RESET_TEXT_SIZE, { 0.0f, 0.0f }, WHITE_B);
		}
		else
		{
			drw::Text("Press Up Arrow or W to reset", RESET_TEXT_POS, RESET_TEXT_SIZE, { 0.0f, 0.0f }, WHITE_B);
		}
	}
}