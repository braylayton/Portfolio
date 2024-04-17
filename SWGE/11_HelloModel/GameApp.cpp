#include "GameApp.h"

using namespace SWGE;
namespace
{
Graphics::MaterialNode* tempMat = nullptr;
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

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();

	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 0.0f, -25.0f });

	mVertexShader.Initialize(L"../Assets/Shaders/SimpleModel.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/SimpleModel.fx", "PS", "ps_5_0", Graphics::Vertex::Format);

	mDuckModel.LoadModel("../Assets/Models/duck.swge");
	mElyModel.LoadModel("../Assets/Models/ely.swge");

	mLight.direction = { Math::Vector3::ZAxis(), 0.0f };
	mLight.ambient = { 0.5f, 0.5f, 0.5f, 0.5f };
	mLight.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	mMaterial.ambient = { 1.0f ,1.0f,1.0f ,1.0f };
	mMaterial.diffuse = { 0.65f, 0.65f, 0.65f,0.65f };
	mMaterial.specular = { 1.0f ,1.0f ,1.0f ,1.0f };
	mMaterial.power = 10;
	mMaterial.displacementFactor = 0.35f;

	auto cameraNode = mSceneManager.CreateCameraNode(mCamera);
	mTransformNode = mSceneManager.CreateTransformNode();
	auto lightNode = mSceneManager.CreateLightNode(mLight);
	auto materialNode = mSceneManager.CreateMaterialNode(mMaterial);
	auto samplerNode = mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Clamp, 0);
	auto shaderNode = mSceneManager.CreateShaderNode();

	mSceneManager.SetRoot(cameraNode);

	shaderNode->SetPixelShader(&mPixelShader);
	shaderNode->SetVertexShader(&mVertexShader);

	mDuckModel.Initialize(mSceneManager);
	mElyModel.Initialize(mSceneManager);
	auto modelNode = mDuckModel.GetRootNode();
	auto animModelNode = mElyModel.GetRootNode();

	cameraNode->AddChild(shaderNode);
	shaderNode->AddChild(samplerNode);
	samplerNode->AddChild(lightNode);
	lightNode->AddChild(materialNode);
	materialNode->AddChild(mTransformNode);
	mTransformNode->AddChild(animModelNode);
	mTransformNode->GetTransform().SetScale({ 0.05f, 0.05f,0.05f });

}

void GameApp::OnTerminate()
{
	mSceneManager.Purge();
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
