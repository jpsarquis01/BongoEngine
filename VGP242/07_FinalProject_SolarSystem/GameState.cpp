#include "GameState.h"
#include <cstdlib>
#include <cmath>

using namespace BongoEngine;
using namespace BongoEngine::Graphics;
using namespace BongoEngine::Input;

// imgui speed controls 
float gOrbitalRotationSpeed = 0.0f;
float gRotationSpeed = 0.0f;

// gives a random tilt angle for "Random mode"
static float RandomTilt()
{
	return ((rand() % 360) - 180) * 0.01745329f;
}

static void DrawCircle(float radius, const Math::Matrix4& matrix, const Color& color)
{
	const int slices = 60;
	for (int i = 0; i < slices; ++i)
	{
		float a0 = (i / (float)slices) * 6.2831853f;
		float a1 = ((i + 1) / (float)slices) * 6.2831853f;
		Math::Vector3 p0 = Math::TransformCoord({ radius * sinf(a0), 0.0f, radius * cosf(a0) }, matrix);
		Math::Vector3 p1 = Math::TransformCoord({ radius * sinf(a1), 0.0f, radius * cosf(a1) }, matrix);
		SimpleDraw::AddLine(p0, p1, color);
	}
}

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 8.0f, -25.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	Graphics::MeshPX skysphere = MeshBuilder::CreateSkySpherePX(100, 100, 200.0f);
	mSkyboxMeshBuffer.Initialize(skysphere);
	mSkyboxTextureId = TextureManager::Get()->LoadTexture("skysphere/space.jpg");

	// make all the spheres/planets
	Graphics::MeshPX sun = MeshBuilder::CreateSpherePX(30, 30, 1.5f);
	mSunMeshBuffer.Initialize(sun);

	Graphics::MeshPX mercury = MeshBuilder::CreateSpherePX(30, 30, 0.15f);
	mMercuryMeshBuffer.Initialize(mercury);

	Graphics::MeshPX venus = MeshBuilder::CreateSpherePX(30, 30, 0.25f);
	mVenusMeshBuffer.Initialize(venus);

	Graphics::MeshPX earth = MeshBuilder::CreateSpherePX(30, 30, 0.3f);
	mEarthMeshBuffer.Initialize(earth);

	Graphics::MeshPX moon = MeshBuilder::CreateSpherePX(30, 30, 0.1f);
	mMoonMeshBuffer.Initialize(moon);

	Graphics::MeshPX mars = MeshBuilder::CreateSpherePX(30, 30, 0.22f);
	mMarsMeshBuffer.Initialize(mars);

	Graphics::MeshPX jupiter = MeshBuilder::CreateSpherePX(30, 30, 0.7f);
	mJupiterMeshBuffer.Initialize(jupiter);

	Graphics::MeshPX saturn = MeshBuilder::CreateSpherePX(30, 30, 0.6f);
	mSaturnMeshBuffer.Initialize(saturn);

	Graphics::MeshPX uranus = MeshBuilder::CreateSpherePX(30, 30, 0.45f);
	mUranusMeshBuffer.Initialize(uranus);

	Graphics::MeshPX neptune = MeshBuilder::CreateSpherePX(30, 30, 0.43f);
	mNeptuneMeshBuffer.Initialize(neptune);

	Graphics::MeshPX pluto = MeshBuilder::CreateSpherePX(30, 30, 0.12f);
	mPlutoMeshBuffer.Initialize(pluto);

	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderPath);
	mPixelShader.Initialize(shaderPath);
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	// load all the textures
	mSunTextureId = TextureManager::Get()->LoadTexture("planets/sun.jpg");
	mMercuryTextureId = TextureManager::Get()->LoadTexture("planets/mercury.jpg");
	mVenusTextureId = TextureManager::Get()->LoadTexture("planets/venus.jpg");
	mEarthTextureId = TextureManager::Get()->LoadTexture("earth.jpg");
	mMoonTextureId = TextureManager::Get()->LoadTexture("earth.jpg");
	mMarsTextureId = TextureManager::Get()->LoadTexture("planets/mars.jpg");
	mJupiterTextureId = TextureManager::Get()->LoadTexture("planets/jupiter.jpg");
	mSaturnTextureId = TextureManager::Get()->LoadTexture("planets/saturn.jpg");
	mUranusTextureId = TextureManager::Get()->LoadTexture("planets/uranus.jpg");
	mNeptuneTextureId = TextureManager::Get()->LoadTexture("planets/neptune.jpg");
	mPlutoTextureId = TextureManager::Get()->LoadTexture("planets/pluto.jpg");

	// how far each planet is from the sun
	mMoonOrbitDistance = 0.6f; // moon distance from the earth
	mMercuryOrbitDistance = 3.0f;
	mVenusOrbitDistance = 4.0f;
	mEarthOrbitDistance = 5.5f;
	mMarsOrbitDistance = 7.0f;
	mJupiterOrbitDistance = 9.5f;
	mSaturnOrbitDistance = 12.0f;
	mUranusOrbitDistance = 14.5f;
	mNeptuneOrbitDistance = 16.5f;
	mPlutoOrbitDistance = 18.5f;
}

