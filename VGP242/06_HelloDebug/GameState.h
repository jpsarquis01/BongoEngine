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

	// Skybox
	BongoEngine::Graphics::TextureId mSkyboxTextureId;
	BongoEngine::Graphics::MeshBuffer mSkyboxMeshBuffer;

	// Planets
	BongoEngine::Graphics::TextureId mSunTextureId;
	BongoEngine::Graphics::TextureId mMercuryTextureId;
	BongoEngine::Graphics::TextureId mVenusTextureId;
	BongoEngine::Graphics::TextureId mEarthTextureId;
	BongoEngine::Graphics::TextureId mMarsTextureId;
	BongoEngine::Graphics::TextureId mJupiterTextureId;
	BongoEngine::Graphics::TextureId mSaturnTextureId;
	BongoEngine::Graphics::TextureId mUranusTextureId;
	BongoEngine::Graphics::TextureId mNeptuneTextureId;
	BongoEngine::Graphics::TextureId mPlutoTextureId;

	BongoEngine::Graphics::MeshBuffer mSunMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mMercuryMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mVenusMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mEarthMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mMarsMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mJupiterMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mSaturnMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mUranusMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mNeptuneMeshBuffer;
	BongoEngine::Graphics::MeshBuffer mPlutoMeshBuffer;

	float mSunRotation = 0.0f;

	float mMercuryRotation = 0.0f;
	float mMercuryOrbitRotation = 0.0f;
	float mMercuryOrbitDistance = 0.0f;

	float mVenusRotation = 0.0f;
	float mVenusOrbitRotation = 0.0f;
	float mVenusOrbitDistance = 0.0f;

	float mEarthRotation = 0.0f;
	float mEarthOrbitRotation = 0.0f;
	float mEarthOrbitDistance = 0.0f;

	float mMarsRotation = 0.0f;
	float mMarsOrbitRotation = 0.0f;
	float mMarsOrbitDistance = 0.0f;

	float mJupiterRotation = 0.0f;
	float mJupiterOrbitRotation = 0.0f;
	float mJupiterOrbitDistance = 0.0f;

	float mSaturnRotation = 0.0f;
	float mSaturnOrbitRotation = 0.0f;
	float mSaturnOrbitDistance = 0.0f;

	float mUranusRotation = 0.0f;
	float mUranusOrbitRotation = 0.0f;
	float mUranusOrbitDistance = 0.0f;

	float mNeptuneRotation = 0.0f;
	float mNeptuneOrbitRotation = 0.0f;
	float mNeptuneOrbitDistance = 0.0f;

	float mPlutoRotation = 0.0f;
	float mPlutoOrbitRotation = 0.0f;
	float mPlutoOrbitDistance = 0.0f;

	// random mode tilts the orbit 
	bool mRandomMode = false;
	bool mShowSaturnRings = false;

	// camera follows the picked planet
	int mCameraTarget = 0;

	float mMercuryTiltX = 0.0f;
	float mMercuryTiltZ = 0.0f;
	float mVenusTiltX = 0.0f;
	float mVenusTiltZ = 0.0f;
	float mEarthTiltX = 0.0f;
	float mEarthTiltZ = 0.0f;
	float mMarsTiltX = 0.0f;
	float mMarsTiltZ = 0.0f;
	float mJupiterTiltX = 0.0f;
	float mJupiterTiltZ = 0.0f;
	float mSaturnTiltX = 0.0f;
	float mSaturnTiltZ = 0.0f;
	float mUranusTiltX = 0.0f;
	float mUranusTiltZ = 0.0f;
	float mNeptuneTiltX = 0.0f;
	float mNeptuneTiltZ = 0.0f;
	float mPlutoTiltX = 0.0f;
	float mPlutoTiltZ = 0.0f;

	BongoEngine::Graphics::VertexShader mVertexShader;
	BongoEngine::Graphics::PixelShader mPixelShader;
	BongoEngine::Graphics::Sampler mSampler;

	BongoEngine::Graphics::Camera mCamera;
	BongoEngine::Graphics::ConstantBuffer mConstantBuffer;

	// Moon 
	float mMoonOrbitAngle = 0.0f;
};
