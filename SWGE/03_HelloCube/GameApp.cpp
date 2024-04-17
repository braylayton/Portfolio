#include "GameApp.h"

using namespace SWGE;

namespace //Internal Linkage -- to not pollute the global namespace
{
	
//sizeof is a compile time operator(static)

	float Xlength =0.5f, YHeight = 0.5f, ZWidth = 0.5f;

	const Graphics::VertexPC kVertices[] =
	{
		//Front
		{ Math::Vector3(-Xlength,  YHeight, -ZWidth), Math::Vector4::Red() },	//top left 0
		{ Math::Vector3(Xlength,  YHeight,	-ZWidth), Math::Vector4::Blue() },		//top right 1
		{ Math::Vector3(Xlength, -YHeight,	-ZWidth), Math::Vector4::Yellow() },	//bot right 2
		{ Math::Vector3(-Xlength, -YHeight, -ZWidth), Math::Vector4::Green() },	//bot left 3
		//Back
		{ Math::Vector3(-Xlength,  YHeight, ZWidth), Math::Vector4::Cyan() },	//top left 4
		{ Math::Vector3(Xlength,  YHeight,  ZWidth), Math::Vector4::Orange() },	//top right 5
		{ Math::Vector3(Xlength, -YHeight,  ZWidth), Math::Vector4::Magenta() },	//bot right 6
		{ Math::Vector3(-Xlength, -YHeight, ZWidth), Math::Vector4::LightRed() },	//bot left 7

	};

	const int kVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);
	const uint32_t kIndices[] =
	{
		//front  good
		0,1,2, 
		0,2,3,
		//Top	good
		4,1,0,
		4,5,1,
		//Left good
		4,0,3,
		4,3,7,
		//Right
		1,5,6,
		1,6,2,
		//Back
		5,4,7,
		5,7,6,
		//Bot
		3,2,6,
		3,6,7

	};
	const int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);

}

GameApp::GameApp()
	:	mTriBuffer(nullptr),
		mHeartBuffer(nullptr),
		mStarBuffer(nullptr),
		mBoatBuffer(nullptr),
		mCurrentBuffer(nullptr),
		mConstantBuffer(nullptr)
{
}

GameApp::~GameApp()
{

}

void GameApp::OnInitialize()
{

	mWindow.Initialize(GetInstance(), GetAppName(), 720, 720);
	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();
	
	MBuffer = new Graphics::MeshBuffer;
	MBuffer->Initialize(kVertices, sizeof(Graphics::VertexPC), kVertexCount, kIndices, kIndexCount);


	D3D11_BUFFER_DESC bufferDesc = {}; // 0 initialize
	////////////////////////////////
	// Create and fill constant buffer
	bufferDesc.ByteWidth = sizeof(Math::Matrix4) * 3;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	device->CreateBuffer(&bufferDesc, nullptr, &mConstantBuffer);


	///////////////////////////////
	//Compile and create vertex shader\\
	//D3DCOMPILE_DEBUG flag improves the shader debugging experience\\

	//// Create vertex Shader
	
	VShader = new Graphics::VertexShader;
	VShader->Initialize(L"../Assets/Shaders/DoTransform.fx", "VS", "vs_5_0", Graphics::VertexPC::Format);
	
	///////////////////////////////
	//Compile and create pixel shader
	 //Create pixel Shader
	PShader = new Graphics::PixelShader;
	PShader->Initialize(L"../Assets/Shaders/DoTransform.fx", "PS", "ps_5_0", Graphics::VertexPC::Format);

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
	SafeRelease(mConstantBuffer);
	Graphics::GraphicsSystem::StaticTerminate();
	SafeDelete(VShader);
	SafeDelete(PShader);
	MBuffer->Terminate();
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

	static float rotationY = 0.0f;
	static float rotationX = 0.0f;

	//if (Input::InputSystem::IsKeyDown())
	//{
		//rotationY += 0.05f;
	//}	

	if (GetAsyncKeyState(VK_RIGHT))
	{
		rotationY -= 0.05f;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		rotationX -= 0.05f;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		rotationX += 0.05f;
	}


	// Do rendering stuff here ...
	//Bind the input layout , vertex shader, and pixel shader

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	ID3D11DeviceContext* context = graphicsSystem->GetContext();

	
	PShader->Bind();
	VShader->Bind();

	Math::Matrix4 rotation = Math::Matrix4::RotationY(rotationY) * Math::Matrix4::RotationX(rotationX);


	Math::Matrix4 world, view, projection;
	world = rotation;
	view = Math::Matrix4
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 3.0f, 1.0f
	};
	projection = Math::Matrix4
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, -1.0f, 0.0f
	};

	//Update Matrices
	Math::Matrix4 matricies[3];
	matricies[0] = Math::Transpose(world);
	matricies[1] = Math::Transpose(view);
	matricies[2] = Math::Transpose(projection);
	context->UpdateSubresource(mConstantBuffer, 0, nullptr, matricies, 0,0);
	context->VSSetConstantBuffers(0, 1, &mConstantBuffer);


	//Set vertex buffer
	
	MBuffer->Render(sizeof(Graphics::VertexPC),kVertexCount, kIndexCount);
}

// HomeWork:
/*
vertexSize * vertexcount  be parameters passed in instead of
bufferDesc.ByteWidth = sizeof(SimpleVertex) * TriVertexCount;


add methods:
void initialize(void* verticies, uint32_t vertexsize,  uint32_t vertexcount, uint32_t* indicies, uint32_t indexcount);
void initialize(void* verticies, uint32_t vertexsize,  uint32_t vertexcount);
void Teminate();
void Render();




*/