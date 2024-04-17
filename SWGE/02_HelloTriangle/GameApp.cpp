#include "GameApp.h"

using namespace SWGE;

namespace //Internal Linkage -- to not polute the global namespace
{
	struct SimpleVertex
	{
		Math::Vector3 position;
		Math::Vector4 colour; //float r, g, b, a;
		
	};

	const D3D11_INPUT_ELEMENT_DESC kVertexLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, //rgb 32 bit, 3 float layout
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }, //
	};

	const SimpleVertex TriVerticies[] =
	{
		//TRIFORCE
		//Top Triangle
		{ Math::Vector3(0.0f, 0.8f, 0.0f),  Math::Vector4::Yellow()  },
		{ Math::Vector3(0.2f, 0.2f, 0.0f),  Math::Vector4::Yellow()  },
		{ Math::Vector3(-0.2f, 0.2f, 0.0f), Math::Vector4::Yellow() },
		
		//Bottom Left
		{ Math::Vector3(-0.2f, 0.2f, 0.0f),  Math::Vector4::Yellow()  },
		{ Math::Vector3(0.0f, -0.4f, 0.0f),  Math::Vector4::Yellow()  },
		{ Math::Vector3(-0.4f, -0.4f, 0.0f), Math::Vector4::Yellow() },
		
		//Bottom Right
		{ Math::Vector3(0.2f, 0.2f, 0.0f),  Math::Vector4::Yellow()  },
		{ Math::Vector3(0.4f, -0.4f, 0.0f), Math::Vector4::Yellow() },
		{ Math::Vector3(0.0f, -0.4f, 0.0f), Math::Vector4::Yellow() },
	};
	const SimpleVertex HeartVerticies[] =
	{
		//Heart
		//Bottom
		{ Math::Vector3(0.0f, -0.8f, 0.0f), Math::Vector4::Red()	},	//Bottom
		{ Math::Vector3(-0.6f, 0.2f, 0.0f), Math::Vector4::Red()	},	//Left
		{ Math::Vector3(0.6f, 0.2, 0.0f),	Math::Vector4::Red()	},	//Right
		//Left
		{ Math::Vector3(-0.6f, 0.2f, 0.0f), Math::Vector4::Red() },	//Left 
		{ Math::Vector3(-0.3f, 0.6f, 0.0f),	Math::Vector4::Red() },	//Top
		{ Math::Vector3(0.0f, 0.2, 0.0f),	Math::Vector4::Red() },		//Right
		//Right
		{ Math::Vector3(0.0f, 0.2f, 0.0f), Math::Vector4::Red() },	//Left 
		{ Math::Vector3(0.3f, 0.6f, 0.0f),	Math::Vector4::Red() },	//Top
		{ Math::Vector3(0.6f, 0.2, 0.0f),	Math::Vector4::Red() },		//Right

	};

	const SimpleVertex StarVerticies[] =
	{
		//Star
		//Top
		{ Math::Vector3(0.0f, 0.8f, 0.0f),	Math::Vector4::Yellow() }, //Top
		{ Math::Vector3(0.2f, 0.4f, 0.0f), Math::Vector4::Yellow()	}, //Right
		{ Math::Vector3(-0.2f, 0.4, 0.0f),	Math::Vector4::Yellow() }, //Left
		//Middle
		{ Math::Vector3(0.0f, -0.2f, 0.0f),	Math::Vector4::Yellow() }, //Bottom
		{ Math::Vector3(-0.6f, 0.4f, 0.0f), Math::Vector4::Yellow() }, //Left
		{ Math::Vector3(0.6f, 0.4, 0.0f),	Math::Vector4::Yellow() }, //Right
		//Bot Left
		{ Math::Vector3(-0.3f, 0.1f, 0.0f),	Math::Vector4::Yellow() }, //Top
		{ Math::Vector3(0.0f, -0.2f, 0.0f), Math::Vector4::Yellow() }, //Right
		{ Math::Vector3(-0.4f, -0.5, 0.0f),	Math::Vector4::Yellow() }, //Left
		//Bot Right
		{ Math::Vector3( 0.3f, 0.1f, 0.0f),	Math::Vector4::Yellow() }, //Top
		{ Math::Vector3( 0.4f, -0.5f, 0.0f), Math::Vector4::Yellow() }, //Right
		{ Math::Vector3( 0.0f, -0.2f, 0.0f),	Math::Vector4::Yellow() }, //Left
	};

	const SimpleVertex BoatVerticies[] =
	{
		// Boat
		//bot left
		{ Math::Vector3(-0.3f, -0.8f, 0.0f), Math::Vector4::Black() }, //Bottom
		{ Math::Vector3(-0.6f, -0.4f, 0.0f), Math::Vector4::Black() }, //Left
		{ Math::Vector3(0.0f, -0.4, 0.0f),	Math::Vector4::Black() }, //Right
		//bot right
		{ Math::Vector3(0.3f, -0.8f, 0.0f), Math::Vector4::Black() }, //Bottom
		{ Math::Vector3(0.0f, -0.4f, 0.0f), Math::Vector4::Black() }, //Left
		{ Math::Vector3(0.6f, -0.4, 0.0f),	Math::Vector4::Black() }, //Right
		//bot Middle
		{ Math::Vector3(0.0f, -0.4f, 0.0f), Math::Vector4::Black() }, //Top
		{ Math::Vector3(0.3f, -0.8f, 0.0f), Math::Vector4::Black() }, //Right
		{ Math::Vector3(-0.3f, -0.8f, 0.0f),Math::Vector4::Black() }, //Left
		//Sail
		//Left
		{ Math::Vector3(-0.03f, 0.2f, 0.0f), Math::Vector4::White() }, //Top
		{ Math::Vector3(-0.03f, -0.35f, 0.0f), Math::Vector4::White() }, //Right
		{ Math::Vector3(-0.3f, -0.35f, 0.0f),Math::Vector4::White() }, //Left
		//Right
		{ Math::Vector3(0.0f, 0.6f, 0.0f), Math::Vector4::White() }, //Top
		{ Math::Vector3(0.4f, -0.3, 0.0f), Math::Vector4::White() }, //Right
		{ Math::Vector3(0.0f, -0.3f, 0.0f),Math::Vector4::White() }, //Left
	};

	const int TriVertexCount = sizeof(TriVerticies) / sizeof(TriVerticies[0]);
	const int HeartVertexCount = sizeof(HeartVerticies) / sizeof(HeartVerticies[0]);
	const int StarVertexCount = sizeof(StarVerticies) / sizeof(StarVerticies[0]);
	const int BoatVertexCount = sizeof(BoatVerticies) / sizeof(BoatVerticies[0]);
	int CurrentCount;
	//sizeof is a compile time operator(static)


}

