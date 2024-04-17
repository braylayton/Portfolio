#include "GameApp.h"

using namespace SWGE;

namespace //Internal Linkage -- to not pollute the global namespace
{

	//sizeof is a compile time operator(static)

	float Xlength = 1.0f, YHeight = 1.0f, ZWidth = 1.0f;

	const Graphics::Vertex kVertices[] =
	{
		//Front
		{ Math::Vector3(-Xlength, YHeight,  -ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)) },	//top left 0 
		{ Math::Vector3(Xlength,  YHeight,	-ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(Xlength,   YHeight, -ZWidth)) },	//top right 1
		{ Math::Vector3(Xlength,  -YHeight,	-ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, -ZWidth)) },	//bot right 2
		{ Math::Vector3(-Xlength, -YHeight, -ZWidth),	Math::Vector3(0,0,-1),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)) },	//bot left 3
		//Back											 				 					    
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth) ,	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, ZWidth)) },	//top left 4
		{ Math::Vector3(Xlength,   YHeight,  ZWidth) ,	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(Xlength,   YHeight, ZWidth)) },	//top right 5
		{ Math::Vector3(Xlength,  -YHeight,  ZWidth) ,	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, ZWidth)) },	//bot right 6
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth) ,	Math::Vector3(0,0,1),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, ZWidth)) },	//bot left 7
		//Top											
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth),	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight,  ZWidth)) },	//top left 8 
		{ Math::Vector3(Xlength,   YHeight,	 ZWidth),	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(Xlength,   YHeight,  ZWidth)) },	//top right 9
		{ Math::Vector3(Xlength,   YHeight,	-ZWidth),	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(Xlength,   YHeight, -ZWidth)) },	//bot right 10
		{ Math::Vector3(-Xlength,  YHeight, -ZWidth),	Math::Vector3(0,1,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)) },	//bot left 11
		//Bottom											   				 					    
		{ Math::Vector3(-Xlength, -YHeight, -ZWidth) ,	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)) },	//top left 12
		{ Math::Vector3(Xlength,  -YHeight, -ZWidth) ,	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(Xlength,  -YHeight, -ZWidth)) },	//top right 13
		{ Math::Vector3(Xlength,  -YHeight,  ZWidth) ,	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(Xlength,  -YHeight,  ZWidth)) },	//bot right 14
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth) ,	Math::Vector3(0,-1,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight,  ZWidth)) },	//bot left 15
		//Left											
		{ Math::Vector3(-Xlength,  YHeight,  ZWidth),	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight,  ZWidth)) },	//top left 16
		{ Math::Vector3(-Xlength,  YHeight,	-ZWidth),	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength,  YHeight, -ZWidth)) },	//top right 17
		{ Math::Vector3(-Xlength, -YHeight,	-ZWidth),	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight, -ZWidth)) },	//bot right 18
		{ Math::Vector3(-Xlength, -YHeight,  ZWidth),	Math::Vector3(-1,0,0),	Math::Normalize(Math::Vector3(-Xlength, -YHeight,  ZWidth)) },	//bot left 19
		//Right											   				 					    
		{ Math::Vector3(Xlength,  YHeight, -ZWidth) ,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength,  YHeight, -ZWidth)) },	//top left 20
		{ Math::Vector3(Xlength,  YHeight,  ZWidth) ,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength,  YHeight,  ZWidth)) },	//top right 21
		{ Math::Vector3(Xlength, -YHeight,  ZWidth) ,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength, -YHeight,  ZWidth)) },	//bot right 22
		{ Math::Vector3(Xlength, -YHeight, -ZWidth) ,	Math::Vector3(1,0,0),	Math::Normalize(Math::Vector3(Xlength, -YHeight, -ZWidth)) },	//bot left 23
	};

	const int kVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);
	const uint32_t kIndices[] =
	{
		//Front
		0,1,2,
		0,2,3,
		//Back good
		5,4,7,
		5,7,6,
		//Top	good
		8,9,10,		//8,11,10,8,10,9,
		8,10,11,
		//Bot
		12,13,14,
		12,14,15,
		//Left good
		16,17,18,
		16,18,19,
		//Right
		20,21,22,
		20,22,23

	};
	const int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);

}

