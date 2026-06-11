#include "GameState.h"

using namespace BongoEngine;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"06_HelloDebug";

	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);
	return 0;
}