
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
	Graphics::MeshBuilder::CreateUVSphere(mUVSphereMesh, 200, 200);
	Graphics::MeshBuilder::CreateSkyBox(mSkyboxMesh);

	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 0.0f, -500.0f });

	mLight.direction = { -Math::Vector3::YAxis(), 0.0f };
	mLight.ambient = { 0.5f, 0.5f, 0.5f, 0.5f };
	mLight.diffuse = {0.7f, 0.7f, 0.7f, 0.7f };
	mLight.specular = {0.2f, 0.2f, 0.2f, 0.2f };
	
	mSkyboxMaterial.specular = Math::Vector4::Black();

	mSkyboxTexture.Initialize("../Assets/Textures/Stars.png");
	//Sun Initialize
	mSphereTexture[0].Initialize("../Assets/Textures/Sun.jpg");
	mScale[0] = { 190.0f, 190.0f, 190.0f };
	mTranslation[0] = { 0.0f,0.0f,0.0f };
	//Mercury Initialize
	mSphereTexture[1].Initialize("../Assets/Textures/Mercury.jpg");
	mScale[1] = { 3.8f, 3.8f, 3.8f };
	mTranslation[1] = { 1124.1f,0,0 };
	//Venus Initialize
	mSphereTexture[2].Initialize("../Assets/Textures/Venus.jpg");
	mScale[2] = { 9.5f, 9.5f, 9.5f };
	mTranslation[2] = { 1627.0f, 0, 0 };
	//Earth Initialize
	mSphereTexture[3].Initialize("../Assets/Textures/Earth.jpg");
	mScale[3] = { 10.0f, 10.0f, 10.0f };
	mTranslation[3] = { 2041.0f, 0, 0 };
	//Mars Initialize
	mSphereTexture[4].Initialize("../Assets/Textures/Mars.jpg");
	mScale[4] = { 5.3f, 5.3f, 5.3f };
	mTranslation[4] = { 2824.0f, 0, 0 };
	//Jupiter Initialize
	mSphereTexture[5].Initialize("../Assets/Textures/Jupiter.jpg");
	mScale[5] = { 112.0f, 112.0f, 112.0f };
	mTranslation[5] = { 8330.0f, 0, 0 };
	//Saturn Initialize
	mSphereTexture[6].Initialize("../Assets/Textures/Saturn.jpg");
	mScale[6] = { 94.5f, 94.5f, 94.5f };
	mTranslation[6] = { 14835.0f, 0, 0 };
	//Uranus Initialize
	mSphereTexture[7].Initialize("../Assets/Textures/Uranus.png");
	mScale[7] = { 40.0f, 40.0f, 40.0f };
	mTranslation[7] = { 29255.0f, 0, 0 };
	//Neptune Initialize
	mSphereTexture[8].Initialize("../Assets/Textures/Neptune.png");
	mScale[8] = { 38.8f, 38.8f, 38.8f };
	mTranslation[8] = { 45525.0f, 0, 0 };

	mVertexShader.Initialize(L"../Assets/Shaders/Lighting.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/Lighting.fx", "PS", "ps_5_0", Graphics::Vertex::Format);

	mSampler.Initialize(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Clamp);

	mMeshBufferCube.Initialize(mCubeMesh, true);
	mMeshBufferSphere.Initialize(mUVSphereMesh, true);
	mMeshBufferSkybox.Initialize(mSkyboxMesh, true);
	mConstantBuffer.Initialize();

}

void GameApp::OnTerminate()
{
	mMeshBufferCube.Terminate();
	mMeshBufferSkybox.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mSampler.Terminate();
	mMeshBufferSphere.Terminate();
	for (size_t i = 0; i < 9; i++)
	{
		mSphereTexture[i].Terminate();
	}
	mSkyboxTexture.Terminate();
	mCubeMesh.Destroy();
	mUVSphereMesh.Destroy();
	mSkyboxMesh.Destroy();

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
	auto DeltaTime = mTimer.GetElapsedTime();

	auto inputSystem = Input::InputSystem::Get();
	inputSystem->Update();

	if (inputSystem->IsKeyPressed(SWGE::Input::KeyCode::ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}

	const float moveSpeed = 500.0f;
	const float turnSpeed = 10.0f;
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::W))
		mCamera.Walk(DeltaTime * moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::S))
		mCamera.Walk(DeltaTime * -moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::D))
		mCamera.Strafe(DeltaTime * moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::A))
		mCamera.Strafe(DeltaTime * -moveSpeed);
	mCamera.Yaw(inputSystem->GetMouseMoveX() * DeltaTime * turnSpeed);
	mCamera.Pitch(inputSystem->GetMouseMoveY() * DeltaTime * turnSpeed);

	static float rotationx = 0.0f;
	static float rotationy = 0.0f;
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::LEFT))
	{
		rotationx += 0.1f;
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::RIGHT))
	{
		rotationx -= 0.1f;
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::DOWN))
	{
		rotationy += 0.1f;
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::UP))
	{
		rotationy -= 0.1f;
	}
	static float rotation = rotationx * rotationy;
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

	// Bind the input layout, vertex shader, and pixel shader
	mVertexShader.Bind();
	mPixelShader.Bind();

	Math::Matrix4 Rotation = Math::Matrix4::RotationY(rotationx) * Math::Matrix4::RotationX(rotationy);

	//Math::Matrix4 world = Rotation;
	Math::Matrix4 view = mCamera.GetViewMatrix();
	Math::Matrix4 projection = mCamera.GetPerspectiveMatrix();

	auto context = graphicsSystem->GetContext();

	// Update matrices

	Math::Matrix4 CubeWorld;
	Math::Matrix4 SkyboxWorld;

	TransformData data;
	
		data.cameraPosition = Math::Vector4(mCamera.GetPosition(), 1);
		data.useTextureBool = true;
		data.material = mSkyboxMaterial;
		data.light = mLight;
        SkyboxWorld = Math::Matrix4::Translation(mCamera.GetPosition());
		data.world = SkyboxWorld;
		data.wvp = Math::Transpose(SkyboxWorld * view * projection);
		mSkyboxTexture.BindVS(0);
		mSkyboxTexture.BindPS(0);
		mSampler.BindVS(0);
		mSampler.BindPS(0);
		mConstantBuffer.BindVS(0);
		mConstantBuffer.BindPS(0);
		mConstantBuffer.Set(data);
		mMeshBufferSkybox.Render();

		//data.world = Math::Transpose(world);
		data.material = mMaterial;

		for (size_t i = 0; i < 9; i++)
		{
			Math::Matrix4 planetMatrix; 
			planetMatrix = planetMatricies[i].Scaling(mScale[i]) * planetMatricies[i].Translation(mTranslation[i]);
			planetMatrix = planetMatrix * Rotation;
			data.world = Math::Transpose(planetMatrix);
			data.wvp = Math::Transpose(planetMatrix * view * projection);
			mSphereTexture[i].BindVS(0);
			mSphereTexture[i].BindPS(0);
			mConstantBuffer.Set(data);
			mMeshBufferSphere.Render();
		}



	
	graphicsSystem->EndRender();
}

