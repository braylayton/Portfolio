#ifndef  INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>
#include <Physics\Inc\Physics.h>
#include <random>

class GameApp : public SWGE::Core::Application
{
public:
	GameApp();
	~GameApp() override;

private:
	void OnInitialize() override;
	void OnTerminate() override;
	void OnUpdate() override;

	SWGE::Core::Window mWindow;
	SWGE::Core::Timer mTimer;
	SWGE::Physics::PhysicsWorld mPhysicsWorld;
	SWGE::Physics::PhysicsWorld::Settings settings;
	SWGE::Graphics::Camera mCamera;

	std::vector<SWGE::Math::Vector3> mPoints;
	std::vector<float> mLengths;

};

#endif // INCLUDED_GAMEAPP_H

