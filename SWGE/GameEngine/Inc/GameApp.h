#pragma once

namespace SWGE{
namespace GameEngine {

class GameApp : public SWGE::Core::Application
{
public:
	GameApp();
	~GameApp();
private:
	void OnInitialize() override;
	void OnTerminate() override;
	void OnUpdate() override;

	Core::Window mWindow;
	Core::Timer mTimer;

	SWGE::Graphics::ColorFormat mColorFormat;

	SWGE::Graphics::Camera mCamera;
	SWGE::Graphics::Camera mDepthCamera;

	SWGE::Physics::PhysicsWorld mPhysicsWorld;
	SWGE::Physics::PhysicsWorld::Settings settings;

	SWGE::Graphics::Light mLight;
	SWGE::Graphics::Material mMaterial;

	SWGE::Graphics::MeshBuffer mMeshBuffer;
	SWGE::Graphics::MeshBuffer mRenderMeshBuffer;

	SWGE::Graphics::VertexShader mVertexShader;
	SWGE::Graphics::PixelShader mPixelShader;

	SWGE::Graphics::Animation mAnimation;
	SWGE::Graphics::AnimationBuilder mAnimationBuilder;

	SWGE::Graphics::TransformNode* mTransformNode;
	SWGE::Graphics::SceneManager mSceneManager;



};

}
}

// Addstate<frontendState>


// Addstate
// ChangeState 