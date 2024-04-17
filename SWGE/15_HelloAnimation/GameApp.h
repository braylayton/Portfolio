#ifndef  INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>

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

	SWGE::Graphics::ColorFormat mColorFormat;

	SWGE::Graphics::Camera mCamera;
	SWGE::Graphics::Camera mDepthCamera;

	SWGE::Graphics::Light mLight;
	SWGE::Graphics::Material mMaterial;

	SWGE::Graphics::MeshBuffer mMeshBuffer;
	SWGE::Graphics::MeshBuffer mRenderMeshBuffer;
	SWGE::Graphics::MeshBuffer mUIQuadMeshBuffer;

	struct PostProcessingData
	{
		float screenWidth;
		float screenHeight;
		float lineThickness;
		SWGE::Math::Vector4 lineColor;
	};

	SWGE::Graphics::Mesh mPlane;

	SWGE::Graphics::Model mDuckModel;

	SWGE::Graphics::Texture mRenderTargetTexture;
	SWGE::Graphics::Texture mDepthTexture;
	SWGE::Graphics::Texture mPlaneTexture;

	SWGE::Graphics::VertexShader mVertexShader;
	SWGE::Graphics::VertexShader mPostProcessVertexShader;
	SWGE::Graphics::VertexShader mPostProcessVertexShader2;
	SWGE::Graphics::VertexShader mDepthVertexShader;
	SWGE::Graphics::VertexShader mUIVertexShader;
	SWGE::Graphics::PixelShader mPixelShader;
	SWGE::Graphics::PixelShader mPostProcessPixelShader;
	SWGE::Graphics::PixelShader mPostProcessPixelShader2;
	SWGE::Graphics::PixelShader mDepthPixelShader;
	SWGE::Graphics::PixelShader mUIPixelShader;

	SWGE::Graphics::Animation mAnimation;
	SWGE::Graphics::AnimationBuilder mAnimationBuilder;

	SWGE::Graphics::TransformNode* mTransformNode;
	SWGE::Graphics::SceneManager mSceneManager;
};

#endif // INCLUDED_GAMEAPP_H

