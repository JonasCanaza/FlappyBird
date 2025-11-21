#include "states/MenuState.h"

#include "BorjaLib.h"

#include "game/Game.h"
#include "states/GameplayState.h"
#include "interface/Button.h"
#include "audio/AudioManager.h"

namespace menuState
{
	static drw::SpriteData logo;
	static const vec::Vector2 LOGO_SIZE = { 0.5f, 0.5f };
	static const vec::Vector2 LOGO_POS = { 0.5f, 0.75f };

	// BUTTONS

	static btn::Button singlePlayer;
	static btn::Button twoPlayers;
	static btn::Button creditsButton;
	static btn::Button exitButton;

	static const vec::Vector2 SINGLE_PLAYER_BUTTON_POS = { 0.5f, 0.4f };
	static const vec::Vector2 TWO_PLAYERS_BUTTON_POS = { 0.5f, 0.3f };
	static const vec::Vector2 CREDITS_BUTTON_POS = { 0.5f, 0.2f };
	static const vec::Vector2 EXIT_BUTTON_POS = { 0.5f, 0.1f };

	// TEXT VERSION

	static drw::TextData versionTextData;

	static const vec::Vector2 VERSION_TEXT_POS = { 0.97f, 0.045f };
	static const float VERSION_TEXT_SIZE = 0.05f;

	// TEMPORARY BACKGROUND

	static const vec::Vector4 TRANSPARENT_BACKGROUND = { 0.0f, 0.0f, 1.0f, 1.0f };
	static const bColor BACKGROUND_COLOR = { 0, 0, 0, 48 };

	static void InitLogo();
	static void DrawLogo();

	static void InitButtons();
	static void UpdateButtons();
	static void DrawButtons();

	static void InitTextVersion();
	static void DrawTextVersion();

	void Init()
	{
		InitLogo();
		InitButtons();
		InitTextVersion();

		audioManager::PlayMusic(audioManager::MusicID::MUSIC_MENU);
	}

	void Update()
	{
		UpdateButtons();
	}

	void Draw()
	{
		drw::Rectangle(TRANSPARENT_BACKGROUND, BACKGROUND_COLOR);
		DrawLogo();
		DrawButtons();
		DrawTextVersion();
	}

	void Close()
	{
		drw::DeInitSpriteData(logo);
	}

	static void InitLogo()
	{
		logo.file = "res/sprites/ui/logo.png";
		logo.size = LOGO_SIZE;
		logo.id = drw::InitSpriteData(logo);
	}

	static void DrawLogo()
	{
		drw::Sprite(drw::spriteDataList[logo.id], LOGO_POS, logo.size);
	}

	static void InitButtons()
	{
		singlePlayer = button::GetTemplate();
		singlePlayer.pos = SINGLE_PLAYER_BUTTON_POS;
		singlePlayer.textData.text = "Single Player";
		singlePlayer.mainTextureID = button::GetNormalTextureID();
		singlePlayer.hoveredTextureID = button::GetHoverTextureID();
		singlePlayer.useSprite = true;
		btn::Init(singlePlayer);

		twoPlayers = button::GetTemplate();
		twoPlayers.pos = TWO_PLAYERS_BUTTON_POS;
		twoPlayers.textData.text = "Two Players";
		twoPlayers.mainTextureID = button::GetNormalTextureID();
		twoPlayers.hoveredTextureID = button::GetHoverTextureID();
		twoPlayers.useSprite = true;
		btn::Init(twoPlayers);

		creditsButton = button::GetTemplate();
		creditsButton.pos = CREDITS_BUTTON_POS;
		creditsButton.textData.text = "Credits";
		creditsButton.mainTextureID = button::GetNormalTextureID();
		creditsButton.hoveredTextureID = button::GetHoverTextureID();
		creditsButton.useSprite = true;
		btn::Init(creditsButton);

		exitButton = button::GetTemplate();
		exitButton.pos = EXIT_BUTTON_POS;
		exitButton.textData.text = "Exit";
		exitButton.mainTextureID = button::GetNormalTextureID();
		exitButton.hoveredTextureID = button::GetHoverTextureID();
		exitButton.useSprite = true;
		btn::Init(exitButton);
	}

	static void UpdateButtons()
	{
		btn::UpdateInput(singlePlayer);
		btn::UpdateInput(twoPlayers);
		btn::UpdateInput(creditsButton);
		btn::UpdateInput(exitButton);

		if (singlePlayer.signal || twoPlayers.signal)
		{
			audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);

			if (singlePlayer.signal)
			{
				flappyBird::isMultiplayer = false;
			}
			else
			{
				flappyBird::isMultiplayer = true;
			}

			gameplayState::Reset();
			flappyBird::currentState = flappyBird::GameState::GAMEPLAY;
			audioManager::StopMusic(audioManager::MusicID::MUSIC_MENU);
			audioManager::PlayMusic(audioManager::MusicID::MUSIC_GAMEPLAY);
		}

		if (creditsButton.signal)
		{
			audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);

			flappyBird::currentState = flappyBird::GameState::CREDITS;
		}

		if (exitButton.signal)
		{
			flappyBird::isRunning = false;
		}
	}

	static void DrawButtons()
	{
		btn::Draw(singlePlayer);
		btn::Draw(twoPlayers);
		btn::Draw(creditsButton);
		btn::Draw(exitButton);
	}

	static void InitTextVersion()
	{
		versionTextData.fontSize = VERSION_TEXT_SIZE;
		versionTextData.text = "v0.4";
		versionTextData.color = SEMITRANSPARENT_B;
	}

	static void DrawTextVersion()
	{
		drw::Text(versionTextData.text.c_str(), versionTextData, VERSION_TEXT_POS, versionTextData.fontSize);
	}
}