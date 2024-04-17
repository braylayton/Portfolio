#include "GameApp.h"

using namespace SWGE;

namespace //Internal Linkage -- to not pollute the global namespace
{

	//sizeof is a compile time operator(static)

	float Xlength = 0.5f, YHeight = 0.5f, ZWidth = 0.5f;

	const Graphics::VertexPC kVertices[] =
	{
		//Front
		{ Math::Vector3(-Xlength,  YHeight, -ZWidth), Math::Vector4::Red() },	//top left 0
	{ Math::Vector3(Xlength,  YHeight,	-ZWidth), Math::Vector4::Blue() },		//top right 1
	{ Math::Vector3(Xlength, -YHeight,	-ZWidth), Math::Vector4::Yellow() },	//bot right 2
	{ Math::Vector3(-Xlength, -YHeight, -ZWidth), Math::Vector4::Green() },	//bot left 3
																			//Back
	{ Math::Vector3(-Xlength,  YHeight, ZWidth), Math::Vector4::Cyan() },	//top left 4
	{ Math::Vector3(Xlength,  YHeight,  ZWidth), Math::Vector4::Orange() },	//top right 5
	{ Math::Vector3(Xlength, -YHeight,  ZWidth), Math::Vector4::Magenta() },	//bot right 6
	{ Math::Vector3(-Xlength, -YHeight, ZWidth), Math::Vector4::LightRed() },	//bot left 7

	};

	const int kVertexCount = sizeof(kVertices) / sizeof(kVertices[0]);
	const uint32_t kIndices[] =
	{
		//front  good
		0,1,2,
		0,2,3,
		//Top	good
		4,1,0,
		4,5,1,
		//Left good
		4,0,3,
		4,3,7,
		//Right
		1,5,6,
		1,6,2,
		//Back
		5,4,7,
		5,7,6,
		//Bot
		3,2,6,
		3,6,7

	};
	const int kIndexCount = sizeof(kIndices) / sizeof(kIndices[0]);
	std::random_device device;
	std::mt19937 engine(device());
}


void FabrickForward(std::vector<Math::Vector3>& points, std::vector<float>& lengths, Math::Vector3 target)
{
	points.back() = target;
	for (int i = 0; i < (int)points.size(); i++)
	{

	}

}

void FabrikBack(std::vector<Math::Vector3>& points, std::vector<float>& lengths, Math::Vector3 orgin)
{
	points.front() = orgin;
	for (int i = 0; i < (int)points.size(); i++)
	{

	}

}

void RunFabrick(std::vector<Math::Vector3>& points, std::vector<float>& lengths, Math::Vector3 target, int marginOfError)
{
	Math::Vector3 orgin = points.front();
	for (size_t i = 0; i < 6; i++)
	{
		if (Math::DistanceSqr(points.back(), target) < Math::Sqr(marginOfError))
		{
			break;
		}
		FabrickForward(points, lengths, target);
		FabrikBack(points, lengths, orgin);
	}
}


GameApp::GameApp()
{
}

GameApp::~GameApp()
{
}

void GameApp::OnInitialize()
{
	mWindow.Initialize(GetInstance(), GetAppName(), 1280, 720);
	mTimer.Initialize();

	Graphics::GraphicsSystem::StaticInitialize(mWindow.GetWindowHandle(), false);
	Input::InputSystem::StaticInitialize(mWindow.GetWindowHandle());

	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	auto device = graphicsSystem->GetDevice();
	Graphics::SimpleDraw::Initialize();
	mPhysicsWorld.Setup(settings);
	mCamera.SetPosition({ 0.0f, 10.0f, -25.0f });
}

void GameApp::OnTerminate()
{

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
	const float turnSpeed = 5.0f;
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::W))
		mCamera.Walk(dt * moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::S))
		mCamera.Walk(dt * -moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::D))
		mCamera.Strafe(dt * moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::A))
		mCamera.Strafe(dt * -moveSpeed);
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::SPACE))
	{
		mPhysicsWorld.ClearAll();
		for (size_t i = 0; i < 80; i++)
		{
			auto p = new Physics::Particle();
			p->SetPosition({ 0.0f, 2.0f, 0.0f });
			p->SetVelocity({ std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine) });
			p->radius = 0.1f;
			mPhysicsWorld.AddParticle(p);
		}
	}
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
	mPhysicsWorld.Update(dt);
	auto graphicsSystem = Graphics::GraphicsSystem::Get();
	graphicsSystem->BeginRender();

	Graphics::SimpleDraw::AddPlane(Math::Plane(), Math::Vector3::Zero(), 100.0f, 1.0f, Math::Vector4::Black());
	Graphics::SimpleDraw::AddTransform(Math::Matrix4::Identity());

	Graphics::SimpleDraw::Render(mCamera);
	mPhysicsWorld.DebugDraw();

	graphicsSystem->EndRender();
}

