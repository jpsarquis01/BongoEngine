#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace BongoEngine;
using namespace BongoEngine::Core;
using namespace BongoEngine::Input;

void App::Run(const AppConfig& config)
{
	// start the app
	LOG("App Started");

	// for all systems we build, initialize all singletones
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight);

	auto handle = myWindow.GetWindowHandle();
	InputSystem::StaticInitialize(handle);

	// After initializing singletones, initialize current state
	ASSERT(mCurrentState != nullptr, "App: need app state to run");
	mCurrentState->Initialize();

	// run the app
	InputSystem* input = InputSystem::Get();
	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();
		input->Update();

		if (!myWindow.IsActive() || input->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}

		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		float deltaTime = TimeUtil::GetDeltaTime();
#if defined(_DEBUG)
		if (deltaTime > 0.5f)
		{
			LOG("App: really long deltaTime, skipping frame %f", deltaTime);
			continue;
		}
#endif
		mCurrentState->Update(deltaTime);

		// render flow
	}
	// terminate active state first
	mCurrentState->Terminate();

	// for all systems we build, terminate all sigletones
	InputSystem::StaticTerminate();

	// Close the app
	myWindow.Terminate();
	LOG("AppEnded");
}

void App::Quit()
{
	mRunning = false;
}

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}