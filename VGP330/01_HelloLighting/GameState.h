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

	// added in assignment 1 
	BongoEngine::Graphics::RenderObject mRenderBall;
	BongoEngine::Graphics::RenderObject mRenderPlane;

private:
	void UpdateCamera(float deltaTime);

	BongoEngine::Graphics::Camera mCamera;
	BongoEngine::Graphics::DirectionalLight mDirectionalLight;
	BongoEngine::Graphics::StandardEffect mStandardEffect;
	BongoEngine::Graphics::StandardEffect mStandardEffectCel;

	BongoEngine::Graphics::RenderTarget mRenderTarget;

	BongoEngine::Graphics::RenderObject mRenderObject;
	bool mUseCelShading = false;
};
