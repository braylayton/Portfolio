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
	SWGE::Graphics::Light mLight;
	SWGE::Graphics::Material mMaterial;

	SWGE::Graphics::MeshBuffer mMeshBuffer;

	SWGE::Graphics::Model mDuckModel;

	SWGE::Graphics::Texture mRenderTargetTexture;

	SWGE::Graphics::VertexShader mVertexShader;
	SWGE::Graphics::PixelShader mPixelShader;

	SWGE::Graphics::VertexShader mPostProcessVertexShader;
	SWGE::Graphics::PixelShader mPostProcessPixelShader;

	SWGE::Graphics::TransformNode* mTransformNode;
	SWGE::Graphics::SceneManager mSceneManager;
};

#endif // INCLUDED_GAMEAPP_H

