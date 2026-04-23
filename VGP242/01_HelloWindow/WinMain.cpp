#include<BongoEngine/Inc/BongoEngine.h>

using namespace BongoEngine;
using namespace BongoEngine::Core;
using namespace BongoEngine::Input;

class MainState : public AppState
{
public:
	void Initialize() override
	{
		LOG("MainState : Initialize");
		mStartTime = Core::TimeUtil::GetTime();
	}

	void Update(float deltaTime) override
	{
		if (InputSystem::Get()->IsKeyPressed(KeyCode::G))
		{
			MainApp().ChangeState("GameState");
		}
	}

	void Terminate() override
	{
		LOG("MainState: Terminate");
	}
	
private:
	float mStartTime = 0.0f;
};

class GameState : public AppState
{
public:
	void Initialize() override
	{
		LOG("GameState : Initialize");
		mStartTime = TimeUtil::GetTime();
	}

	void Update(float deltaTime) override
	{
		if (InputSystem::Get()->IsKeyPressed(KeyCode::M))
		{
			MainApp().ChangeState("MainState");
		}
	}

	void Terminate() override
	{
		LOG("GameState: Terminate");
	}

private:
	float mStartTime = 0.0f;
};

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"HelloWindow";

	App& mainApp = MainApp();
	mainApp.AddState<MainState>("MainState");
	mainApp.AddState<GameState>("GameState");
	mainApp.Run(config);
	return 0;

	// :3 Arthur was here :)
}