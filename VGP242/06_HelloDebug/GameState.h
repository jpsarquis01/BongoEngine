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

	BongoEngine::Graphics::TextureId mEarthTextureId;
	BongoEngine::Graphics::TextureId mSunTextureId;
	 
	BongoEngine::Graphics::MeshBuffer mEarthMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mSunMeshBuffer;

	float mEarthRotation = 0.0f;
	float mEarthOrbitRotation = 0.0f;
	float mEarthOrbitDistance = 0.0f;

	BongoEngine::Graphics::VertexShader mVertexShader;
	BongoEngine::Graphics::PixelShader mPixelShader;
	BongoEngine::Graphics::Sampler mSampler;
	 
	BongoEngine::Graphics::Camera mCamera;
	BongoEngine::Graphics::ConstantBuffer mConstantBuffer;
};
