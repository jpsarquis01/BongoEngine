#include <BongoEngine/Inc/BongoEngine.h>
#include "ShapeStates.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	BongoEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	BongoEngine::App& myApp = BongoEngine::MainApp();

	// need states
	myApp.AddState<ShapesState>("ShapeState");
	myApp.Run(config);

	return 0;
}