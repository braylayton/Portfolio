
#include "GameApp.h"

using namespace SWGE;

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
	Graphics::MeshBuilder::CreateCube(mCubeMesh);
	Graphics::MeshBuilder::CreateUVSphere(mUVSphereMesh, 16 ,16);
	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mConstantBuffer.Initialize();
	mTerrain.Initialize("../Assets/Textures/heightmap.raw", 256, 256, 50);
	mTexture.Initialize("../Assets/Textures/HappyFace.jpg");
	mSampler.Initialize(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Wrap);
	mVertexShader.Initialize(L"../Assets/Shaders/Lighting.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/Lighting.fx", "PS", "ps_5_0", Graphics::Vertex::Format);
	mMeshBuffer.Initialize(mUVSphereMesh, true);
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
	mUVSphereMesh.Destroy();
	mTerrain.Terminate();


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

	Math::Matrix4 world = Math::Matrix4::RotationX(rotation);
	Math::Matrix4 view = mCamera.GetViewMatrix();
	Math::Matrix4 projection = mCamera.GetPerspectiveMatrix(720, 720);

	auto context = graphicsSystem->GetContext();

	mLight.direction = { 0.0f, -1.0f, 1.0f, 0.0f };
	mLight.ambient = { 0.25f, 0.25f, 0.25f, 0.25f };
	//mLight.difuse ={0.3f, 0.3f, 0.3f, 0.3f };
	mLight.specular = {0.1f, 0.1f, 0.1f, 0.1f };

	// Update matrices
	TransformData data;
	data.world = Math::Transpose(world);
	data.wvp = Math::Transpose(world * view * projection);
	data.cameraPosition = Math::Vector4(mCamera.GetPosition(), 1);
	data.light = mLight;
	data.material = mMaterial;
	data.useTextureBool = true;
	mTexture.BindVS(0);
	mTexture.BindPS(0);
	mSampler.BindVS(0);
	mSampler.BindPS(0);
	mConstantBuffer.Set(data);
	mConstantBuffer.BindVS(0);
	mConstantBuffer.BindPS(0);

	mTerrain.Render();
	//mMeshBuffer.Render();
	graphicsSystem->EndRender();

}

/*

Homework:

//create a class called meshbuilder
{
public:
static void CreateCube(Mesh& mesh); 
static void CreateSphere(Mesh& mesh); // for ring sphere specify how many rings and slices


*/