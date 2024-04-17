
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
	Graphics::MeshBuilder::CreateCube(mCubeMesh, { 0,1,0 });
	Graphics::MeshBuilder::CreatePlane(mPlaneMesh, 50, 50, 20);
	Graphics::MeshBuilder::CreateCylinder(mCylinderMesh, 1.0f, 50, 3);
	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 5.0f, -25.0f });
	mConstantBuffer.Initialize();
	mPlaneDiffuseMap.Initialize("../Assets/Textures/Blue.jpg");
	mCylinDiffuseMap.Initialize("../Assets/Textures/Green.jpg");
	mCubeDiffuseMap.Initialize("../Assets/Textures/Checkerboard.jpg");
	mSampler.Initialize(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Clamp);
	mVertexShader.Initialize(L"../Assets/Shaders/Standard.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/Standard.fx", "PS", "ps_5_0", Graphics::Vertex::Format);
	mPlaneMeshBuffer.Initialize(mPlaneMesh, false);
	mCylinderMeshBuffer.Initialize(mCylinderMesh, false);
	mCubeMeshBuffer.Initialize(mCubeMesh, false);

	mBones.resize(3);
	mBoneOffsets.reserve(3);
	mBoneAngles.reserve(3);
	mBoneWorldTransform.resize(3);
	mBoneTransforms.resize(3);

	mBoneTransforms[0].SetScale({ 1.0f,2.0f,1.0f });
	for (uint32_t i = 0; i < mBones.size(); i++)
	{
		if (i != 0)
		{
			mBoneTransforms[i].SetScale({ 1.0f, 1.0f, 1.0f });
		}

		mBoneTransforms[i].SetPosition({0.0f, 2.0f, 0.0f});
		mBones[i].transform = mBoneTransforms[i].GetTransform();
		mBoneOffsets.push_back(Math::Vector3{0,static_cast<float>(i),0});
	}

	//mBoneTransforms[0].SetRotation({ 0, 0, Math::kPi });
	//mBones[0].transform = mBoneTransforms[0].GetTransform();

	const auto lightDir = Math::Normalize({ 0.0f,-1.0f,1.0f });
	mLight.direction = { lightDir, 1.0f };
	mLight.ambient = { 0.3f, 0.3f, 0.3f, 0.3f };
	mLight.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void GameApp::OnTerminate()
{
	mCubeMeshBuffer.Terminate();
	mCylinderMeshBuffer.Terminate();
	mPlaneMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mSampler.Terminate();
	mCubeDiffuseMap.Terminate();
	mCylinDiffuseMap.Terminate();
	mPlaneDiffuseMap.Terminate();
	mCubeMesh.Destroy(); 
	mPlaneMesh.Destroy();
	mCylinderMesh.Destroy();

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
	{
		mCamera.Walk(dt * moveSpeed);
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::S))
	{
		mCamera.Walk(dt * -moveSpeed);
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::D))
	{
		mCamera.Strafe(dt * moveSpeed);
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::A))
	{
		mCamera.Strafe(dt * -moveSpeed);
	}
	mCamera.Yaw(inputSystem->GetMouseMoveX() * dt * turnSpeed);
	mCamera.Pitch(inputSystem->GetMouseMoveY() * dt * turnSpeed);

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

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

	// Bind the input layout, vertex shader, and pixel shader
	mVertexShader.Bind();
	mPixelShader.Bind();
	Math::Matrix4 rotation = Math::Matrix4::RotationX(rotationx) * Math::Matrix4::RotationY(rotationy);
	Math::Matrix4 world = rotation;
	Math::Matrix4 view = mCamera.GetViewMatrix();
	Math::Matrix4 projection = mCamera.GetPerspectiveMatrix();



	if(inputSystem->IsKeyDown(SWGE::Input::KeyCode::THREE))
	{
		change = 0;
	}
	if(inputSystem->IsKeyDown(SWGE::Input::KeyCode::ONE))
	{
		change = 1;
	}
	if(inputSystem->IsKeyDown(SWGE::Input::KeyCode::TWO))
	{
		change = 2;
	}
	Math::Vector3 tempCubeScale;
	tempCubeScale.One();
	if(change == 0)
	{
		static float c0rotationx = 0.0f;
		static float c0rotationy = 0.0f;
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::LEFT))
		{
			c0rotationy += 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::RIGHT))
		{
			c0rotationy -= 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::DOWN))
		{
			c0rotationx += 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::UP))
		{
			c0rotationx -= 0.1f;
		}

		mBoneTransforms[0].SetRotation({ c0rotationx, 0.0f , c0rotationy });
		mBones[0].transform = mBoneTransforms[0].GetTransform();
	}
	if (change == 1)
	{
		static float c1rotationx = 0.0f;
		static float c1rotationy = 0.0f;
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::LEFT))
		{
			c1rotationy += 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::RIGHT))
		{
			c1rotationy -= 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::DOWN))
		{
			c1rotationx += 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::UP))
		{
			c1rotationx -= 0.1f;
		}
		mBoneTransforms[1].SetRotation({ c1rotationx, 0.0f, c1rotationy });
		mBones[1].transform = mBoneTransforms[1].GetTransform();
	}
	if (change == 2)
	{
		static float c2rotationx = 0.0f;
		static float c2rotationy = 0.0f;
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::LEFT))
		{
			c2rotationy += 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::RIGHT))
		{
			c2rotationy -= 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::DOWN))
		{
			c2rotationx += 0.1f;
		}
		if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::UP))
		{
			c2rotationx -= 0.1f;
		}
		mBoneTransforms[2].SetRotation({ c2rotationx, 0.0f, c2rotationy });
		mBones[2].transform = mBoneTransforms[2].GetTransform();
	}

	Math::Matrix4 tempMat = Math::Matrix4::Identity();
	for (uint32_t i = 0; i < mBones.size(); ++i)
	{	
		tempMat = mBones[i].transform * tempMat;
		mBoneWorldTransform[i] = tempMat;
	}

	//Math::Matrix4 matOffset = Math::Matrix4::Identity();
	//for (uint32_t i = 0; i < mBones.size(); ++i)
	//{
	//	Math::Matrix4 parentTransform = Math::Matrix4::Identity();
	//	Bone* parent = mBones[i].Parent;
	//	while (parent)
	//	{
	//		parentTransform = parentTransform * parent->transform;
	//		parent = parent->Parent;
	//	}
	//	mBoneWorldTransform[i] = parentTransform * mBones[i].transform;

	//	matOffset = Math::Matrix4::Translation(-mBoneOffsets[i]) * matOffset;
	//	//mSkinningTransform;
	//}

	auto context = graphicsSystem->GetContext();
	// Update matrices

	//data.useTextureBool = true;
	TransformData data;

	data.world = Math::Transpose(world);
	data.wvp = Math::Transpose(world * view * projection);
	data.cameraPosition = Math::Vector4(mCamera.GetPosition(), 1);
	data.light = mLight;
	data.material = mMaterial;
	data.displacementFactor = 0.3f;
	mSampler.BindVS(0);
	mSampler.BindPS(0);
	mConstantBuffer.BindVS(0);
	mConstantBuffer.BindPS(0);
	mConstantBuffer.Set(data);
	 
	Math::Matrix4 tempMatrix;
	Math::Vector3 tempTranslation = {0.0f, 1.0f, 0.0f};
	Math::Vector3 tempScale = { 1.0, 1.0, 1.0f };

	tempMatrix = (tempMatrix.Scaling(tempScale) * tempMatrix.Translation(tempTranslation));
	data.world = Math::Transpose(tempMatrix);
	data.wvp = Math::Transpose(tempMatrix * view * projection);
	mPlaneDiffuseMap.BindVS(0);
	mPlaneDiffuseMap.BindPS(0);
	mConstantBuffer.Set(data);
	mPlaneMeshBuffer.Render();

	tempScale = { 1.0f, 0.5f, 1.0f };
	for (uint32_t i = 0; i < mBones.size(); i++)
	{
		tempMatrix = mBoneWorldTransform[i]; //mBoneOffsetTransform *;
		data.wvp = Math::Transpose(tempMatrix * view * projection);
		mCubeDiffuseMap.BindVS(0);
		mCubeDiffuseMap.BindPS(0);
		mConstantBuffer.Set(data);
		mCubeMeshBuffer.Render();
	}

	tempTranslation = { 5.0f, 2.0f, 0.0f };
	tempMatrix = (tempMatrix.Scaling(tempScale) * tempMatrix.Translation(tempTranslation));
	data.world = Math::Transpose(tempMatrix);
	data.wvp = Math::Transpose(tempMatrix * view * projection);
	mCylinDiffuseMap.BindVS(0);
	mCylinDiffuseMap.BindPS(0);
	mConstantBuffer.Set(data);
	mCylinderMeshBuffer.Render();

	graphicsSystem->EndRender();
}

/*

*Fabrik*

Math::Vector3 Start;
Math::Vector3 End;

Math::Vector3 BonePos[3];


*/
 