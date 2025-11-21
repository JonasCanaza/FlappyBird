#include "states/CreditsState.h"

#include "BorjaLib.h"

#include "game/Game.h"
#include "interface/Button.h"
#include "audio/AudioManager.h"

namespace creditsState
{
	static btn::Button backButton;
	static drw::TextData creditsTextData;
	
	static const vec::Vector2 BACK_BUTTON_POS = { 0.5f, 0.075f };

	static const vec::Vector2 TEXT_CREDITS_POS = { 0.5f, 0.95f };
	static const float TEXT_CREDITS_SIZE = 0.075f;

	static const int BUTTON_COUNT = 7;

	static btn::Button buttons[BUTTON_COUNT];

	static const float START_Y = 0.225f;
	static const float SPACING_Y = 0.1f;
	static const float BUTTON_X = 0.5f;

	static const vec::Vector2 BUTTONS_CREDITS_SIZE = { 1.2f, 0.08f };

	static const std::string buttonTexts[BUTTON_COUNT] =
	{
		"BorjaLib By: Borja Lia",
		"UI Audio By: Kenney",
		"Player Points Audio By: Kenney",
		"Player Hits Audio By: Kenney",
		"Player Jump Audio By: Kenney",
		"Gameplay Music By: Cyberwave-Orchestra",
		"Menu Music By: Cyberwave-Orchestra"
	};

	enum CreditButton
	{
		BORJALIB_AUTHOR,
		UI_AUDIO,
		PLAYER_POINTS_AUDIO,
		PLAYER_HITS_AUDIO,
		PLAYER_JUMP_AUDIO,
		GAMEPLAY_MUSIC,
		MENU_MUSIC
	};

	void Init()
	{
		backButton = button::GetTemplate();
		backButton.pos = BACK_BUTTON_POS;
		backButton.textData.text = "Back";
		btn::Init(backButton);

		creditsTextData.fontSize = TEXT_CREDITS_SIZE;
		creditsTextData.text = "Made by Borja Lia and Jonas Canaza";

		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			buttons[i] = button::GetTemplate();
			buttons[i].size = BUTTONS_CREDITS_SIZE;
			buttons[i].pos = { BUTTON_X, START_Y + (i * SPACING_Y) };
			buttons[i].textData.text = buttonTexts[i];
			btn::Init(buttons[i]);
		}
	}

	void Update()
	{
		btn::UpdateInput(backButton);

		if (backButton.signal)
		{
			audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);

			flappyBird::currentState = flappyBird::GameState::MAIN_MENU;
		}

		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			btn::UpdateInput(buttons[i]);

			if (buttons[i].signal)
			{
				audioManager::PlaySfx(audioManager::SfxID::SFX_BUTTON_CLICK);

				if (i == CreditButton::MENU_MUSIC)
				{
					OpenURL("https://pixabay.com/es/music/titulo-principal-puzzle-game-loop-bright-casual-video-game-music-249201/");
				}
				else if (i == CreditButton::GAMEPLAY_MUSIC)
				{
					OpenURL("https://pixabay.com/es/music/melod%c3%adas-para-ni%c3%b1os-felices-upbeat-background-loop-casual-video-game-music-249200/");
				}
				else if (i == CreditButton::PLAYER_JUMP_AUDIO)
				{
					OpenURL("https://www.kenney.nl/assets/interface-sounds");
				}
				else if (i == CreditButton::PLAYER_HITS_AUDIO)
				{
					OpenURL("https://www.kenney.nl/assets/impact-sounds");
				}
				else if (i == CreditButton::PLAYER_POINTS_AUDIO)
				{
					OpenURL("https://www.kenney.nl/assets/digital-audio");
				}
				else if (i == CreditButton::UI_AUDIO)
				{
					OpenURL("https://www.kenney.nl/assets/ui-audio");
				}
				else if (i == CreditButton::BORJALIB_AUTHOR)
				{
					OpenURL("https://github.com/BorjaLia/Borja_Lib");
				}
			}
		}
	}

	void Draw()
	{
		btn::Draw(backButton);

		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			btn::Draw(buttons[i]);
		}

		drw::Text(creditsTextData.text.c_str(), creditsTextData, TEXT_CREDITS_POS, creditsTextData.fontSize);
	}
}