GameApp::GameApp()
	:	mTriBuffer(nullptr),
		mHeartBuffer(nullptr),
		mStarBuffer(nullptr),
		mBoatBuffer(nullptr),
		mCurrentBuffer(nullptr)
		
{
}

GameApp::~GameApp()
{

}

void GameApp::OnInitialize()
{

	mWindow.Initialize(GetInstance(), GetAppName(), 1280, 720);
	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	auto graphicsSystem = Graphics::GraphicsSystem::Get();

	////////////////////////////////
	//Create and fill vertex buffer
	D3D11_BUFFER_DESC bufferDesc = {}; // 0 initialize
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; //specify the usage
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * TriVertexCount; // the size of vertex
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0; // will cpu need access to this buffer
	bufferDesc.MiscFlags = 0;
	//Triforce
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = TriVerticies;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mTriBuffer);
	mCurrentBuffer = mTriBuffer;
	CurrentCount = TriVertexCount;
	//Heart
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * HeartVertexCount;
	initData.pSysMem = HeartVerticies;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mHeartBuffer);
	//Star
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * StarVertexCount;
	initData.pSysMem = StarVerticies;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mStarBuffer);
	//Boat
	bufferDesc.ByteWidth = sizeof(SimpleVertex) * BoatVertexCount;
	initData.pSysMem = BoatVerticies;
	graphicsSystem->GetDevice()->CreateBuffer(&bufferDesc, &initData, &mBoatBuffer);

	///////////////////////////////
	//Compile and create vertex shader\\
	//D3DCOMPILE_DEBUG flag improves the shader debugging experience\\

	//// Create vertex Shader
	
	VShader = new Graphics::VertexShader;
	VShader->Initialize();
	
	///////////////////////////////
	//Compile and create pixel shader
	 //Create pixel Shader
	PShader = new Graphics::PixelShader;
	PShader->Initialize();

}

void GameApp::OnTerminate()
{
	PShader->Terminate();
	VShader->Terminate();
	SafeRelease(mTriBuffer);
	SafeRelease(mHeartBuffer);
	SafeRelease(mStarBuffer);
	SafeRelease(mBoatBuffer);
	SafeRelease(mCurrentBuffer);
	Graphics::GraphicsSystem::StaticTerminate();
	mWindow.Terminate();
}

void GameApp::OnUpdate()
{
	if(mWindow.ProcessMessage())
	{
		Kill();
		return;
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}
	

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

	// Do rendering stuff here ...
	//Bind the input layout , vertex shader, and pixel shader

	ID3D11DeviceContext* context = graphicsSystem->GetContext();
	
	PShader->Bind();
	VShader->Bind();

	//Set vertex buffer
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mCurrentBuffer, &stride, &offset);

	//set primitive topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw mesh
	if (GetAsyncKeyState(VK_F1))
	{
		CurrentCount = TriVertexCount;
		mCurrentBuffer = mTriBuffer;
	}
	if (GetAsyncKeyState(VK_F2))
	{
		CurrentCount = HeartVertexCount;
		mCurrentBuffer = mHeartBuffer;
	}
	if (GetAsyncKeyState(VK_F3))
	{
		CurrentCount = StarVertexCount;
		mCurrentBuffer = mStarBuffer;
	}
	if (GetAsyncKeyState(VK_F4))
	{
		CurrentCount = BoatVertexCount;
		mCurrentBuffer = mBoatBuffer;
	}

	context->Draw(CurrentCount, 0);

	graphicsSystem->EndRender();

}

// HomeWork:
/*
Initialize 3 vertex buffers and initialize the with 
the following

1) triforce DONE
2) heart DONE
3) star DONE
4) random shape DONE

use this code below to switch between them:
	if(getAsyncKeyState(VK_F1/VK_F2/VK_F3)) Done

	add VertexShader and PixelShader classes in Graphics

	Graphics::VertexShader mVertexShader;
	//ID3D11InputLaytout* mInputLayout;
	//ID3D11

	Class VertexShader
	-Initialize()/Terminate()
	-Bind()


*/