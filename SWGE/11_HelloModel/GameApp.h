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

	SWGE::Graphics::Camera mCamera;
	SWGE::Graphics::Light mLight;
	SWGE::Graphics::Material mMaterial;
	SWGE::Graphics::MeshBuffer mMeshBuffer;
	SWGE::Graphics::Mesh mCubeMesh;
	SWGE::Graphics::Mesh mUVSphereMesh;
	SWGE::Graphics::Mesh mSkyBoxMesh;

	SWGE::Graphics::Model mDuckModel;
	SWGE::Graphics::AnimationModel mElyModel;
	SWGE::Graphics::PixelShader mPixelShader;

	SWGE::Graphics::Texture mSkyBoxDiffuse;
	SWGE::Graphics::Texture mDiffuseMap;
	SWGE::Graphics::Texture mSpecularMap;
	SWGE::Graphics::Texture mNormalMap;
	SWGE::Graphics::Texture mDisplacementMap;
	SWGE::Graphics::VertexShader mVertexShader;

	SWGE::Graphics::TransformNode* mTransformNode;
	SWGE::Graphics::SceneManager mSceneManager;
};

#endif // INCLUDED_GAMEAPP_H

