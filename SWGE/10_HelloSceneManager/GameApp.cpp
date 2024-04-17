
#include "GameApp.h"

using namespace SWGE;
namespace
{
Graphics::MaterialNode* tempMat = nullptr;
bool Initialized = false;
bool show_demo_window = true;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED && Initialized)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
			ImGui_ImplDX11_CreateDeviceObjects();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::OnInitialize()
{
	mWindow.Initialize(GetInstance(), GetAppName(), 720, 720, WndProc);
	mTimer.Initialize();

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();
	Graphics::MeshBuilder::CreateCube(mCubeMesh);
	Graphics::MeshBuilder::CreateUVSphere(mUVSphereMesh,100,100);
	mCamera.SetLookAt(Math::Vector3(0, 0, 1));
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mDiffuseMap.Initialize("../Assets/Textures/earth_diff.jpg");
	mNormalMap.Initialize("../Assets/Textures/earth_normal.jpg");
	mSpecularMap.Initialize("../Assets/Textures/earth_spec.jpg");
	mDisplacementMap.Initialize("../Assets/Textures/earth_bump.jpg");
	mVertexShader.Initialize(L"../Assets/Shaders/Standard2.fx", "VS", "vs_5_0", Graphics::Vertex::Format);
	mPixelShader.Initialize(L"../Assets/Shaders/Standard2.fx", "PS", "ps_5_0", Graphics::Vertex::Format);
	mMeshBuffer.Initialize(mUVSphereMesh, false);
	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplDX11_Init(mWindow.GetWindowHandle(), graphicsSystem->GetDevice(), graphicsSystem->GetContext());
	mLight.direction = { Math::Vector3::ZAxis(), 0.0f };
	mLight.ambient = { 0.1f, 0.1f, 0.1f, 0.1f };
	mLight.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	ImGui::StyleColorsClassic();
	io.Fonts->AddFontDefault();

	mMaterial.ambient = { 1.0f ,1.0f,1.0f ,1.0f };
	mMaterial.diffuse = { 0.65f, 0.65f, 0.65f,0.65f };
	mMaterial.specular = { 1.0f ,1.0f ,1.0f ,1.0f };
	mMaterial.power = 10;
	mMaterial.displacementFactor = 0.25f;



	auto cameraNode = mSceneManager.CreateCameraNode(mCamera);
	mSceneManager.SetRoot(cameraNode);
	auto transformNode = mSceneManager.CreateTransformNode();
	auto lightNode = mSceneManager.CreateLightNode(mLight);
	auto materialNode = mSceneManager.CreateMaterialNode(mMaterial);
	auto meshNode = mSceneManager.CreateMeshNode();
	auto samplerNode = mSceneManager.CreateSamplerNode(Graphics::Sampler::Filter::Anisotropic, Graphics::Sampler::AddressMode::Clamp);
	auto shaderNode = mSceneManager.CreateShaderNode();
	auto diffuseMapNode = mSceneManager.CreateTextureNode();
	auto specularMapNode = mSceneManager.CreateTextureNode();
	auto normalMapNode = mSceneManager.CreateTextureNode();
	auto displacementMapNode = mSceneManager.CreateTextureNode();

	diffuseMapNode->SetIndex(0);
	diffuseMapNode->SetTexture(&mDiffuseMap);
	specularMapNode->SetIndex(1);
	specularMapNode->SetTexture(&mSpecularMap);
	normalMapNode->SetIndex(2);
	normalMapNode->SetTexture(&mNormalMap);
	displacementMapNode->SetIndex(3);
	displacementMapNode->SetTexture(&mDisplacementMap);

	meshNode->SetRenderMesh(&mMeshBuffer);
	shaderNode->SetPixelShader(&mPixelShader);
	shaderNode->SetVertexShader(&mVertexShader);
	cameraNode->AddChild(shaderNode);
	shaderNode->AddChild(samplerNode);
	samplerNode->AddChild(lightNode);
	lightNode->AddChild(materialNode);
	materialNode->AddChild(diffuseMapNode);
	diffuseMapNode->AddChild(specularMapNode);
	specularMapNode->AddChild(normalMapNode);
	normalMapNode->AddChild(displacementMapNode);
	displacementMapNode->AddChild(transformNode);
	transformNode->AddChild(meshNode);
	tempMat = materialNode;
}

void GameApp::OnTerminate()
{
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

	mSceneManager.Purge();
	mMeshBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mDisplacementMap.Terminate();
	mSpecularMap.Terminate();
	mNormalMap.Terminate();
	mDiffuseMap.Terminate();
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
	ImGui_ImplDX11_NewFrame();

	if (show_demo_window)
	{
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	auto inputSystem = Input::InputSystem::Get();
	inputSystem->Update();
	auto& mat = tempMat->GetMaterial();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (inputSystem->IsKeyPressed(SWGE::Input::KeyCode::ESCAPE))
	{
		PostQuitMessage(0);
		return;
	}
	if (inputSystem->IsKeyPressed(SWGE::Input::KeyCode::J))
	{
		mat.displacementFactor -= 0.05f;
		//mat.power -= 0.1f;
	}
	
	if (inputSystem->IsKeyPressed(SWGE::Input::KeyCode::L))
	{
		mat.displacementFactor += 0.05f;
		//mat.power += 0.5f;
	}

	mSceneManager.Update(dt);

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();
	mSceneManager.Render();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	graphicsSystem->EndRender();
}
