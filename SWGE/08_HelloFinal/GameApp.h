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
	SWGE::Graphics::Material mSkyboxMaterial;
	SWGE::Graphics::Sampler mSampler;
	SWGE::Graphics::Texture mSphereTexture[9];
	SWGE::Graphics::Texture mSkyboxTexture;
	SWGE::Graphics::VertexShader mVertexShader;
	SWGE::Graphics::PixelShader mPixelShader;
	SWGE::Graphics::MeshBuffer mMeshBufferSphere;
	SWGE::Graphics::MeshBuffer mMeshBufferCube;
	SWGE::Graphics::MeshBuffer mMeshBufferSkybox;
	SWGE::Graphics::Mesh mCubeMesh;
	SWGE::Graphics::Mesh mUVSphereMesh;
	SWGE::Graphics::Mesh mSkyboxMesh;


	SWGE::Math::Matrix4 planetMatricies[9];
	SWGE::Math::Vector3 mScale[9];
	SWGE::Math::Vector3 mTranslation[9];

};

#endif // INCLUDED_GAMEAPP_H

