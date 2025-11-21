#pragma once

namespace gameplayState
{
	void Init();
	void Update();
	void Draw();
	void Close();

	void Reset();
	bool IsGamePaused();
	bool IsGameStarted();
	bool IsGameOver();
}