#include "GameApp.h"

using namespace SWGE;
namespace
{
Graphics::MaterialNode* tempMat = nullptr;
	static const Graphics::VertexPT kVertices[]
	{
		{SWGE::Math::Vector3(-1.0f, 1.0f,	0.0f), SWGE::Math::Vector2(0.0f, 0.0f)},	//top left 0 
		{SWGE::Math::Vector3(1.0f,	1.0f,	0.0f), SWGE::Math::Vector2(1.0f, 0.0f)},	//top right 1
		{SWGE::Math::Vector3(1.0f,  -1.0f,	0.0f), SWGE::Math::Vector2(1.0f,1.0f) },	//bot right 2
		{SWGE::Math::Vector3(-1.0f, -1.0f,	0.0f), SWGE::Math::Vector2(0.0f,1.0f) },	//bot left 3
	};
	const int kVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);

	uint32_t kIndices[]
	{
		0,1,2,
		0,2,3
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
	mWindow.Initialize(GetInstance(), GetAppName(), 720, 720);
	mTimer.Initialize();
	mColorFormat = Graphics::ColorFormat::RGBA_U8;
	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();

	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 0.0f, -25.0f });

	mMeshBuffer.Initialize(kVertices, sizeof(Graphics::VertexPT), kVertexCount, kIndices, kIndexCount);


	mVertexShader.Initialize(L"../Assets/Shaders/SimpleModel.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/SimpleModel.fx", "PS", "ps_5_0", Graphics::Vertex::Format);

	mPostProcessVertexShader.Initialize(L"../Assets/Shaders/PostProcessing.fx", "VS", "vs_5_0", Graphics::VertexPT::Format);
	mPostProcessPixelShader.Initialize(L"../Assets/Shaders/PostProcessing.fx", "PS", "ps_5_0", Graphics::VertexPT::Format);

	mDuckModel.LoadModel("../Assets/Models/duck.swge");

	mLight.direction = { Math::Vector3::ZAxis(), 0.0f };
	mLight.ambient = { 0.5f, 0.5f, 0.5f, 0.5f };
	mLight.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	mMaterial.ambient = { 1.0f ,1.0f,1.0f ,1.0f };
	mMaterial.diffuse = { 0.65f, 0.65f, 0.65f,0.65f };
	mMaterial.specular = { 1.0f ,1.0f ,1.0f ,1.0f };
	mMaterial.power = 10;
	mMaterial.displacementFactor = 0.35f;

	auto emptyNode = mSceneManager.CreateEmptySceneNode();
	auto cameraNode = mSceneManager.CreateCameraNode(mCamera);
	mTransformNode = mSceneManager.CreateTransformNode();
	auto lightNode = mSceneManager.CreateLightNode(mLight);
	auto materialNode = mSceneManager.CreateMaterialNode(mMaterial);
	auto samplerNode = mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Clamp, 0);
	auto shaderNode = mSceneManager.CreateShaderNode();
	auto renderTargetNode = mSceneManager.CreateRenderTargetNode();
	auto renderTextureNode = mSceneManager.CreateTextureNode();
	auto rasterizerStateNode = mSceneManager.CreateRasterizerStateNode();

	auto ppSamplerNode = mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Clamp, 0);
	auto quadMeshNode = mSceneManager.CreateMeshNode();
	auto ppShaderNode = mSceneManager.CreateShaderNode();

	ppShaderNode->SetPixelShader(&mPostProcessPixelShader);
	ppShaderNode->SetVertexShader(&mPostProcessVertexShader);

	quadMeshNode->SetRenderMesh(&mMeshBuffer);

	mSceneManager.SetRoot(emptyNode);

	shaderNode->SetPixelShader(&mPixelShader);
	shaderNode->SetVertexShader(&mVertexShader);

	rasterizerStateNode->Initialize(Graphics::CullMode::Back, Graphics::FillMode::Solid);

	renderTargetNode->Initialize(graphicsSystem->GetWidth(), graphicsSystem->GetHeight(), mColorFormat);
	mRenderTargetTexture.Initialize(renderTargetNode->GetRenderTarget());
	renderTextureNode->SetIndex(0);
	renderTextureNode->SetTexture(&mRenderTargetTexture, true);
	mDuckModel.Initialize(mSceneManager);
	auto modelNode = mDuckModel.GetRootNode();

	emptyNode->AddChild(renderTargetNode);
	renderTargetNode->AddChild(cameraNode);
	cameraNode->AddChild(shaderNode);
	shaderNode->AddChild(samplerNode);
	samplerNode->AddChild(lightNode);
	lightNode->AddChild(materialNode);
	materialNode->AddChild(mTransformNode);
	mTransformNode->AddChild(rasterizerStateNode);
	rasterizerStateNode->AddChild(modelNode);
	mTransformNode->GetTransform().SetScale({ 0.05f, 0.05f,0.05f });

	
	emptyNode->AddChild(renderTextureNode);
	renderTextureNode->AddChild(ppShaderNode);
	ppShaderNode->AddChild(ppSamplerNode);
	ppSamplerNode->AddChild(quadMeshNode);

}

void GameApp::OnTerminate()
{
	mSceneManager.Purge();
	mRenderTargetTexture.Terminate();
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
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
