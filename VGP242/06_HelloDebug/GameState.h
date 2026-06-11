#pragma once
#include <BongoEngine/Inc/BongoEngine.h>

class GameState : public BongoEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	void UpdateCamera(float deltaTime);

	BongoEngine::Graphics::Camera mCamera;
};
