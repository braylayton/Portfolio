#include "Precompiled.h"
#include "PixelShader.h"
#include "Graphics\Inc\Graphics.h"

using namespace SWGE;
using namespace Graphics;

PixelShader::PixelShader()
{
	//auto graphicsSystem = Graphics::GraphicsSystem::Get();

}

PixelShader::~PixelShader()
{

}

void PixelShader::Initialize(LPCWSTR filename, const char* entrypoint, LPCSTR shadermodel, uint32_t vertexformat)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	mPixelShader = nullptr;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile
	(
		filename,		//L"../Assets/Shaders/DoTransform.fx",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypoint,		//"PS",
		shadermodel,	//"ps_5_0",
		shaderFlags,
		0,
		&shaderBlob,
		&errorBlob
	);
	ASSERT(SUCCEEDED(hr), "Failed to Compile shader. Error: %s", (const char*)errorBlob->GetBufferPointer());
	SafeRelease(errorBlob);

	GraphicsSystem::Get()->GetDevice()->CreatePixelShader
	(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader
	);
}

void PixelShader::Terminate()
{
	SafeRelease(mPixelShader);
}

void PixelShader::Bind()
{

	ID3D11DeviceContext* context = GraphicsSystem::Get()->GetContext();
	context->PSSetShader(mPixelShader, nullptr, 0);
}