#pragma once
#include <BongoEngine/Inc/BongoEngine.h>

class ShapesState : public BongoEngine::AppState
{
public:
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();

	BongoEngine::Graphics::TextureId mTextureId;
	BongoEngine::Graphics::MeshPX mMesh;
	
	BongoEngine::Graphics::MeshBuffer mMeshBuffer;
	BongoEngine::Graphics::VertexShader mVertexShader;
	BongoEngine::Graphics::PixelShader mPixelShader;
	BongoEngine::Graphics::Sampler mSampler;
	
	BongoEngine::Graphics::Camera mCamera;
	BongoEngine::Graphics::ConstantBuffer mConstantBuffer;
};

