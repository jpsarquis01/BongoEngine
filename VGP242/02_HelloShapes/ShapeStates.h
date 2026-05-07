#pragma once
#include <BongoEngine/Inc/BongoEngine.h>

class ShapesState : public BongoEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();

	// data tocreate an obj
	struct Vertex
	{
		BongoEngine::Math::Vector3 position;
		BongoEngine::Graphics::Color color;
	};
	using Vertices = std::vector<BongoEngine::Graphics::VertexPC>;
	Vertices mVertices;

	//// info to pass  to the graphics card
	//// stores the data from the shape
	//ID3D11Buffer* mVertexBuffer = nullptr;
	//// what functions are called on the shader file
	//ID3D11VertexShader* mVertexShader = nullptr;
	//// what data am i expecting on the shader (position, color, texture, etc...)
	//ID3D11InputLayout* mInputLayout = nullptr;
	//// what function are called on the shader file per pixel
	//ID3D11PixelShader* mPixelShader = nullptr;

	BongoEngine::Graphics::MeshBuffer mMeshBuffer;
	BongoEngine::Graphics::VertexShader mVertexShader;
	BongoEngine::Graphics::PixelShader mPixelShader;

};

class QuadState : public ShapesState
{
public:
	void Update(float deltaTime) override;

protected:
	void CreateShape() override;
};

class HouseState : public ShapesState
{
public:
	void Update(float deltaTime) override;
protected:
	void CreateShape() override;
};