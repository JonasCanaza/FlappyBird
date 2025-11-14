#include "states/MenuState.h"

#include "BorjaLib.h"

#include "game/Game.h"
#include "states/GameplayState.h"
#include "interface/Button.h"

namespace menuState
{
	static btn::Button singlePlayer;
	static btn::Button twoPlayers;
	static btn::Button creditsButton;
	static btn::Button exitButton;

	static drw::TextData versionTextData;

	void Init()
	{
		singlePlayer = button::GetTemplate();
		singlePlayer.pos = { 0.5f, 0.5f };
		singlePlayer.textData.text = "Single Player";
		btn::Init(singlePlayer);

		twoPlayers = button::GetTemplate();
		twoPlayers.pos = { 0.5f, 0.4f };
		twoPlayers.textData.text = "Two Players";
		btn::Init(twoPlayers);

		creditsButton = button::GetTemplate();
		creditsButton.pos = { 0.5f, 0.3f };
		creditsButton.textData.text = "Credits";
		btn::Init(creditsButton);

		exitButton = button::GetTemplate();
		exitButton.pos = { 0.5f, 0.2f };
		exitButton.textData.text = "Exit";
		btn::Init(exitButton);

		versionTextData.fontSize = 0.05f;
		versionTextData.text = "v0.4";
		versionTextData.color = SEMITRANSPARENT_B;
	}

	void Update()
	{
		btn::UpdateInput(singlePlayer);
		btn::UpdateInput(twoPlayers);
		btn::UpdateInput(creditsButton);
		btn::UpdateInput(exitButton);

		if (singlePlayer.signal || twoPlayers.signal)
		{
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
		}

		if (creditsButton.signal)
		{
			flappyBird::currentState = flappyBird::GameState::CREDITS;
		}

		if (exitButton.signal)
		{
			flappyBird::isRunning = false;
		}
	}

	void Draw()
	{
		btn::Draw(singlePlayer);
		btn::Draw(twoPlayers);
		btn::Draw(creditsButton);
		btn::Draw(exitButton);
		drw::Text(versionTextData.text.c_str(), versionTextData, { 0.97f, 0.045f }, versionTextData.fontSize, { 0,0 }, WHITE_B);
	}
}