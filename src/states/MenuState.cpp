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

	static btn::Button singlePlayer;
	static btn::Button twoPlayers;
	static btn::Button creditsButton;
	static btn::Button exitButton;

	static drw::TextData versionTextData;

	static void InitLogo();
	static void DrawLogo();

	void Init()
	{
		InitLogo();

		singlePlayer = button::GetTemplate();
		singlePlayer.pos = { 0.5f, 0.4f };
		singlePlayer.textData.text = "Single Player";
		btn::Init(singlePlayer);

		twoPlayers = button::GetTemplate();
		twoPlayers.pos = { 0.5f, 0.3f };
		twoPlayers.textData.text = "Two Players";
		btn::Init(twoPlayers);

		creditsButton = button::GetTemplate();
		creditsButton.pos = { 0.5f, 0.2f };
		creditsButton.textData.text = "Credits";
		btn::Init(creditsButton);

		exitButton = button::GetTemplate();
		exitButton.pos = { 0.5f, 0.1f };
		exitButton.textData.text = "Exit";
		btn::Init(exitButton);

		versionTextData.fontSize = 0.05f;
		versionTextData.text = "v0.4";
		versionTextData.color = SEMITRANSPARENT_B;

		audioManager::PlayMusic(audioManager::MusicID::MUSIC_MENU); // ESTO NO
	}

	void Update()
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

	void Draw()
	{
		DrawLogo();

		btn::Draw(singlePlayer);
		btn::Draw(twoPlayers);
		btn::Draw(creditsButton);
		btn::Draw(exitButton);
		drw::Text(versionTextData.text.c_str(), versionTextData, { 0.97f, 0.045f }, versionTextData.fontSize, { 0,0 }, WHITE_B);
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
}