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
{
}

GameApp::~GameApp()
{
}

void GameApp::OnInitialize()
{
	mWindow.Initialize(GetInstance(), GetAppName(), 1280, 720);
	mTimer.Initialize();

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();

	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });

	mConstantBuffer.Initialize();
	mVertexShader.Initialize(L"../Assets/Shaders/DoTransform.fx", "VS", "vs_5_0", Graphics::VertexPC::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/DoTransform.fx", "PS", "ps_5_0", Graphics::VertexPC::Format);
	mMeshBuffer.Initialize(kVertices, sizeof(Graphics::VertexPC), kVertexCount, kIndices, kIndexCount);
}

void GameApp::OnTerminate()
{
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();

	Input::InputSystem::StaticTerminate();
	Graphics::GraphicsSystem::StaticTerminate();
	mWindow.Terminate();
}

void GameApp::OnUpdate()
{
	if (mWindow.ProcessMessage())
	{
		Kill();
		return;
	}

	mTimer.Update();
	auto dt = mTimer.GetElapsedTime();

	auto inputSystem = Input::InputSystem::Get();
	inputSystem->Update();

	if (inputSystem->IsKeyPressed(SWGE::Input::KeyCode::ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}

	const float moveSpeed = 1.0f;
	const float turnSpeed = 1.0f;
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::W))
		mCamera.Walk(dt * moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::S))
		mCamera.Walk(dt * -moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::D))
		mCamera.Strafe(dt * moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::A))
		mCamera.Strafe(dt * -moveSpeed);
	mCamera.Yaw(inputSystem->GetMouseMoveX() * dt * turnSpeed);
	mCamera.Pitch(inputSystem->GetMouseMoveY() * dt * turnSpeed);

	static float rotation = 0.0f;
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::LEFT))
	{
		rotation += 0.01f;
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::RIGHT))
	{
		rotation -= 0.01f;
	}

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

	// Bind the input layout, vertex shader, and pixel shader
	mVertexShader.Bind();
	mPixelShader.Bind();

	Math::Matrix4 world = Math::Matrix4::RotationY(rotation);
	Math::Matrix4 view = mCamera.GetViewMatrix();
	Math::Matrix4 projection = mCamera.GetPerspectiveMatrix();

	auto context = graphicsSystem->GetContext();

	// Update matrices
	TransformData data;
	data.world = Math::Transpose(world);
	data.view = Math::Transpose(view);
	data.projection = Math::Transpose(projection);
	mConstantBuffer.Set(data);
	mConstantBuffer.BindVS();

	mMeshBuffer.Render(sizeof(Graphics::VertexPC), kVertexCount, kIndexCount);

	graphicsSystem->EndRender();
}

