#include "Precompiled.h"
#include "BlendState.h"

#include "GraphicsSystem.h"

using namespace BongoEngine;
using namespace BongoEngine::Graphics;

namespace
{
	D3D11_BLEND GetSrcBlend(BlendState::Mode mode)
	{
		switch (mode)
		{
		case BlendState::Mode::Additive:			return D3D11_BLEND_SRC_ALPHA;
		case BlendState::Mode::AlphaBlend:			return D3D11_BLEND_SRC_ALPHA;
		case BlendState::Mode::AlphaPremultiplied:	return D3D11_BLEND_ONE;
		case BlendState::Mode::Opaque:				return D3D11_BLEND_ONE;
		default:
			ASSERT(false, "BlendState: blend mode not found");
			break;
		}
		return D3D11_BLEND_ONE;
	}
	D3D11_BLEND GetDestBlend(BlendState::Mode mode)
	{
		switch (mode)
		{
		case BlendState::Mode::Additive:			return D3D11_BLEND_ONE;
		case BlendState::Mode::AlphaBlend:			return D3D11_BLEND_INV_SRC_ALPHA;
		case BlendState::Mode::AlphaPremultiplied:	return D3D11_BLEND_INV_SRC_ALPHA;
		case BlendState::Mode::Opaque:				return D3D11_BLEND_ZERO;
		default:
			ASSERT(false, "BlendState: blend mode not found");
			break;
		}
		return D3D11_BLEND_ZERO;
	}
}

void BlendState::ClearState()
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->OMSetBlendState(nullptr, nullptr, UINT_MAX);
	context->OMSetDepthStencilState(nullptr, 0);
}

BlendState::~BlendState()
{
	ASSERT(mBlendState == nullptr, "BlendState: terminate must be called");
}

void BlendState::Initialize(Mode mode)
{
	const D3D11_BLEND srcBlend = GetSrcBlend(mode);
	const D3D11_BLEND destBlend = GetDestBlend(mode);

	D3D11_BLEND_DESC desc{};
	desc.RenderTarget[0].BlendEnable = (srcBlend != D3D11_BLEND_ONE) || (destBlend != D3D11_BLEND_ZERO);
	desc.RenderTarget[0].SrcBlend = srcBlend;
	desc.RenderTarget[0].DestBlend = destBlend;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = srcBlend;
	desc.RenderTarget[0].DestBlendAlpha = destBlend;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	auto device = GraphicsSystem::Get()->GetDevice();
	HRESULT hr = device->CreateBlendState(&desc, &mBlendState);
	ASSERT(SUCCEEDED(hr), "BlendState: failed to create blend state");

	// transparent objects still depth test but don't write depth
	D3D11_DEPTH_STENCIL_DESC depthDesc{};
	depthDesc.DepthEnable = TRUE;
	depthDesc.DepthWriteMask = (mode == Mode::Opaque) ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDesc.StencilEnable = FALSE;

	hr = device->CreateDepthStencilState(&depthDesc, &mDepthStencilState);
	ASSERT(SUCCEEDED(hr), "BlendState: failed to create depth stencil state");
}

void BlendState::Terminate()
{
	SafeRelease(mBlendState);
	SafeRelease(mDepthStencilState);
}

void BlendState::Set()
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->OMSetBlendState(mBlendState, nullptr, UINT_MAX);
	context->OMSetDepthStencilState(mDepthStencilState, 0);
}