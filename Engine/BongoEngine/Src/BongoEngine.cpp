#include "Precompiled.h"
#include "BongoEngine.h"

BongoEngine::App& BongoEngine::MainApp()
{
	static App sApp;
	return sApp;
}