//
//GameApp::CreateSphere()
//{
//	float mRadius = 1.0f;
//	int mSliceCount = 5;
//	int mStackCount = 5;
//	int size = mSliceCount * mStackCount;
//
//
//	const Graphics::Vertex *kSphereVertices = new Graphics::Vertex[size];
//
//
//
//	float mPhi = Math::kPi / mStackCount;
//	float mTheta = Math::kDegToRad / mSliceCount;
//
//	for (int i = 0; i < mStackCount; i++)
//	{
//		mPhi *= i;
//		for (int j = 0; j < mSliceCount; j++)
//		{
//			mTheta *= j;
//			Math::Vector3 mPosition;
//			Var.x = (mRadius * sin(mPhi) * cos(mTheta));
//			Var.y = (mRadius * cos(mPhi));
//			Var.z = (mRadius * sin(mPhi) * sin(mTheta));
//
//			Math::Vector3 mNormal = Math::Normalize(mPosition);
//			Math::Vector3 mTangent = 1 //Math::Normalize(); 
//				Math::Vector2 mUV = Math::Vector2(mTheta / Math::kTwoPi, mPhi / Math::kPi);
//
//			kSphereVertices[j] = (mPosition, mNormal, mTangent, Math::Vector4::White(), mUV);
//		}
//	}
//}

GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::OnInitialize()
{
	mWindow.Initialize(GetInstance(), GetAppName(), 720, 720);
	mTimer.Initialize();

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();
	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });

	mBulder.CreateCube(mCubeMesh);

	mConstantBuffer.Initialize();
	mTexture.Initialize("../Assets/Textures/CheckerBoard.jpg");
	mSampler.Initialize(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Clamp);
	mVertexShader.Initialize(L"../Assets/Shaders/texturing.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/texturing.fx", "PS", "ps_5_0", Graphics::Vertex::Format);
	mMeshBuffer.Initialize(mCubeMesh);
	//mMeshBuffer.Initialize(kVertices, sizeof(Graphics::Vertex), kVertexCount, kIndices, kIndexCount);
	//for (size_t x = 0; x < 24; x++)
	//{
	//	kVertices[x].position() = Math::Vector3(2.0f, 0, 0);
	//}
}

void GameApp::OnTerminate()
{
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mSampler.Terminate();
	mTexture.Terminate();
	mCubeMesh.Destroy();

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

	const float moveSpeed = 10.0f;
	const float turnSpeed = 10.0f;
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

	Math::Matrix4 world = Math::Matrix4::Identity();
	Math::Matrix4 view = mCamera.GetViewMatrix();
	Math::Matrix4 projection = mCamera.GetPerspectiveMatrix(720, 720);

	auto context = graphicsSystem->GetContext();

	// Update matrices
	TransformData data;
	data.world = Math::Transpose(world);
	data.view = Math::Transpose(view);
	data.projection = Math::Transpose(projection);	
	mTexture.BindVS(0);
	mTexture.BindPS(0);
	mSampler.BindVS(0);
	mSampler.BindGS(0);
	mSampler.BindPS(0);
	mConstantBuffer.Set(data);
	mConstantBuffer.BindVS();
	/*for (int x = 0; x < 5; x++)
	{

		Math::Matrix4 cube = world + Math::Matrix4::RotationX(rotation) + Math::Matrix4::Translation(x, 0.0f, 0.0f);
		data.world = Math::Transpose(cube);
		mConstantBuffer.Set(data);
		mConstantBuffer.BindVS();
		
	}*/

	mMeshBuffer.Render();
	graphicsSystem->EndRender();
}

/*

Homework:

05_HelloTexture

3 cubes with 3 sampling mode

build a long wall map textures

*/