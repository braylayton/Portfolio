#include "Precompiled.h"
#include "VertexShader.h"
#include "VertexTypes.h"
#include "GraphicsSystem.h"

namespace SWGE {

namespace Graphics 
{

namespace 
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> GetVertexDescription(uint32_t vertexformat)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> desc;

		if (vertexformat & VF_POSITION)
		{
			desc.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexformat & VF_NORMAL)
		{
			desc.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexformat & VF_TANGENT)
		{
			desc.push_back({ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexformat & VF_COLOR)
		{
			desc.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexformat & VF_UV)
		{
			desc.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexformat & VF_BINDEX)
		{
			desc.push_back({ "BLENDINDICIES", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
		if (vertexformat & VF_BWEIGHT)
		{
			desc.push_back({ "BLENDWEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}



		return desc;
	}
}

	const D3D11_INPUT_ELEMENT_DESC kVertexLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, //rgb 32 bit, 3 float layout
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }, //
	};

	// this is the descriptor so graphics card understands


	VertexShader::VertexShader()
	{
		//auto graphicsSystem = Graphics::GraphicsSystem::Get();
	}

	VertexShader::~VertexShader()
	{
	}

	void  VertexShader::Initialize(LPCWSTR filename, const char* entrypoint, LPCSTR shadermodel, uint32_t vertexformat)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

		mVertexShader = nullptr;
		mInputLayout = nullptr;
		ID3DBlob* shaderBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;

		const auto vertexDesc = GetVertexDescription(vertexformat);

		HRESULT hr = D3DCompileFromFile
		(
			//L"../Assets/Shaders/DoTransform.fx",
			filename,
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entrypoint, //"VS"
			shadermodel, //"vs_5_0"
			shaderFlags,
			0,
			&shaderBlob,
			&errorBlob
		);
		ASSERT(SUCCEEDED(hr), "Failed to Compile shader. Error: %s", (const char*)errorBlob->GetBufferPointer());
		SafeRelease(errorBlob);

		GraphicsSystem::Get()->GetDevice()->CreateVertexShader
		(
			shaderBlob->GetBufferPointer(),
			shaderBlob->GetBufferSize(),
			nullptr,
			&(this->mVertexShader)
		);

		//Create input Laytout
		GraphicsSystem::Get()->GetDevice()->CreateInputLayout
		(
			vertexDesc.data(),
			(UINT)vertexDesc.size(),
			shaderBlob->GetBufferPointer(),
			shaderBlob->GetBufferSize(),
			&(this->mInputLayout)
		);
		SafeRelease(shaderBlob);
	}

	void VertexShader::Bind()
	{

		//auto graphicsSystem = Graphics::GraphicsSystem::Get();
		ID3D11DeviceContext* context = GraphicsSystem::Get()->GetContext();
		context->IASetInputLayout(mInputLayout);
		context->VSSetShader(mVertexShader, nullptr, 0);
	}

	void VertexShader::Terminate()
	{
		SafeRelease(mInputLayout);
		SafeRelease(mVertexShader);
	}

}
}