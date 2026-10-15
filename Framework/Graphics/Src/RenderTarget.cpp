#include "Precompiled.h"
#include "RenderTarget.h"
#include "GraphicsSystem.h"

using namespace BongoEngine;
using namespace BongoEngine::Graphics;

namespace
{
	DXGI_FORMAT GetDXGIFormat(RenderTarget::Format format)
	{
		switch (format)
		{
		case RenderTarget::Format::RGBA_U8: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case RenderTarget::Format::RGBA_U32: return DXGI_FORMAT_R32G32B32A32_UINT;
		default:
			ASSERT(false, "RenderTarget: unknown format");
			break;
		}
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	}
}

RenderTarget::~RenderTarget()
{
	ASSERT(mRenderTargetView == nullptr && mDepthStencilView == nullptr, "RenderTarget: must be terminated");
}

RenderTarget::Initialize(const std::filesystem::path& fileName)
{
	ASSERT(false, "RenderTarget: Initialize from file is not implemented yet");
}

RenderTarget::Initialize(uint32_t width, uint32_t height, Format format)
{
	D3D11_TEXTURE2D_DESC desc{};
}

void RenderTarget::Terminaete()
{

}

void RenderTarget::BeginRender(Color clearColor)
{
}