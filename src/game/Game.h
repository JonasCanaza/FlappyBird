#pragma once

namespace flappyBird
{
	enum class GameState
	{
		MAIN_MENU,
		GAMEPLAY,
		CREDITS
	};

	extern GameState currentState;
	extern bool isRunning;
	extern bool isMultiplayer;

	void Play();
}