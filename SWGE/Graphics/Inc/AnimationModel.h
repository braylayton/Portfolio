#ifndef INCLUDED_CORE_ANIMATIONMODEL_H
#define INCLUDED_CORE_ANIMATIONMODEL_H

#include <exception>
#include "Bone.h"
#include "SkinnedMesh.h"
#include "Material.h"
#include "MeshBuffer.h"
#include "Texture.h"
#include "SceneNodeInc\SceneManager.h"
#include "SceneNodeInc\MeshNode.h"
#include "SceneNodeInc\TransformNode.h"
#include "SceneNodeInc\TextureNode.h"
namespace SWGE {
namespace Graphics {

	class AnimationModel
	{
	public:

		AnimationModel();
		~AnimationModel();
		void SaveModel(const char* filename);
		void LoadModel(const char* filename);
		void Destroy();
		void Initialize(SceneManager& mSceneManager);

		SceneNode* GetRootNode() { return rootNode; }

		std::vector<SkinnedMesh> mSkinMesh; // Saved // Loaded
		std::vector<Material> mMaterial; // Saved // Loaded
		std::vector<std::string> mDiffuseTexture; // Saved // Loaded
		std::vector<int> mMaterialIndex; // Saved // Loaded

		std::vector<uint32_t> mBoneVertexID; // Saved 
		std::vector<float> mBoneWeights; // Saved
		std::map<std::string, uint32_t> mBoneIndexMap; // Saved 
		std::vector<Bone*> mBones; // Saved
		//std::vector<uint32_t> mBoneIndices;

	private:
		Bone* mRootBones;
		
		MeshBuffer* mMeshBuffer;
		SceneNode* rootNode;
		std::vector<Texture> mTexture;
	};

} // Core
} // SWGE

#endif //INCLUDED_CORE_MODEL_H