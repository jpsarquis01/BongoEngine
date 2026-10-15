#include "GameState.h"
#include <cstdlib>
#include <cmath>

using namespace BongoEngine;
using namespace BongoEngine::Graphics;
using namespace BongoEngine::Input;

void GameState::Initialize()
{
	// Setup camera
	mCamera.SetPosition({ 0.0f, 8.0f, -15.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// Setup directional light
	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f,0.8f, 0.8f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	// Setup render object
	Mesh mesh = MeshBuilder::CreateSphere(20, 20, 1.0f);
	mRenderObject.meshBuffer.Initialize(mesh);
	TextureManager* tm = TextureManager::Get();
	mRenderObject.diffuseMapId = tm->LoadTexture("earth.jpg");
	mRenderObject.specMapId = tm->LoadTexture("earth_spec.jpg");
	mRenderObject.normMapId = tm->LoadTexture("earth_normal.jpg");
	mRenderObject.bumpMapId = tm->LoadTexture("earth_bump.jpg");

	// Setup Effect
	std::filesystem::path shaderPath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderPath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	// Setup Effect Cel
	shaderPath = L"../../Assets/Shaders/CelShader.fx";
	mStandardEffectCel.Initialize(shaderPath);
	mStandardEffectCel.SetCamera(mCamera);
	mStandardEffectCel.SetDirectionalLight(mDirectionalLight);
}

void GameState::Terminate()
{
	mStandardEffectCel.Terminate();
	mStandardEffect.Terminate();
	mRenderObject.Terminate();
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}

void GameState::Render()
{
	SimpleDraw::AddGroundPlane(25, Colors::Gray);
	SimpleDraw::Render(mCamera);	

	if (mUseCelShading)
	{
		mStandardEffectCel.Begin();
			mStandardEffectCel.Render(mRenderObject);
		mStandardEffectCel.End();
	}
	else
	{
		mStandardEffect.Begin();
			mStandardEffect.Render(mRenderObject);
		mStandardEffect.End();
	}
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
		{
			mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
		}
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Emissive##Material", &mRenderObject.material.emissive.r);
		ImGui::ColorEdit4("Ambient##Material", &mRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##Material", &mRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##Material", &mRenderObject.material.specular.r);
		ImGui::DragFloat("Shininess##Material", &mRenderObject.material.shinines, 0.01f, 0.0f, 1000.0f);
	}

	ImGui::Checkbox("UseCelShader", &mUseCelShading);
	if (mUseCelShading)
	{
		mStandardEffectCel.DebugUI();
	}
	else
	{
		mStandardEffect.DebugUI();
	}

	mStandardEffect.DebugUI();
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
