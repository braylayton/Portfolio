#include "GameApp.h"

using namespace SWGE;
namespace
{
Graphics::MaterialNode* tempMat = nullptr;
static const Graphics::VertexPT kVertices[]
{
	{ SWGE::Math::Vector3(-1.0f, 1.0f,	0.0f), SWGE::Math::Vector2(0.0f, 0.0f) },	//top left	0 
	{ SWGE::Math::Vector3(1.0f,	1.0f,	0.0f), SWGE::Math::Vector2(1.0f, 0.0f) },	//top right 1
	{ SWGE::Math::Vector3(1.0f,  -1.0f,	0.0f), SWGE::Math::Vector2(1.0f,1.0f)  },	//bot right 2
	{ SWGE::Math::Vector3(-1.0f, -1.0f,	0.0f), SWGE::Math::Vector2(0.0f,1.0f)  },	//bot left	3
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
	PostProcessingData ppData;
	ppData.screenWidth = (float)graphicsSystem->GetWidth();
	ppData.screenHeight = (float)graphicsSystem->GetHeight();
	ppData.lineThickness = 0.3f;
	ppData.lineColor = Math::Vector4::Black();

	const float uiQuadWidth = 0.35f;
	const float uiQuadHeight = uiQuadWidth * graphicsSystem->GetAspectRatio();
	const Graphics::VertexPT uiVertices[] =
	{
		{ { -1.0f,					-1.0f,						0.0f },{ 0.0f , 1.0f } },
		{ { -1.0f,					-1.0f + uiQuadHeight,		0.0f },{ 0.0f , 0.0f } },
		{ { -1.0f + uiQuadWidth,	-1.0f + uiQuadHeight,		0.0f },{ 1.0f , 0.0f } },
		{ { -1.0f + uiQuadWidth,	-1.0f,						0.0f },{ 1.0f , 1.0f } },
	};

	Graphics::MeshBuilder::CreatePlane(mPlane, 100, 100, 50);

	mMeshBuffer.Initialize(mPlane,false);
	mRenderMeshBuffer.Initialize(kVertices, sizeof(Graphics::VertexPT), kVertexCount, kIndices, kIndexCount);
	mUIQuadMeshBuffer.Initialize(uiVertices, sizeof(Graphics::VertexPT), (uint32_t)std::size(uiVertices), kIndices, kIndexCount);
	//Initialize Standard Shader
	mVertexShader.Initialize(L"../Assets/Shaders/StandardShadow.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/StandardShadow.fx", "PS", "ps_5_0", Graphics::Vertex::Format);
	//Initialize Post Processing Shader

	mPostProcessVertexShader.Initialize(L"../Assets/Shaders/PostProcessing.fx", "OutlineVertexShader", "vs_5_0", Graphics::VertexPT::Format);
	mPostProcessPixelShader.Initialize(L"../Assets/Shaders/PostProcessing.fx", "OutlinePixelShader", "ps_5_0", Graphics::VertexPT::Format);
	
	mPostProcessVertexShader2.Initialize(L"../Assets/Shaders/PostProcessing.fx", "VS", "vs_5_0", Graphics::VertexPT::Format);
	mPostProcessPixelShader2.Initialize(L"../Assets/Shaders/PostProcessing.fx", "PS", "ps_5_0", Graphics::VertexPT::Format);


	//Initialize DepthMap Shader
	mDepthVertexShader.Initialize(L"../Assets/Shaders/DepthMap.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	//mDepthPixelShader.Initialize(L"../Assets/Shaders/DepthMap.fx", "PS", "ps_5_0", Graphics::VertexPT::Format);

	//Initialize DepthMap_Debug Shader
	mUIVertexShader.Initialize(L"../Assets/Shaders/DepthMap.fx", "VSDebug", "vs_5_0", Graphics::VertexPT::Format);
	mUIPixelShader.Initialize(L"../Assets/Shaders/DepthMap.fx", "PSDebug", "ps_5_0", Graphics::VertexPT::Format);

	//Set Light
	const auto lightDir = Math::Normalize({ 0.0f,-1.0f,1.0f });
	mLight.direction = { lightDir, 1.0f };
	mLight.ambient = { 0.4f, 0.4f, 0.4f, 1.0f };
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
	//auto debugDepthMapNode = mSceneManager.CreateDepthMapNode();
	auto debugTextureNode =		mSceneManager.CreateTextureNode();
	auto depthCameraNode =		mSceneManager.CreateCameraNode(mDepthCamera, true, true);
	auto depthMapNode =			mSceneManager.CreateDepthMapNode();
	auto depthMapTextureNode =	mSceneManager.CreateTextureNode();
	auto depthMapShaderNode =	mSceneManager.CreateShaderNode();
	auto depthMapSamplerNode =	mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Wrap, 1);
	auto emptyNode =			mSceneManager.CreateEmptySceneNode();
	auto lightNode =			mSceneManager.CreateLightNode(mLight);
	auto materialNode =			mSceneManager.CreateMaterialNode(mMaterial);
	auto planeMeshNode =		mSceneManager.CreateMeshNode();
	auto planeTextureNode =		mSceneManager.CreateTextureNode();
	auto planeTransformNode =	mSceneManager.CreateTransformNode();
	auto ppSamplerNode =		mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Wrap, 0);
	auto ppQuadMeshNode =		mSceneManager.CreateMeshNode();
	auto ppShaderNode =			mSceneManager.CreateShaderNode();
	auto ppShaderNode2 =		mSceneManager.CreateShaderNode();
	auto renderTargetNode =		mSceneManager.CreateRenderTargetNode();
	auto renderTextureNode =	mSceneManager.CreateTextureNode();
	auto rasterizerStateNode =	mSceneManager.CreateRasterizerStateNode();
	auto samplerNode =			mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Wrap, 0);
	auto shaderNode =			mSceneManager.CreateShaderNode();
	mTransformNode =			mSceneManager.CreateTransformNode();
	auto ConstantBufferNode =	mSceneManager.CreateConstantBufferNode();
	auto uiMeshNode =			mSceneManager.CreateMeshNode();
	auto uiSamplerNode =		mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Wrap, 0);
	auto uiShaderNode =			mSceneManager.CreateShaderNode();

	depthCameraNode->SetIndex(7);
	ConstantBufferNode->Initialize(sizeof(PostProcessingData), Graphics::ShaderStage::Vertex | Graphics::ShaderStage::Pixel, 8);
	ConstantBufferNode->Set(&ppData);
	
	//Set ShaderNodes
	depthMapShaderNode->SetVertexShader(&mDepthVertexShader);
	ppShaderNode->SetPixelShader(&mPostProcessPixelShader);
	ppShaderNode->SetVertexShader(&mPostProcessVertexShader);
	ppShaderNode2->SetPixelShader(&mPostProcessPixelShader2);
	ppShaderNode2->SetVertexShader(&mPostProcessVertexShader2);
	shaderNode->SetPixelShader(&mPixelShader);
	shaderNode->SetVertexShader(&mVertexShader);
	uiShaderNode->SetVertexShader(&mUIVertexShader);
	uiShaderNode->SetPixelShader(&mUIPixelShader);

	//Set Mesh Nodes
	ppQuadMeshNode->SetRenderMesh(&mRenderMeshBuffer);
	planeMeshNode->SetRenderMesh(&mMeshBuffer);
	uiMeshNode->SetRenderMesh(&mUIQuadMeshBuffer);

	depthMapNode->Initialize(graphicsSystem->GetWidth() * 4, graphicsSystem->GetHeight() * 4);
	rasterizerStateNode->Initialize(Graphics::CullMode::Back, Graphics::FillMode::Solid);
	renderTargetNode->Initialize(graphicsSystem->GetWidth(), graphicsSystem->GetHeight(), mColorFormat);
	mPlaneTexture.Initialize("../Assets/Textures/Green.jpg");
	mDuckModel.LoadModel("../Assets/Models/duck.swge");
	
	mRenderTargetTexture.Initialize(renderTargetNode->GetRenderTarget());
	mDepthTexture.Initialize(depthMapNode->GetDepthMap());
	

	renderTextureNode->SetTexture(&mRenderTargetTexture, true);
	renderTextureNode->SetIndex(0);
	depthMapTextureNode->SetTexture(&mDepthTexture, true);
	depthMapTextureNode->SetIndex(4);
	debugTextureNode->SetIndex(0);
	debugTextureNode->SetTexture(&mDepthTexture, true);
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
	depthCameraNode->AddChild(renderTargetNode);
	renderTargetNode->AddChild(depthMapTextureNode);
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
	mTransformNode->AddChild(modelNode);
	//rasterizerStateNode->AddChild(modelNode);
	mTransformNode->GetTransform().SetScale({ 0.05f, 0.05f,0.05f });

	//Post Processing branch
	depthCameraNode->AddChild(renderTextureNode);
	renderTextureNode->AddChild(ConstantBufferNode);
	ConstantBufferNode->AddChild(ppShaderNode);
	ppShaderNode->AddChild(ppSamplerNode);
	ppSamplerNode->AddChild(ppQuadMeshNode);

	ConstantBufferNode->AddChild(ppShaderNode2);
	ppShaderNode2->AddChild(ppSamplerNode);
	ppSamplerNode->AddChild(ppQuadMeshNode);

	//Animation
	mAnimationBuilder
		.AddKey(Math::Vector3{ 1.0f,1.0f,1.0f }, Math::Vector3{ 0.06f,0.06f,0.06f }, Math::Quaternion{ 1.0f,1.0f,1.0f,1.0f }, 0.0f)
		.AddKey(Math::Vector3{ 1.0f,1.0f,1.0f }, Math::Vector3{ 0.06f,0.06f,0.06f }, Math::Quaternion{ 1.0f,1.0f,1.0f,1.0f }, 1.0f)
		.AddKey(Math::Vector3{ 15.0f,25.0f,10.0f }, Math::Vector3{ 0.05f,0.05f,0.05f }, Math::Quaternion{ 1.0f,2.0f,3.0f,0.0f }, 2.0f)
		.AddPositionKey(Math::Vector3{ 3.0f,4.0f,1.0f }, 3.0f)
		.AddScaleKey(Math::Vector3{ 0.05f,1.0f,0.05f }, 4.0f)
		.AddRotationKey(Math::Quaternion{ 3.0f,4.0f,1.0f,5.0f }, 5.0f);
	mAnimation = mAnimationBuilder.BuildAnimation();

}

void GameApp::OnTerminate()
{
	mSceneManager.Purge();
	mDepthTexture.Terminate();
	mRenderTargetTexture.Terminate();
	mPlaneTexture.Terminate();
	mMeshBuffer.Terminate();
	mRenderMeshBuffer.Terminate();
	mUIQuadMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mPostProcessPixelShader.Terminate();
	mPostProcessVertexShader.Terminate();
	mDepthVertexShader.Terminate();
	mDepthPixelShader.Terminate();
	mUIPixelShader.Terminate();
	mUIVertexShader.Terminate();
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
	auto mAnimationTimer = mTimer.GetTotalTime();
	float TotalTime = 1.0f;
	auto inputSystem = Input::InputSystem::Get();
	inputSystem->Update();

	if (inputSystem->IsKeyPressed(SWGE::Input::KeyCode::ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}
	float rotSpeed = 5.0f;

	if(mAnimationTimer >= TotalTime)
	{
		mTimer.Initialize();
	}
		auto& transform = mTransformNode->GetTransform();
		transform.SetWorldMatrix(mAnimation.GetTransform(mAnimationTimer));

	mSceneManager.Update(dt);

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();
	mSceneManager.Render();
	graphicsSystem->EndRender();
}
