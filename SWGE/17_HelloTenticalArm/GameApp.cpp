#include "GameApp.h"

using namespace SWGE;
namespace
{
Graphics::MaterialNode* tempMat = nullptr;
static const Graphics::VertexPT kVertices[]
{
	{ SWGE::Math::Vector3(-1.0f, 1.0f,	0.0f), SWGE::Math::Vector2(0.0f, 0.0f) },	//top left 0 
	{ SWGE::Math::Vector3(1.0f,	1.0f,	0.0f), SWGE::Math::Vector2(1.0f, 0.0f) },	//top right 1
	{ SWGE::Math::Vector3(1.0f,  -1.0f,	0.0f), SWGE::Math::Vector2(1.0f,1.0f) },	//bot right 2
	{ SWGE::Math::Vector3(-1.0f, -1.0f,	0.0f), SWGE::Math::Vector2(0.0f,1.0f) },	//bot left 3
};
uint32_t kIndices[]
{
	0,1,2,
	0,2,3
};
const int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);
const int kVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);


}
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
	mColorFormat = Graphics::ColorFormat::RGBA_U8;
	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();
	debugDepthData debugDepthDATA;
	debugDepthDATA.farPlane = 200.0f;
	debugDepthDATA.nearPlane = 1.0f;

	Graphics::MeshBuilder::CreatePlane(mPlane, 100, 100, 50);
	Graphics::MeshBuilder::CreateCylinderSkinned(mSkinnedCylinder, 1, 50, 50);

	mMeshBuffer.Initialize(mPlane,false);
	mSkinCylinMeshBuffer.Initialize(mSkinnedCylinder, false);

	mRenderMeshBuffer.Initialize(kVertices, sizeof(Graphics::VertexPT), kVertexCount, kIndices, kIndexCount);

	//Initialize Standard Shader
	mVertexShader.Initialize(L"../Assets/Shaders/StandardShadow.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/StandardShadow.fx", "PS", "ps_5_0", Graphics::Vertex::Format);

	//Initialize Post Processing Shader
	mPostProcessVertexShader.Initialize(L"../Assets/Shaders/StandardShadow.fx", "VS", "vs_5_0", Graphics::VertexPT::Format);
	mPostProcessPixelShader.Initialize(L"../Assets/Shaders/StandardShadow.fx", "PS", "ps_5_0", Graphics::VertexPT::Format);

	//Initialize DepthMap Shader
	mDepthVertexShader.Initialize(L"../Assets/Shaders/DepthMap.fx", "VS", "vs_5_0", Graphics::Vertex::Format);

	//Set Light
	const auto lightDir = Math::Normalize({ 0.0f,-1.0f,1.0f });
	mLight.direction = { lightDir, 1.0f };
	mLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mLight.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	//Set Material
	mMaterial.ambient = { 0.2f ,0.2f, 0.2f ,1.0f };
	mMaterial.diffuse = { 0.65f, 0.65f, 0.65f,0.65f };
	mMaterial.specular = { 1.0f ,1.0f ,1.0f ,1.0f };
	mMaterial.power = 10;
	mMaterial.displacementFactor = 0.35f;

	//Set Camera
	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 15.0f, -75.0f });
	mCamera.Pitch(10);

	//Set Depth Camera --- Should be set to what the light direction is
	mDepthCamera.SetDirection({ mLight.direction.x, mLight.direction.y, mLight.direction.z });//These relate to the lights position and direction
	mDepthCamera.SetPosition({ -lightDir * 50.0f });
	mDepthCamera.Pitch(10);
	mDepthCamera.SetFarPlane(100.0f);

	//Create Nodes
	auto cameraNode = mSceneManager.CreateCameraNode(mCamera);
	auto depthCameraNode = mSceneManager.CreateCameraNode(mDepthCamera, true, true);
	auto depthMapNode = mSceneManager.CreateDepthMapNode();
	auto depthMapTextureNode = mSceneManager.CreateTextureNode();
	auto depthMapShaderNode = mSceneManager.CreateShaderNode();
	auto depthMapSamplerNode = mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Wrap, 1);
	auto emptyNode = mSceneManager.CreateEmptySceneNode();
	auto lightNode = mSceneManager.CreateLightNode(mLight);
	auto materialNode = mSceneManager.CreateMaterialNode(mMaterial);
	auto planeMeshNode = mSceneManager.CreateMeshNode();
	auto planeTextureNode = mSceneManager.CreateTextureNode();
	auto planeTransformNode = mSceneManager.CreateTransformNode();
	auto ppSamplerNode = mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Wrap, 0);
	auto ppQuadMeshNode = mSceneManager.CreateMeshNode();
	auto ppShaderNode = mSceneManager.CreateShaderNode();
	auto rasterizerStateNode = mSceneManager.CreateRasterizerStateNode();
	auto samplerNode = mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Wrap, 0);
	auto shaderNode = mSceneManager.CreateShaderNode();
	auto skinnedCylinMeshNode = mSceneManager.CreateMeshNode();
	auto skinnedCylinTextureNode = mSceneManager.CreateTextureNode();
	mTransformNode = mSceneManager.CreateTransformNode();
	
	depthCameraNode->SetIndex(7);
	
	//Set ShaderNodes
	depthMapShaderNode->SetVertexShader(&mDepthVertexShader);
	ppShaderNode->SetPixelShader(&mPostProcessPixelShader);
	ppShaderNode->SetVertexShader(&mPostProcessVertexShader);
	shaderNode->SetPixelShader(&mPixelShader);
	shaderNode->SetVertexShader(&mVertexShader);

	//Set Mesh Nodes
	ppQuadMeshNode->SetRenderMesh(&mRenderMeshBuffer);
	planeMeshNode->SetRenderMesh(&mMeshBuffer);

	depthMapNode->Initialize(graphicsSystem->GetWidth() * 4, graphicsSystem->GetHeight() * 4);
	rasterizerStateNode->Initialize(Graphics::CullMode::Back, Graphics::FillMode::WireFrame);

	mPlaneTexture.Initialize("../Assets/Textures/Green.jpg");
	mDuckModel.LoadModel("../Assets/Models/duck.swge");
	
	mDepthTexture.Initialize(depthMapNode->GetDepthMap());

	depthMapTextureNode->SetTexture(&mDepthTexture, true);
	depthMapTextureNode->SetIndex(4);
	planeTextureNode->SetTexture(&mPlaneTexture);
	planeTextureNode->SetIndex(0);

	mSceneManager.SetRoot(emptyNode);

	mDuckModel.Initialize(mSceneManager);
	auto modelNode = mDuckModel.GetRootNode();

	//First Branch --- DepthMap stuff Here
	emptyNode->AddChild(cameraNode);
	cameraNode->AddChild(depthCameraNode);
	depthCameraNode->AddChild(depthMapNode);
	depthMapNode->AddChild(depthMapShaderNode);
	depthMapShaderNode->AddChild(mTransformNode);
	mTransformNode->AddChild(modelNode);

	//Second Main Branch --- Scene Stuff
	depthCameraNode->AddChild(depthMapTextureNode);
	depthMapTextureNode->AddChild(shaderNode);
	shaderNode->AddChild(lightNode);
	shaderNode->AddChild(depthMapSamplerNode);
	shaderNode->AddChild(samplerNode);
	samplerNode->AddChild(materialNode);
	//Plane
	materialNode->AddChild(planeTextureNode);
	planeTextureNode->AddChild(planeTransformNode);
	planeTransformNode->AddChild(planeMeshNode);
	planeTransformNode->GetTransform().SetPosition({ 0.0f,0.5f,0.0f });
	//Model
	samplerNode->AddChild(mTransformNode);
	mTransformNode->AddChild(rasterizerStateNode);
	rasterizerStateNode->AddChild(modelNode);
	mTransformNode->GetTransform().SetScale({ 0.05f, 0.05f,0.05f });

}

