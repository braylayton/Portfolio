#ifndef  INCLUDED_GAMEAPP_H
#define INCLUDED_GAMEAPP_H

#include <Core/Inc/Core.h>
#include <Graphics/Inc/Graphics.h>

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


	ID3D11Buffer* mTriBuffer;
	ID3D11Buffer* mHeartBuffer;
	ID3D11Buffer* mStarBuffer;
	ID3D11Buffer* mBoatBuffer;
	ID3D11Buffer* mCurrentBuffer;

	SWGE::Graphics::VertexShader* VShader;
	SWGE::Graphics::PixelShader* PShader;
};


#endif // ! INCLUDED_GAMEAPP_H
