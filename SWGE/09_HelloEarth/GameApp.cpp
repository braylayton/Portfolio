
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
	Graphics::MeshBuilder::CreateUVSphere(mUVSphereMesh,100,100);
	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mConstantBuffer.Initialize();
	mDiffuseMap.Initialize("../Assets/Textures/earth_diff.jpg");
	mNormalMap.Initialize("../Assets/Textures/earth_normal.jpg");
	mSpecularMap.Initialize("../Assets/Textures/earth_spec.jpg");
	mDisplacementMap.Initialize("../Assets/Textures/earth_bump.jpg");
	mSampler.Initialize(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Clamp);
	mVertexShader.Initialize(L"../Assets/Shaders/Standard.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/Standard.fx", "PS", "ps_5_0", Graphics::Vertex::Format);
	mMeshBuffer.Initialize(mUVSphereMesh, false);//mMeshBuffer.Initialize(mCubeMesh);
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
	mDiffuseMap.Terminate();
	mSpecularMap.Terminate();
	mNormalMap.Terminate();
	mDisplacementMap.Terminate();
	mCubeMesh.Destroy();
	mUVSphereMesh.Destroy();


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

	static float rotationx = 0.0f;
	static float rotationy = 0.0f;
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::LEFT))
	{
		rotationy += 0.1f;
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::RIGHT))
	{
		rotationy -= 0.1f;
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::DOWN))
	{
		rotationx += 0.1f;
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::UP))
	{
		rotationx -= 0.1f;
	}

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

	// Bind the input layout, vertex shader, and pixel shader
	mVertexShader.Bind();
	mPixelShader.Bind();
	Math::Matrix4 rotation = Math::Matrix4::RotationX(rotationx) * Math::Matrix4::RotationY(rotationy);
	Math::Matrix4 world = rotation;
	Math::Matrix4 view = mCamera.GetViewMatrix();
	Math::Matrix4 projection = mCamera.GetPerspectiveMatrix();

	auto context = graphicsSystem->GetContext();

	mLight.direction = { Math::Vector3::ZAxis(), 0.0f };
	mLight.ambient = { 0.1f, 0.1f, 0.1f, 0.1f };
	mLight.diffuse ={ 1.0f, 1.0f, 1.0f, 1.0f };
	mLight.specular = {1.0f, 1.0f, 1.0f, 1.0f };

	mMaterial.ambient = { 1.0f ,1.0f,1.0f ,1.0f };
	mMaterial.diffuse = { 0.65f, 0.65f, 0.65f,0.65f };
	mMaterial.specular = { 1.0f ,1.0f ,1.0f ,1.0f };
	mMaterial.power = 10;

	// Update matrices
	TransformData data;
	data.world = Math::Transpose(world);
	data.wvp = Math::Transpose(world * view * projection);
	data.cameraPosition = Math::Vector4(mCamera.GetPosition(), 1);
	data.light = mLight;
	data.material = mMaterial;
	data.displacementFactor = 0.3f;
	//data.useTextureBool = true;
	mDiffuseMap.BindVS(0);
	mDiffuseMap.BindPS(0);
	mSpecularMap.BindPS(1);
	
	mNormalMap.BindPS(2);
	mDisplacementMap.BindVS(3);
	mSampler.BindVS(0);
	mSampler.BindPS(0);
	mConstantBuffer.Set(data);
	mConstantBuffer.BindVS(0);
	mConstantBuffer.BindPS(0);
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

//create a class called meshbuilder
{
public:
static void CreateCube(Mesh& mesh); 
static void CreateSphere(Mesh& mesh); // for ring sphere specify how many rings and slices


*/