void GameApp::OnTerminate()
{
	mSceneManager.Purge();
	mDepthTexture.Terminate();
	mRenderTargetTexture.Terminate();
	mPlaneTexture.Terminate();
	mRenderMeshBuffer.Terminate();
	mSkinCylinMeshBuffer.Terminate();
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mPostProcessPixelShader.Terminate();
	mPostProcessVertexShader.Terminate();
	mDepthVertexShader.Terminate();
	mSkinnedCylinder.Destroy();
	mPlane.Destroy();
	mDuckModel.Destroy();

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
	float rotSpeed = 5.0f;
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::RIGHT))
	{
		auto& transform = mTransformNode->GetTransform();
		auto rot = transform.GetRotation();
		rot.y += rotSpeed * dt;
		transform.SetRotation(rot);
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::LEFT))
	{
		auto& transform = mTransformNode->GetTransform();
		auto rot = transform.GetRotation();
		rot.y -= rotSpeed * dt;
		transform.SetRotation(rot);
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::UP))
	{
		auto& transform = mTransformNode->GetTransform();
		auto rot = transform.GetRotation();
		rot.x += rotSpeed * dt;
		transform.SetRotation(rot);
	}
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::DOWN))
	{
		auto& transform = mTransformNode->GetTransform();
		auto rot = transform.GetRotation();
		rot.x -= rotSpeed * dt;
		transform.SetRotation(rot);
	}

	mSceneManager.Update(dt);

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();
	mSceneManager.Render();
	graphicsSystem->EndRender();
}