void GameState::Terminate()
{
	TextureManager::Get()->ReleaseTexture(mPlutoTextureId);
	TextureManager::Get()->ReleaseTexture(mNeptuneTextureId);
	TextureManager::Get()->ReleaseTexture(mUranusTextureId);
	TextureManager::Get()->ReleaseTexture(mSaturnTextureId);
	TextureManager::Get()->ReleaseTexture(mJupiterTextureId);
	TextureManager::Get()->ReleaseTexture(mMarsTextureId);
	TextureManager::Get()->ReleaseTexture(mEarthTextureId);
	TextureManager::Get()->ReleaseTexture(mMoonTextureId);
	TextureManager::Get()->ReleaseTexture(mVenusTextureId);
	TextureManager::Get()->ReleaseTexture(mMercuryTextureId);
	TextureManager::Get()->ReleaseTexture(mSunTextureId);
	TextureManager::Get()->ReleaseTexture(mSkyboxTextureId);

	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();

	mPlutoMeshBuffer.Terminate();
	mNeptuneMeshBuffer.Terminate();
	mUranusMeshBuffer.Terminate();
	mSaturnMeshBuffer.Terminate();
	mJupiterMeshBuffer.Terminate();
	mMarsMeshBuffer.Terminate();
	mEarthMeshBuffer.Terminate();
	mMoonMeshBuffer.Terminate();
	mVenusMeshBuffer.Terminate();
	mMercuryMeshBuffer.Terminate();
	mSunMeshBuffer.Terminate();
	mSkyboxMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	// gRotationSpeed = how fast they spin, gOrbitalRotationSpeed = how fast they go around the sun
	mSunRotation += (0.1f + gRotationSpeed) * deltaTime;

	// the closer planets go faster
	mMercuryRotation += (0.8f + gRotationSpeed) * deltaTime;
	mMercuryOrbitRotation += (0.5f + gOrbitalRotationSpeed) * deltaTime;

	mVenusRotation += (0.6f + gRotationSpeed) * deltaTime;
	mVenusOrbitRotation += (0.35f + gOrbitalRotationSpeed) * deltaTime;

	mEarthRotation += (0.5f + gRotationSpeed) * deltaTime;
	mEarthOrbitRotation += (0.2f + gOrbitalRotationSpeed) * deltaTime;

	mMoonRotation += (0.5f + gRotationSpeed) * deltaTime;
	mMoonOrbitRotation += (1.0f + gOrbitalRotationSpeed) * deltaTime;

	mMarsRotation += (0.5f + gRotationSpeed) * deltaTime;
	mMarsOrbitRotation += (0.16f + gOrbitalRotationSpeed) * deltaTime;

	mJupiterRotation += (1.0f + gRotationSpeed) * deltaTime;
	mJupiterOrbitRotation += (0.1f + gOrbitalRotationSpeed) * deltaTime;

	mSaturnRotation += (0.9f + gRotationSpeed) * deltaTime;
	mSaturnOrbitRotation += (0.08f + gOrbitalRotationSpeed) * deltaTime;

	mUranusRotation += (0.7f + gRotationSpeed) * deltaTime;
	mUranusOrbitRotation += (0.06f + gOrbitalRotationSpeed) * deltaTime;

	mNeptuneRotation += (0.7f + gRotationSpeed) * deltaTime;
	mNeptuneOrbitRotation += (0.05f + gOrbitalRotationSpeed) * deltaTime;

	mPlutoRotation += (0.4f + gRotationSpeed) * deltaTime;
	mPlutoOrbitRotation += (0.04f + gOrbitalRotationSpeed) * deltaTime;

	// follow the planet picked in the Camera menu
	if (mCameraTarget == 0)
	{
		UpdateCamera(deltaTime);
	}
	else
	{
		Math::Matrix4 world = Math::Matrix4::Identity;
		if (mCameraTarget == 1) world = Math::Matrix4::RotationY(mMercuryRotation) * Math::Matrix4::Translation(mMercuryOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mMercuryOrbitRotation) * Math::Matrix4::RotationX(mMercuryTiltX) * Math::Matrix4::RotationZ(mMercuryTiltZ);
		if (mCameraTarget == 2) world = Math::Matrix4::RotationY(mVenusRotation) * Math::Matrix4::Translation(mVenusOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mVenusOrbitRotation) * Math::Matrix4::RotationX(mVenusTiltX) * Math::Matrix4::RotationZ(mVenusTiltZ);
		if (mCameraTarget == 3) world = Math::Matrix4::RotationY(mEarthRotation) * Math::Matrix4::Translation(mEarthOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mEarthOrbitRotation) * Math::Matrix4::RotationX(mEarthTiltX) * Math::Matrix4::RotationZ(mEarthTiltZ);
		if (mCameraTarget == 4) world = Math::Matrix4::RotationY(mMarsRotation) * Math::Matrix4::Translation(mMarsOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mMarsOrbitRotation) * Math::Matrix4::RotationX(mMarsTiltX) * Math::Matrix4::RotationZ(mMarsTiltZ);
		if (mCameraTarget == 5) world = Math::Matrix4::RotationY(mJupiterRotation) * Math::Matrix4::Translation(mJupiterOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mJupiterOrbitRotation) * Math::Matrix4::RotationX(mJupiterTiltX) * Math::Matrix4::RotationZ(mJupiterTiltZ);
		if (mCameraTarget == 6) world = Math::Matrix4::RotationY(mSaturnRotation) * Math::Matrix4::Translation(mSaturnOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mSaturnOrbitRotation) * Math::Matrix4::RotationX(mSaturnTiltX) * Math::Matrix4::RotationZ(mSaturnTiltZ);
		if (mCameraTarget == 7) world = Math::Matrix4::RotationY(mUranusRotation) * Math::Matrix4::Translation(mUranusOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mUranusOrbitRotation) * Math::Matrix4::RotationX(mUranusTiltX) * Math::Matrix4::RotationZ(mUranusTiltZ);
		if (mCameraTarget == 8) world = Math::Matrix4::RotationY(mNeptuneRotation) * Math::Matrix4::Translation(mNeptuneOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mNeptuneOrbitRotation) * Math::Matrix4::RotationX(mNeptuneTiltX) * Math::Matrix4::RotationZ(mNeptuneTiltZ);
		if (mCameraTarget == 9) world = Math::Matrix4::RotationY(mPlutoRotation) * Math::Matrix4::Translation(mPlutoOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mPlutoOrbitRotation) * Math::Matrix4::RotationX(mPlutoTiltX) * Math::Matrix4::RotationZ(mPlutoTiltZ);
		if (mCameraTarget == 10) world = Math::Matrix4::RotationY(mMoonRotation) * Math::Matrix4::Translation(mMoonOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mMoonOrbitRotation) * Math::Matrix4::RotationX(mMoonTiltX) * Math::Matrix4::RotationZ(mMoonTiltZ);;

		Math::Vector3 planetPos = Math::GetTranslation(world);
		const Math::Vector3 offset = { 2.0f, 3.0f, 0.0f };
		mCamera.SetPosition(planetPos + offset);
		mCamera.SetLookAt(planetPos);
	}
}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mConstantBuffer.BindVS(0);
	mSampler.BindPS(0);

	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	Math::Matrix4 sunMatWorld = Math::Matrix4::RotationY(mSunRotation);
	Math::Matrix4 mercuryMatWorld = Math::Matrix4::RotationY(mMercuryRotation) * Math::Matrix4::Translation(mMercuryOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mMercuryOrbitRotation) * Math::Matrix4::RotationX(mMercuryTiltX) * Math::Matrix4::RotationZ(mMercuryTiltZ);
	Math::Matrix4 venusMatWorld = Math::Matrix4::RotationY(mVenusRotation) * Math::Matrix4::Translation(mVenusOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mVenusOrbitRotation) * Math::Matrix4::RotationX(mVenusTiltX) * Math::Matrix4::RotationZ(mVenusTiltZ);
	Math::Matrix4 earthMatWorld = Math::Matrix4::RotationY(mEarthRotation) * Math::Matrix4::Translation(mEarthOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mEarthOrbitRotation) * Math::Matrix4::RotationX(mEarthTiltX) * Math::Matrix4::RotationZ(mEarthTiltZ);
	Math::Vector3 earthPos = Math::GetTranslation(earthMatWorld);
	Math::Matrix4 moonMatWorld = Math::Matrix4::RotationY(mMoonRotation) * Math::Matrix4::Translation(mMoonOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mMoonOrbitRotation) * Math::Matrix4::Translation(earthPos);
	Math::Matrix4 marsMatWorld = Math::Matrix4::RotationY(mMarsRotation) * Math::Matrix4::Translation(mMarsOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mMarsOrbitRotation) * Math::Matrix4::RotationX(mMarsTiltX) * Math::Matrix4::RotationZ(mMarsTiltZ);
	Math::Matrix4 jupiterMatWorld = Math::Matrix4::RotationY(mJupiterRotation) * Math::Matrix4::Translation(mJupiterOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mJupiterOrbitRotation) * Math::Matrix4::RotationX(mJupiterTiltX) * Math::Matrix4::RotationZ(mJupiterTiltZ);
	Math::Matrix4 saturnMatWorld = Math::Matrix4::RotationY(mSaturnRotation) * Math::Matrix4::Translation(mSaturnOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mSaturnOrbitRotation) * Math::Matrix4::RotationX(mSaturnTiltX) * Math::Matrix4::RotationZ(mSaturnTiltZ);
	Math::Matrix4 uranusMatWorld = Math::Matrix4::RotationY(mUranusRotation) * Math::Matrix4::Translation(mUranusOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mUranusOrbitRotation) * Math::Matrix4::RotationX(mUranusTiltX) * Math::Matrix4::RotationZ(mUranusTiltZ);
	Math::Matrix4 neptuneMatWorld = Math::Matrix4::RotationY(mNeptuneRotation) * Math::Matrix4::Translation(mNeptuneOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mNeptuneOrbitRotation) * Math::Matrix4::RotationX(mNeptuneTiltX) * Math::Matrix4::RotationZ(mNeptuneTiltZ);
	Math::Matrix4 plutoMatWorld = Math::Matrix4::RotationY(mPlutoRotation) * Math::Matrix4::Translation(mPlutoOrbitDistance, 0.0f, 0.0f) * Math::Matrix4::RotationY(mPlutoOrbitRotation) * Math::Matrix4::RotationX(mPlutoTiltX) * Math::Matrix4::RotationZ(mPlutoTiltZ);

	// sun
	Math::Matrix4 wvp = sunMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mSunTextureId, 0);
	mSunMeshBuffer.Render();

	// mercury
	wvp = mercuryMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mMercuryTextureId, 0);
	mMercuryMeshBuffer.Render();

	// venus
	wvp = venusMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mVenusTextureId, 0);
	mVenusMeshBuffer.Render();

	// earth
	wvp = earthMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mEarthTextureId, 0);
	mEarthMeshBuffer.Render();

	// moon, orbits around the earth
	wvp = moonMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mMoonTextureId, 0);
	mMoonMeshBuffer.Render();

	// mars
	wvp = marsMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mMarsTextureId, 0);
	mMarsMeshBuffer.Render();

	// jupiter
	wvp = jupiterMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mJupiterTextureId, 0);
	mJupiterMeshBuffer.Render();

	// saturn
	wvp = saturnMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mSaturnTextureId, 0);
	mSaturnMeshBuffer.Render();

	// saturn rings
	if (mShowSaturnRings)
	{
		Math::Matrix4 ringMat = Math::Matrix4::RotationX(mSaturnTiltX) * Math::Matrix4::RotationZ(mSaturnTiltZ) * Math::Matrix4::Translation(Math::GetTranslation(saturnMatWorld));
		DrawCircle(0.8f, ringMat, Colors::Khaki);
		DrawCircle(0.9f, ringMat, Colors::Gold);
		DrawCircle(1.0f, ringMat, Colors::Khaki);
	}

	// uranus
	wvp = uranusMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mUranusTextureId, 0);
	mUranusMeshBuffer.Render();

	// neptune
	wvp = neptuneMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mNeptuneTextureId, 0);
	mNeptuneMeshBuffer.Render();

	// pluto
	wvp = plutoMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mPlutoTextureId, 0);
	mPlutoMeshBuffer.Render();

	// Skybox
	Math::Matrix4 skyWorld = Math::Matrix4::Identity;
	Math::Matrix4 skyWvp = Math::Transpose(skyWorld * matView * matProj);
	mConstantBuffer.Update(&skyWvp);
	TextureManager::Get()->BindPS(mSkyboxTextureId, 0);
	mSkyboxMeshBuffer.Render();


	// orbit lines 
	DrawCircle(mMercuryOrbitDistance, Math::Matrix4::RotationX(mMercuryTiltX) * Math::Matrix4::RotationZ(mMercuryTiltZ), Colors::DarkGray);
	DrawCircle(mVenusOrbitDistance, Math::Matrix4::RotationX(mVenusTiltX) * Math::Matrix4::RotationZ(mVenusTiltZ), Colors::DarkGray);
	DrawCircle(mEarthOrbitDistance, Math::Matrix4::RotationX(mEarthTiltX) * Math::Matrix4::RotationZ(mEarthTiltZ), Colors::DarkGray);
	DrawCircle(mMarsOrbitDistance, Math::Matrix4::RotationX(mMarsTiltX) * Math::Matrix4::RotationZ(mMarsTiltZ), Colors::DarkGray);
	DrawCircle(mJupiterOrbitDistance, Math::Matrix4::RotationX(mJupiterTiltX) * Math::Matrix4::RotationZ(mJupiterTiltZ), Colors::DarkGray);
	DrawCircle(mSaturnOrbitDistance, Math::Matrix4::RotationX(mSaturnTiltX) * Math::Matrix4::RotationZ(mSaturnTiltZ), Colors::DarkGray);
	DrawCircle(mUranusOrbitDistance, Math::Matrix4::RotationX(mUranusTiltX) * Math::Matrix4::RotationZ(mUranusTiltZ), Colors::DarkGray);
	DrawCircle(mNeptuneOrbitDistance, Math::Matrix4::RotationX(mNeptuneTiltX) * Math::Matrix4::RotationZ(mNeptuneTiltZ), Colors::DarkGray);
	DrawCircle(mPlutoOrbitDistance, Math::Matrix4::RotationX(mPlutoTiltX) * Math::Matrix4::RotationZ(mPlutoTiltZ), Colors::DarkGray);

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Random Mode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	// give every planet a random tilt so the orbits
	if (ImGui::Checkbox("Random Mode", &mRandomMode))
	{
		if (mRandomMode)
		{
			mMercuryTiltX = RandomTilt();	mMercuryTiltZ = RandomTilt();
			mVenusTiltX = RandomTilt();		mVenusTiltZ = RandomTilt();
			mEarthTiltX = RandomTilt();		mEarthTiltZ = RandomTilt();
			mMarsTiltX = RandomTilt();		mMarsTiltZ = RandomTilt();
			mJupiterTiltX = RandomTilt();	mJupiterTiltZ = RandomTilt();
			mSaturnTiltX = RandomTilt();	mSaturnTiltZ = RandomTilt();
			mUranusTiltX = RandomTilt();	mUranusTiltZ = RandomTilt();
			mNeptuneTiltX = RandomTilt();	mNeptuneTiltZ = RandomTilt();
			mPlutoTiltX = RandomTilt();		mPlutoTiltZ = RandomTilt();
		}
		else
		{
			mMercuryTiltX = 0.0f;	mMercuryTiltZ = 0.0f;
			mVenusTiltX = 0.0f;		mVenusTiltZ = 0.0f;
			mEarthTiltX = 0.0f;		mEarthTiltZ = 0.0f;
			mMarsTiltX = 0.0f;		mMarsTiltZ = 0.0f;
			mJupiterTiltX = 0.0f;	mJupiterTiltZ = 0.0f;
			mSaturnTiltX = 0.0f;	mSaturnTiltZ = 0.0f;
			mUranusTiltX = 0.0f;	mUranusTiltZ = 0.0f;
			mNeptuneTiltX = 0.0f;	mNeptuneTiltZ = 0.0f;
			mPlutoTiltX = 0.0f;		mPlutoTiltZ = 0.0f;
		}
	}
	ImGui::End();

	ImGui::Begin("Saturn Rings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Show Saturn Rings", &mShowSaturnRings);
	ImGui::End();

	// pick which planet the camera follows 
	ImGui::Begin("Camera", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::RadioButton("Free Camera", &mCameraTarget, 0);
	ImGui::RadioButton("Mercury", &mCameraTarget, 1);
	ImGui::RadioButton("Venus", &mCameraTarget, 2);
	ImGui::RadioButton("Earth", &mCameraTarget, 3);
	ImGui::RadioButton("Mars", &mCameraTarget, 4);
	ImGui::RadioButton("Jupiter", &mCameraTarget, 5);
	ImGui::RadioButton("Saturn", &mCameraTarget, 6);
	ImGui::RadioButton("Uranus", &mCameraTarget, 7);
	ImGui::RadioButton("Neptune", &mCameraTarget, 8);
	ImGui::RadioButton("Pluto", &mCameraTarget, 9);
	ImGui::End();

	// make planets go faster or slower
	ImGui::Begin("Speed", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SliderFloat("Orbital Speed", &gOrbitalRotationSpeed, -0.5f, 0.5f);
	ImGui::SliderFloat("Rotation Speed", &gRotationSpeed, -0.5f, 0.5f);
	ImGui::End();
}

void GameState::UpdateCamera(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}
