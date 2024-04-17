#ifndef  INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>
#include <Input/Inc/Input.h>
#include <External/IMGUI/Inc/DearIMGUI.h>
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
	SWGE::Graphics::VertexShader mVertexShader;
	SWGE::Graphics::PixelShader mPixelShader;
	SWGE::Graphics::MeshBuffer mMeshBuffer;

	SWGE::Graphics::SceneManager mSceneManager;
};

#endif // INCLUDED_GAMEAPP_H

