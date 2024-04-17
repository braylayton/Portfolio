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

	struct TransformData
	{
		SWGE::Math::Matrix4 world;
		SWGE::Math::Matrix4 wvp;
		SWGE::Math::Vector4 cameraPosition;
		SWGE::Graphics::Light  light;
		SWGE::Graphics::Material material;
		int useTextureBool = false;

	};
	typedef SWGE::Graphics::TypedConstantBuffer<TransformData> TransformCB;

	SWGE::Graphics::Camera mCamera;

	TransformCB mConstantBuffer;
	SWGE::Graphics::Light mLight;
	SWGE::Graphics::Material mMaterial;
	SWGE::Graphics::Sampler mSampler;
	SWGE::Graphics::Texture mTexture;
	SWGE::Graphics::VertexShader mVertexShader;
	SWGE::Graphics::PixelShader mPixelShader;
	SWGE::Graphics::MeshBuffer mMeshBuffer;
	SWGE::Graphics::Mesh mCubeMesh;
	SWGE::Graphics::Mesh mUVSphereMesh;
	SWGE::Graphics::Terrain mTerrain;
};

#endif // INCLUDED_GAMEAPP_H

