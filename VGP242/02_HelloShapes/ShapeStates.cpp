#include "ShapeStates.h"

using namespace BongoEngine;
using namespace BongoEngine::Graphics;

void ShapesState::Initialize()
{
	// create shape
	CreateShape();

	auto device = GraphicsSystem::Get()->GetDevice();

	// create a  buffer to store the vertices
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size()) * sizeof(Vertex);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = mVertices.data();
	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	ASSERT(SUCCEEDED(hr), "ShapesState: Failed to create vertex buffer");

	//==================================================================

	// Bind the shader file functions to the appropiate shader obj
	// vertex shader
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";
}

void ShapesState::Terminate()
{
}

void ShapesState::Update(float deltaTime)
{
}

void ShapesState::Render()
{
}

void ShapesState::CreateShape()
{
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f} });
	mVertices.push_back({ {0.0f, 0.5f, 0.0f} });
	mVertices.push_back({ {0.5f, -0.5f, 0.0f} });
}

