#include "Precompiled.h"
#include "RasterizerState.h"


using namespace SWGE;
using namespace Graphics;

namespace
{
	inline D3D11_CULL_MODE GetCullMode(CullMode cullMode)
	{
		switch (cullMode)
		{
			case CullMode::Back:
			{
				return  D3D11_CULL_BACK;
			}
			case CullMode::None:
			{
				return  D3D11_CULL_NONE;
			}
			case CullMode::Front: {}
			default: {}
		}
		return D3D11_CULL_FRONT;
	}

	inline D3D11_FILL_MODE GetFillMode(FillMode fillMode)
	{
		switch (fillMode)
		{
			case FillMode::Solid:
			{
				return  D3D11_FILL_SOLID;
			}
			case FillMode::WireFrame:
			{}
			default:
			{}
		}
		return D3D11_FILL_WIREFRAME;
	}
}

RasterizerState::RasterizerState()
{

}
RasterizerState::~RasterizerState()
{

}


void RasterizerState::Initialize(CullMode cullMode, FillMode fillMode)
{
	D3D11_RASTERIZER_DESC desc{};
	desc.CullMode = GetCullMode(cullMode);
	desc.FillMode = GetFillMode(fillMode);
	desc.FrontCounterClockwise = false;
	
	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;

	ID3D11Device* device = GraphicsSystem::Get()->GetDevice();
	HRESULT hr = device->CreateRasterizerState(&desc, &mRasterizerState);
	ASSERT(SUCCEEDED(hr), "[RasterizerState] failed to create rasterizer state");

}

void RasterizerState::Terminate()
{
	SafeRelease(mRasterizerState);
}

void RasterizerState::Set()
{
	GraphicsSystem::Get()->GetContext()->RSSetState(mRasterizerState);
}
void RasterizerState::Clear()
{
	GraphicsSystem::Get()->GetContext()->RSSetState(nullptr);
}
