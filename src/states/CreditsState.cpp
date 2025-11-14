#include "states/CreditsState.h"

#include "BorjaLib.h"

#include "game/Game.h"
#include "interface/Button.h"

namespace creditsState
{
	static btn::Button backButton;
	static drw::TextData creditsTextData;

	void Init()
	{
		backButton = button::GetTemplate();
		backButton.pos = { 0.5f, 0.3f };
		backButton.textData.text = "Back";
		btn::Init(backButton);

		creditsTextData.fontSize = 0.05f;
		creditsTextData.text = "Made by Borja Lia and Jonas Canaza";
	}

	void Update()
	{
		btn::UpdateInput(backButton);

		if (backButton.signal)
		{
			flappyBird::currentState = flappyBird::GameState::MAIN_MENU;
		}
	}

	void Draw()
	{
		btn::Draw(backButton);
		drw::Text(creditsTextData.text.c_str(), creditsTextData, { 0.5f, 0.6f }, creditsTextData.fontSize, { 0,0 }, WHITE_B);
	}
}