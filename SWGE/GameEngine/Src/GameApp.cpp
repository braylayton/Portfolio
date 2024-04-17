#include "Precompiled.h"
#include "GameApp.h"
 
// NOTE MAKE THIS A STATE MACHINE

using namespace SWGE;
using namespace GameEngine;

GameApp::GameApp()
{

}

GameApp::~GameApp()
{

}

void GameApp::OnInitialize()
{
	//Math::MetaRegistration();
	//Input::MetaRegistration();
	//Graphics::MetaRegistration();
	//Network::MetaRegistration();

	mWindow.Initialize(GetInstance(), GetAppName(), 1280, 720);
	mTimer.Initialize();
	mColorFormat = Graphics::ColorFormat::RGBA_U8;

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();
	Graphics::SimpleDraw::Initialize();
	mPhysicsWorld.Setup(settings);


}
void GameApp::OnTerminate()
{
	//Detach our window and terminate it
	Input::InputSystem::StaticTerminate();
	Graphics::GraphicsSystem::StaticTerminate();
	mWindow.Terminate();
}

void GameApp::OnUpdate()
{
	if(mWindow.ProcessMessage())
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

	mPhysicsWorld.Update(dt);
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

	Graphics::SimpleDraw::Render(mCamera);
	mPhysicsWorld.DebugDraw();

	graphicsSystem->EndRender();

}