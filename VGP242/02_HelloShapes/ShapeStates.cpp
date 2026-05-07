#include "ShapeStates.h"

using namespace BongoEngine;
using namespace BongoEngine::Graphics;
using namespace BongoEngine::Input;

void ShapesState::Initialize()
{
	// create shape
	CreateShape();
	mMeshBuffer.Initialize(mVertices.data(), sizeof(VertexPC), mVertices.size());

	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoColor.fx";
	mVertexShader.Initialize<VertexPC>(shaderPath);
	mPixelShader.Initialize(shaderPath);
}

void ShapesState::Terminate()
{
	mVertices.clear();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void ShapesState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::UP))
	{
		MainApp().ChangeState("HouseState");
	}
}

void ShapesState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mMeshBuffer.Render();
}

void ShapesState::CreateShape()
{
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Red  } });
	mVertices.push_back({ { 0.0f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Green} });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Blue } });
}

void QuadState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::LEFT))
	{
		MainApp().ChangeState("ShapeState");
	}
}

void HouseState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("QuadState");
	}
}

void QuadState::CreateShape()
{
	// Every 3 vertices is a triangle
	// Vertices are clockwiase (otherwise normal is away form camera)
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Red  } });
	mVertices.push_back({ {-0.5f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Green} });
	mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Blue } });

	// Second Triangle
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Red  } });
	mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Blue} });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Green } });
}

void HouseState::CreateShape()
{
	// First Traingle
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Red  } });
	mVertices.push_back({ {-0.5f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Green} });
	mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Blue } });

	// Second Triangle
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Red  } });
	mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Blue} });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Green } });

	// Third Triangle
	mVertices.push_back({ {-0.5f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Red  } });
	mVertices.push_back({ { 0.0f,  1.0f, 0.0f}, {BongoEngine::Graphics::Colors::Blue} });
	mVertices.push_back({ { 0.5f,  0.5f, 0.0f}, {BongoEngine::Graphics::Colors::Green } });
}

