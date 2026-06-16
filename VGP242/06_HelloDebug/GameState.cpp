#include "GameState.h"

using namespace BongoEngine;
using namespace BongoEngine::Graphics;
using namespace BongoEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// create shape
	Graphics::MeshPX sun = MeshBuilder::CreateSpherePX(30, 30, 1.0f);
	mSunMeshBuffer.Initialize(sun);

	Graphics::MeshPX earth = MeshBuilder::CreateSpherePX(30, 30, 0.5f);
	mEarthMeshBuffer.Initialize(earth);

	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderPath);
	mPixelShader.Initialize(shaderPath);
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	mEarthTextureId = TextureManager::Get()->LoadTexture("earth.jpg");
	mSunTextureId = TextureManager::Get()->LoadTexture("planets/sun.jpg");

	mEarthOrbitDistance = 4.0f;
}

void GameState::Terminate()
{
	TextureManager::Get()->ReleaseTexture(mSunTextureId);
	TextureManager::Get()->ReleaseTexture(mEarthTextureId);
	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mEarthMeshBuffer.Terminate();
	mSunMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	// Rotate speed
	const float earthRotationSpeed = 0.5f;
	const float earthOrbitRotationSpeed = 0.2f;
	mEarthRotation += earthRotationSpeed * deltaTime;
	mEarthOrbitRotation += earthOrbitRotationSpeed * deltaTime;
}

void GameState::Render()
{
	// Make Camera follow planets
	//Math::Matrix4 earthMatRot = Math::Matrix4::RotationY(mEarthRotation);
	//Math::Matrix4 earthMatTrans = Math::Matrix4::Translation(mEarthOrbitDistance, 0.0f, 0.0f);
	//Math::Matrix4 earthMatOrbitRot = Math::Matrix4::RotationY(mEarthOrbitRotation);
	//Math::Matrix4 earthMatWorld = earthMatRot * earthMatTrans * earthMatOrbitRot;
	//Math::Vector3 position = Math::GetTranslation(earthMatWorld);
	//const Math::Vector3 offset = { 2.0f, 3.0f, 0.0f };
	//mCamera.SetPosition(position + offset);
	//mCamera.SetLookAt(position);

	// ---------------------------------------------------------------------

	// prepare the GPU
	mVertexShader.Bind();
	mPixelShader.Bind();

	// sync buffer information
	mConstantBuffer.BindVS(0);
	mSampler.BindPS(0);

	// update buffer data
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	// render sun
	Math::Matrix4 matWorld = Math::Matrix4::Identity;
	Math::Matrix4 wvp = matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	// assign textures
	TextureManager::Get()->BindPS(mSunTextureId, 0);
	mSunMeshBuffer.Render();

	// render Earth
	Math::Matrix4 earthMatRot = Math::Matrix4::RotationY(mEarthRotation);
	Math::Matrix4 earthMatTrans = Math::Matrix4::Translation(mEarthOrbitDistance, 0.0f, 0.0f);
	Math::Matrix4 earthMatOrbitRot = Math::Matrix4::RotationY(mEarthOrbitRotation);
	Math::Matrix4 earthMatWorld = earthMatRot * earthMatTrans * earthMatOrbitRot;
	wvp = earthMatWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	// assign textures
	TextureManager::Get()->BindPS(mEarthTextureId, 0);

	// render obj
	mEarthMeshBuffer.Render();

	// render orbit lines
	SimpleDraw::AddGroundCircle(20, mEarthOrbitDistance, Math::Vector3::Zero, Colors::White);

	SimpleDraw::Render(mCamera);
}


	void GameState::DebugUI()
	{
		ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
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