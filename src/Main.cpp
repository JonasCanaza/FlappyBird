#include "BorjaLib.h"
#include "Ball.h"
#include "ObstacleManager.h"

int main()
{
	bool isPaused = false;

	ctrl::Key pauseKey = ctrl::Key::ESCAPE;

	enum class GameState
	{
		MAIN_MENU,
		GAMEPLAY,
		CREDITS
	};

	bool isRunning = true;
	bLib::Init("Flappy Bird");
	GameState currentState = GameState::MAIN_MENU;

	float gameTimer = 0.0f;
	//const int MOUSE_PARTICLE_COUNT = 5;

	//Menu
	btn::Button playButton;
	btn::Button creditsButton;
	btn::Button exitButton;

	// Credits
	btn::Button backButton;
	drw::TextData creditsTextData;

	// Gameplay
	btn::Button pauseButton;
	drw::TextData scoreTextData;
	//drw::AnimationData mouseAnim;
	//prtcl::ParticleActivator mouseParticleActivator;
	//prtcl::ParticleData mouseParticles[MOUSE_PARTICLE_COUNT]; // Array estático

	bll::Ball ball;
	bll::Init(ball);

	obstcl::FullObstacle obstacles[obstcl::maxObstacles];
	obstcl::Init(obstacles);

	// Pause
	btn::Button retryButton;
	btn::Button returnButton;
	btn::Button exitPauseButton;

	//Version Overlay
	drw::TextData versionTextData;

	//drw::SpriteData fireFrame1;
	//fireFrame1.file = "res/sprites/fire1.png";
	//fireFrame1.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame2;
	//fireFrame2.file = "res/sprites/fire2.png";
	//fireFrame2.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame3;
	//fireFrame3.file = "res/sprites/fire3.png";
	//fireFrame3.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrame4;
	//fireFrame4.file = "res/sprites/fire4.png";
	//fireFrame4.size = { 0.1f, 0.1f };

	//drw::SpriteData fireFrames[] = { fireFrame1, fireFrame2, fireFrame3, fireFrame4 };

	//mouseAnim.duration = 0.25f;
	//drw::InitAnimData(mouseAnim, fireFrames, 4);

	// Inicializacion

	btn::Button templateButton;
	templateButton.size = { 0.275f, 0.075f };
	templateButton.textData.fontSize = 0.075f;
	templateButton.useSprite = false;
	templateButton.activeColor = SEMITRANSPARENT_B;
	templateButton.mainColor = SEMITRANSPARENT_B;
	templateButton.hoveredColor = SEMITRANSPARENT_B;


	//Menu
	playButton = templateButton;
	playButton.pos = { 0.5f, 0.6f };
	playButton.textData.text = "Play";
	btn::Init(playButton);

	creditsButton = templateButton;
	creditsButton.pos = { 0.5f, 0.5f };
	creditsButton.textData.text = "Credits";
	btn::Init(creditsButton);

	exitButton = templateButton;
	exitButton.pos = { 0.5f, 0.4f };
	exitButton.textData.text = "Exit";
	btn::Init(exitButton);

	//Credits
	backButton = templateButton;
	backButton.pos = { 0.5f, 0.3f };
	backButton.textData.text = "Back";
	btn::Init(backButton);

	creditsTextData.fontSize = 0.05f;
	creditsTextData.text = "Made by Borja Lia";

	//Gameplay
	pauseButton = templateButton;
	pauseButton.pos = { 0.5f, 0.9f };
	pauseButton.textData.text = "Pause";
	btn::Init(pauseButton);

	scoreTextData.fontSize = 0.1f;

	//mouseParticleActivator.loop = true;
	//mouseParticleActivator.animated = true;
	//mouseParticleActivator.animation = mouseAnim;
	//mouseParticleActivator.amount = MOUSE_PARTICLE_COUNT;
	//mouseParticleActivator.lifetime = { 0.2f, 0.5f };
	//mouseParticleActivator.direction = { 0.0f, -1.0f };
	//mouseParticleActivator.spread = 180.0f;
	//mouseParticleActivator.minSize = { 0.005f, 0.005f };
	//mouseParticleActivator.maxSize = { 0.02f, 0.02f };
	//mouseParticleActivator.speed = { 0.1f, 0.3f };
	//prtcl::Init(mouseParticleActivator, mouseParticles);

	retryButton = templateButton;
	retryButton.pos = { 0.5f, 0.7f };
	retryButton.textData.text = "Retry";
	btn::Init(retryButton);

	returnButton = templateButton;
	returnButton.pos = { 0.5f, 0.6f };
	returnButton.textData.text = "Return";
	btn::Init(returnButton);

	exitPauseButton = templateButton;
	exitPauseButton.pos = { 0.5f, 0.5f };
	exitPauseButton.textData.text = "Exit to Menu";
	btn::Init(exitPauseButton);

	versionTextData.fontSize = 0.05f;
	versionTextData.text = "v0.2";
	versionTextData.color = SEMITRANSPARENT_B;

	while (isRunning)
	{
		isRunning = !rend::ShouldExit();

		//Update
		bLib::UpdateStart();

		switch (currentState)
		{
		case GameState::MAIN_MENU:

			btn::UpdateInput(playButton);
			btn::UpdateInput(creditsButton);
			btn::UpdateInput(exitButton);

			if (playButton.signal)
			{
				currentState = GameState::GAMEPLAY;
				isPaused = false;
				gameTimer = 0.0f;
				bll::Reset(ball);
				obstcl::Reset(obstacles);
			}

			if (creditsButton.signal)
			{
				currentState = GameState::CREDITS;
			}

			if (exitButton.signal)
			{
				isRunning = false;
			}

			break;
		case GameState::GAMEPLAY:

			if (isPaused)
			{
				btn::UpdateInput(retryButton);
				btn::UpdateInput(returnButton);
				btn::UpdateInput(exitPauseButton);

				if (retryButton.signal)
				{
					isPaused = false;
					gameTimer = 0.0f;
					bll::Reset(ball);
					obstcl::Reset(obstacles);
				}

				if (returnButton.signal || ctrl::IsKeyPressed(pauseKey))
				{
					isPaused = false;
				}

				if (exitPauseButton.signal)
				{
					currentState = GameState::MAIN_MENU;
				}

				break;
			}

			gameTimer += rend::deltaTime;

			btn::UpdateInput(pauseButton);

			if (pauseButton.signal || ctrl::IsKeyPressed(pauseKey))
			{
				isPaused = true;
			}

			bll::UpdateInput(ball);

			obstcl::Update(obstacles);

			bll::Update(ball);

			for (int o = 0; o < obstcl::maxObstacles; o++)
			{
				if (obstcl::mngr::Collide(obstacles[o].obstacles, ball))
				{
					bll::Die(ball);
				}
			}

			//mouseParticleActivator.pos = rend::mousePos;
			//prtcl::Update(mouseParticleActivator, mouseParticles);

			break;

		case GameState::CREDITS:

			btn::UpdateInput(backButton);

			if (backButton.signal)
			{
				currentState = GameState::MAIN_MENU;
			}

			break;
		}

		bLib::UpdateEnd();

		//Draw
		drw::Begin();
		drw::Clear(DARKGREY_B);

		switch (currentState)
		{
		case GameState::MAIN_MENU:

			btn::Draw(playButton);
			btn::Draw(creditsButton);
			btn::Draw(exitButton);
			drw::Text(versionTextData.text.c_str(), versionTextData, { 0.97f, 0.045f }, versionTextData.fontSize, { 0,0 }, WHITE_B);

			break;
		case GameState::GAMEPLAY:

			//prtcl::Draw(mouseParticles);

			obstcl::Draw(obstacles);

			bll::Draw(ball);

			btn::Draw(pauseButton);

			//drw::Text(scoreTextData.text.c_str(),scoreTextData, { 0.5f, 0.5f }, scoreTextData.fontSize, { 0,0 }, WHITE_B);
			
			if (isPaused)
			{
				drw::Rectangle(vec::Vector4(0.0f, 0.0f, 1.0f, 1.0f), SEMITRANSPARENT_B);
				btn::Draw(retryButton);
				btn::Draw(returnButton);
				btn::Draw(exitPauseButton);

				scoreTextData.text = std::to_string(gameTimer);
			}
			else
			{
				scoreTextData.text = std::to_string(gameTimer);
			}
			
			break;
		case GameState::CREDITS:

			btn::Draw(backButton);
			drw::Text(creditsTextData.text.c_str(), creditsTextData, { 0.5f, 0.6f }, creditsTextData.fontSize, { 0,0 }, WHITE_B);
			drw::Text(versionTextData.text.c_str(), versionTextData, { 0.97f, 0.045f }, versionTextData.fontSize, { 0,0 }, WHITE_B);

			break;
		}

		drw::End();

		//Sounds

	}

	rend::Close();

	return 0;
}