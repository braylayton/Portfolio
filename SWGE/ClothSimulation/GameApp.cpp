#include "GameApp.h"

using namespace SWGE;

namespace //Internal Linkage -- to not pollute the global namespace
{
	
//sizeof is a compile time operator(static)

	float Xlength =0.5f, YHeight = 0.5f, ZWidth = 0.5f;

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
	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::ONE))
	{
		mPhysicsWorld.ClearAll();
		for (size_t i = 0; i < 10; i++)
		{
			auto p1 = new Physics::Particle();
			auto p2 = new Physics::Particle();
			auto spring = new Physics::Spring(p1, p2, 1.0f);
			p1->SetPosition({ 0.0f, 2.0f, 0.0f });
			p1->SetVelocity({ std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine) });
			p1->radius = 0.1f;
			p2->SetPosition({ 0.0f, 2.0f, 0.0f });
			p2->SetVelocity({ std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine) });
			p2->radius = 0.1f;
			mPhysicsWorld.AddParticle(p1);
			mPhysicsWorld.AddParticle(p2);
			mPhysicsWorld.AddConstraints(spring);
		}
	}

	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::TWO))
	{
		//Octopus ;)
		mPhysicsWorld.ClearAll();
		for (size_t i = 0; i < 8; i++)
		{
			auto p1 = new Physics::Particle();
			auto p2 = new Physics::Particle();
			auto p3 = new Physics::Particle();
			auto p4 = new Physics::Particle();
			auto spring = new Physics::Spring(p1, p2, 1.0f);
			auto spring2 = new Physics::Spring(p2, p3, 1.0f);
			auto spring3 = new Physics::Spring(p3, p4, 1.0f);
			p1->SetPosition({ 0.0f, 2.0f, 0.0f });
			p1->SetVelocity({ 0.0f, 0.0f, 0.0f });
			p1->radius = 0.1f;
			auto fixed = new Physics::Fixed(p1, p1->position);
			p2->SetPosition({ 0.0f, 1.0f, 0.0f });
			p2->SetVelocity({ std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine) });
			p2->radius = 0.1f;
			p3->SetPosition({ 0.0f, 1.0f, 0.0f });
			p3->SetVelocity({ std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine) });
			p3->radius = 0.1f;
			p4->SetPosition({ 0.0f, 1.0f, 0.0f });
			p4->SetVelocity({ std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine),
				std::uniform_real_distribution<float>(-0.1f, 0.1f)(engine) });
			p4->radius = 0.1f;

			mPhysicsWorld.AddParticle(p1);
			mPhysicsWorld.AddParticle(p2);
			mPhysicsWorld.AddParticle(p3);
			mPhysicsWorld.AddParticle(p4);

			mPhysicsWorld.AddConstraints(spring);
			mPhysicsWorld.AddConstraints(spring2);
			mPhysicsWorld.AddConstraints(spring3);
			mPhysicsWorld.AddConstraints(fixed);
		}
	}


	if (inputSystem->IsKeyDown(SWGE::Input::KeyCode::THREE))
	{
		auto particle = std::vector<Physics::Particle*>();
		float restLength = 1.0f;
		Math::Vector3 position(0.0f, 2.0f, 0.0f);
		uint32_t cols = 3;
		uint32_t rows = 3;
		//auto spring = std::vector<Physics::Spring>();
		//auto fixed = std::vector<Physics::Fixed>();
		mPhysicsWorld.ClearAll();
		for (uint32_t i = 0; i < rows; i++) // cols
		{
			for (uint32_t j = 0; j < cols; j++) // rows
			{
				auto p = new Physics::Particle(Math::Vector3({ (float)i,-(float)j - 0.5f,0 }));
				//auto p = new Physics::Particle(Math::Vector3({ 0, - 0.5f,0 }));

				if (i == 0 && j == 0)
				{
					auto fixed = new Physics::Fixed(p, p->position);
					mPhysicsWorld.AddConstraints(fixed);
					mPhysicsWorld.AddParticle(p);
					particle.push_back(p);
				}
				else if ( i== rows -1 && j == 0)
				{
					auto fixed = new Physics::Fixed(p, p->position);
					mPhysicsWorld.AddConstraints(fixed);
					mPhysicsWorld.AddParticle(p);
					particle.push_back(p);
				}
				else
				{
					p->SetVelocity(Math::Vector3({ 0.001f,0.001f,0.001f }));
					mPhysicsWorld.AddParticle(p);
					particle.push_back(p);
					
				}
			}
		}

		for (uint32_t y = 0; y < rows; y++)
		{
			for (uint32_t x = 0; x < cols; x++)
			{
				uint32_t index = y * rows + x;
				if (x == 0 && y > 0)
				{
					auto spring1 = new Physics::Spring(particle[index], particle[index - cols], restLength);
					mPhysicsWorld.AddConstraints(spring1);
				}
				else if (y > 0)
				{
					// add spring from Top to Bottom
					auto spring1 = new Physics::Spring(particle[index], particle[index - 1], restLength);
					mPhysicsWorld.AddConstraints(spring1);
					// add spring from Right to Left
					auto spring2 = new Physics::Spring(particle[index], particle[index - cols], restLength);
					mPhysicsWorld.AddConstraints(spring2);
					// add diagonal spring
					auto spring3 = new Physics::Spring(particle[index], particle[index - cols - 1], restLength);
					mPhysicsWorld.AddConstraints(spring3);
					if(y < cols - 1)
					{
						auto spring3 = new Physics::Spring(particle[index], particle[index + cols - 1], restLength);
						mPhysicsWorld.AddConstraints(spring3);
					}

				}
				else
				{
					if (x != 0)
					{
						auto spring1 = new Physics::Spring(particle[index], particle[index - 1], restLength);
						mPhysicsWorld.AddConstraints(spring1);
						auto spring3 = new Physics::Spring(particle[index], particle[index + cols - 1], restLength);
						mPhysicsWorld.AddConstraints(spring3);
					}
				}
			}
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

