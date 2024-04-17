//#ifndef  INCLUDED_GAMEAPP_H
//#define INCLUDED_GAMEAPP_H
//
//#include <Core/Inc/Core.h>
//#include <Graphics/Inc/Graphics.h>
//#include <Input/Inc/Input.h>
//
//class GameApp : public SWGE::Core::Application
//{
//public:
//	GameApp();
//	~GameApp() override;
//
//private:
//	void OnInitialize() override;
//	void OnTerminate() override;
//	void OnUpdate() override;
//
//	SWGE::Core::Window mWindow;
//	SWGE::Core::Timer mTimer;
//
//	struct TransformData
//	{
//		SWGE::Math::Matrix4 world;
//		SWGE::Math::Matrix4 wvp;
//		SWGE::Math::Matrix4 wvpLight = SWGE::Math::Matrix4::Identity();
//		SWGE::Math::Vector4 cameraPosition;
//		SWGE::Graphics::Light  light;
//		SWGE::Graphics::Material material;
//
//	};
//
//	typedef SWGE::Graphics::TypedConstantBuffer<TransformData> TransformCB;
//
//	SWGE::Graphics::Camera mCamera;
//
//	TransformCB mConstantBuffer;
//	SWGE::Graphics::Light mLight;
//	SWGE::Graphics::Material mMaterial;
//	SWGE::Graphics::Sampler mSampler;
//	SWGE::Graphics::Texture mPlaneDiffuseMap;
//	SWGE::Graphics::Texture mCubeDiffuseMap;
//	SWGE::Graphics::Texture mCylinDiffuseMap;
//	SWGE::Graphics::VertexShader mVertexShader;
//	SWGE::Graphics::PixelShader mPixelShader;
//	SWGE::Graphics::MeshBuffer mCylinderMeshBuffer;
//	SWGE::Graphics::MeshBuffer mCubeMeshBuffer;
//	SWGE::Graphics::MeshBuffer mPlaneMeshBuffer;
//	SWGE::Graphics::SkinnedMesh mCylinderMesh;
//	SWGE::Graphics::Mesh mCubeMesh;
//	SWGE::Graphics::Mesh mPlaneMesh;
//	SWGE::Math::Matrix4	mBoxTransforms[3];
//
//	uint32_t change = 0;
//	struct Bone
//	{
//		Bone* Parent;
//		SWGE::Math::Matrix4 transform;
//	};
//
//	std::vector<Bone> mBones;
//	std::vector<SWGE::Graphics::Transform> mBoneTransforms;
//	std::vector<SWGE::Math::Vector3> mBoneOffsets;
//	std::vector<SWGE::Math::Quaternion> mBoneAngles;
//	std::vector<SWGE::Math::Matrix4> mBoneWorldTransform;
//	std::vector<SWGE::Math::Matrix4> mSkinningTransform;
//};
//
//#endif // INCLUDED_GAMEAPP_H
//
