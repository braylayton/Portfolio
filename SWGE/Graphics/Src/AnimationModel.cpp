#include "Precompiled.h"
#include "AnimationModel.h"
#include "SceneNodeInc/MaterialNode.h"

using namespace SWGE;
using namespace Graphics;

struct AnimationModelData
{
	uint32_t meshCount;
	uint32_t materialCount;
	uint32_t textureCount;
};

struct AnimationMeshData
{
	uint32_t vertexCount;
	uint32_t indexCount;
	uint32_t materialIndex;

};

AnimationModel::AnimationModel()
{
}

AnimationModel::~AnimationModel()
{
	ASSERT(mMeshBuffer == nullptr, "Did not terminate");
}
void AnimationModel::SaveModel(const char* filename)
{
	std::ofstream ofs(filename, std::ios::binary | std::ios::out);
	if (ofs.fail())
	{
		int i = 0;
	}
	AnimationModelData aModelData;
	aModelData.meshCount = static_cast<uint32_t>(mSkinMesh.size());
	aModelData.materialCount = static_cast<uint32_t>(mMaterial.size());
	aModelData.textureCount = static_cast<uint32_t>(mDiffuseTexture.size());

	ofs.write(reinterpret_cast<const char*>(&aModelData), sizeof(AnimationModelData));

	for (size_t i = 0; i < mSkinMesh.size(); i++)
	{
		auto& skinmesh = mSkinMesh[i];
		AnimationMeshData aMeshData;
		aMeshData.vertexCount = skinmesh.GetVertexCount();
		aMeshData.indexCount = skinmesh.GetIndexCount();
		aMeshData.materialIndex = mMaterialIndex[i];

		ofs.write(reinterpret_cast<char*>(&aMeshData), sizeof(AnimationMeshData));

		const auto vertices = skinmesh.GetVertices();
		ofs.write(reinterpret_cast<char*>(vertices), sizeof(*vertices) * skinmesh.GetVertexCount());

		const auto indices = skinmesh.GetIndices();
		ofs.write(reinterpret_cast<char*>(indices), sizeof(*indices) * skinmesh.GetIndexCount());
	}

	ofs.write(reinterpret_cast<char*>(mMaterial.data()), mMaterial.size() * sizeof(mMaterial[0]));

	for (auto& texture : mDiffuseTexture)
	{
		uint32_t size = static_cast<uint32_t>(texture.size());
		ofs.write(reinterpret_cast<char*>(&size), sizeof(uint32_t));
		ofs.write(texture.data(), texture.size());
	}
	
	uint32_t boneSize = static_cast<uint32_t>(mBones.size());
	ofs.write(reinterpret_cast<char*>(&boneSize), sizeof(uint32_t));
	for (auto& bone : mBones)
	{
		// save bone.childrenIdex size and index
		uint32_t childrenSize = static_cast<uint32_t>(bone->childrenIndex.size());
		ofs.write(reinterpret_cast<char*>(&childrenSize), sizeof(uint32_t));
		ofs.write(reinterpret_cast<char*>(bone->childrenIndex.data()), bone->childrenIndex.size());
		// save bone.name
		uint32_t nameStringSize = static_cast<uint32_t>(bone->name.size());
		ofs.write(reinterpret_cast<char*>(&nameStringSize), sizeof(uint32_t));
		ofs.write(bone->name.data(), bone->name.size());
		// save bone matricies
		ofs.write(reinterpret_cast<char*>(&bone->transform), sizeof(Math::Matrix4));
		ofs.write(reinterpret_cast<char*>(&bone->offsetTransform), sizeof(Math::Matrix4));
		// save bone indices
		ofs.write(reinterpret_cast<char*>(&bone->mIndex), sizeof(int));
		ofs.write(reinterpret_cast<char*>(&bone->parentIndex), sizeof(int));
	}
	// save bone Vertex ID
	uint32_t bvSize = static_cast<uint32_t>(mBoneVertexID.size());
	ofs.write(reinterpret_cast<char*>(&bvSize), sizeof(uint32_t));
	ofs.write(reinterpret_cast<char*>(mBoneVertexID.data()), mBoneVertexID.size() * sizeof(uint32_t));
	// save bone Weights
	uint32_t bwSize = static_cast<uint32_t>(mBoneWeights.size());
	ofs.write(reinterpret_cast<char*>(&bwSize), sizeof(uint32_t));
	ofs.write(reinterpret_cast<char*>(mBoneWeights.data()), mBoneWeights.size() * sizeof(float));
	// save bone Index map
	uint32_t bimSize = static_cast<uint32_t>(mBoneIndexMap.size());
	ofs.write(reinterpret_cast<char*>(&bimSize), (sizeof(uint32_t)));
	for (auto& boneIndex : mBoneIndexMap)
	{
		uint32_t keyStringSize = static_cast<uint32_t>(boneIndex.first.size());
		ofs.write(reinterpret_cast<char*>(&keyStringSize), sizeof(uint32_t));
		ofs.write(boneIndex.first.data(), boneIndex.first.size());

		ofs.write(reinterpret_cast<char*>(&boneIndex.second), sizeof(uint32_t));
	}

	ofs.close();
}

void AnimationModel::LoadModel(const char* filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::in);
	if (ifs.fail())
	{
		int i = 0;
	}
	AnimationModelData aModelData;
	ifs.read(reinterpret_cast<char*>(&aModelData), sizeof(AnimationModelData));

	mSkinMesh.resize(aModelData.meshCount);
	mMaterialIndex.resize(aModelData.meshCount);
	mMaterial.resize(aModelData.materialCount);
	mDiffuseTexture.resize(aModelData.textureCount);

	for (size_t i = 0; i < aModelData.meshCount; i++)
	{
		auto& skinmesh = mSkinMesh[i];
		AnimationMeshData aMeshData;

		ifs.read(reinterpret_cast<char*>(&aMeshData), sizeof(AnimationMeshData));

		skinmesh.Allocate(aMeshData.vertexCount, aMeshData.indexCount);
		mMaterialIndex[i] = aMeshData.materialIndex;

		auto vertices = skinmesh.GetVertices();
		ifs.read(reinterpret_cast<char*>(skinmesh.GetVertices()), sizeof(*vertices) * skinmesh.GetVertexCount());

		auto indices = skinmesh.GetIndices();
		ifs.read(reinterpret_cast<char*>(skinmesh.GetIndices()), sizeof(*indices) * skinmesh.GetIndexCount());
	}

	ifs.read(reinterpret_cast<char*>(mMaterial.data()), mMaterial.size() * sizeof(mMaterial[0]));

	char buffer[1024];
	for (auto& texture : mDiffuseTexture)
	{
		uint32_t size = 0;
		ifs.read(reinterpret_cast<char*>(&size), sizeof(uint32_t));

		texture.resize(size);
		ifs.read(buffer, texture.size());
		buffer[size] = '\0';
		texture = buffer;
	}

	// Load bones
	uint32_t boneSize = 0;
	ifs.read(reinterpret_cast<char*>(&boneSize), sizeof(uint32_t));
	mBones.resize(boneSize);
	for (size_t i = 0; i < boneSize; i++)
	{
		// Load bone.childrenIdex size and index
		mBones[i] = new Bone();
		auto& bone = mBones[i];

		uint32_t childrenSize = 0;
		ifs.read(reinterpret_cast<char*>(&childrenSize), sizeof(uint32_t));
		bone->childrenIndex.resize(childrenSize);
		if (!bone->childrenIndex.empty())
		{
			ifs.read(reinterpret_cast<char*>(bone->childrenIndex[0]), childrenSize * sizeof(uint32_t));
		}
		// Load bone.mName
		uint32_t nameStringSize = 0;
		ifs.read(reinterpret_cast<char*>(&nameStringSize), sizeof(uint32_t));
		ifs.read(reinterpret_cast<char*>(&bone->name), nameStringSize * sizeof(std::string));
		// Load bone transforms
		ifs.read(reinterpret_cast<char*>(&bone->transform), sizeof(Math::Matrix4));
		ifs.read(reinterpret_cast<char*>(&bone->offsetTransform), sizeof(Math::Matrix4));
		// Load bone indices
		ifs.read(reinterpret_cast<char*>(&bone->mIndex), sizeof(int));
		ifs.read(reinterpret_cast<char*>(&bone->parentIndex), sizeof(int));
	}

	uint32_t bvSize = 0;
	ifs.read(reinterpret_cast<char*>(&bvSize), sizeof(uint32_t));
	mBoneVertexID.resize(bvSize);
	ifs.read((char*)&mBoneVertexID[0], bvSize * sizeof(uint32_t));

	uint32_t bwSize = 0;
	ifs.read(reinterpret_cast<char*>(&bwSize), sizeof(uint32_t));
	mBoneWeights.resize(bwSize);
	ifs.read((char*)&mBoneWeights[0], bwSize * sizeof(float));

	// Load bone Index map
	uint32_t bimSize = 0;
	ifs.read(reinterpret_cast<char*>(&bimSize), (sizeof(uint32_t)));
	for (size_t i = 0; i < bimSize; i++)
	{
		uint32_t keyStringSize = 0;
		std::string tempString;
		uint32_t tempUint{0};
		ifs.read(reinterpret_cast<char*>(&keyStringSize), sizeof(uint32_t));
		ifs.read(reinterpret_cast<char*>(&tempString), keyStringSize * sizeof(std::string));

		ifs.read(reinterpret_cast<char*>(tempUint), sizeof(uint32_t));
		mBoneIndexMap[tempString] = tempUint;
	}

	ifs.close();
}

void AnimationModel::Initialize(SceneManager& mSceneManager)
{
	AnimationModelData aModelData;
	aModelData.meshCount = static_cast<uint32_t>(mSkinMesh.size());
	aModelData.materialCount = static_cast<uint32_t>(mMaterial.size());
	aModelData.textureCount = static_cast<uint32_t>(mDiffuseTexture.size());

	std::vector<MeshNode*> skinMeshNode;
	skinMeshNode.resize(aModelData.meshCount);
	std::vector<MaterialNode*> matNode;
	matNode.resize(aModelData.materialCount);
	std::vector<TextureNode*> diffuseNode;
	diffuseNode.resize(aModelData.textureCount);
	mTexture.resize(aModelData.textureCount);
	mMeshBuffer = new MeshBuffer[aModelData.meshCount];
	rootNode = mSceneManager.CreateEmptySceneNode();

	for (size_t i = 0; i < aModelData.materialCount; i++)
	{
		matNode[i] = mSceneManager.CreateMaterialNode(mMaterial[i]);
		rootNode->AddChild(matNode[i]);
	}
	for (size_t i = 0; i < aModelData.meshCount; i++)
	{
		skinMeshNode[i] = mSceneManager.CreateMeshNode();
		mMeshBuffer[i].Initialize(mSkinMesh[i], false);
		skinMeshNode[i]->SetRenderMesh(&mMeshBuffer[i]);
	}
	for (size_t i = 0; i < aModelData.textureCount; i++)
	{
		diffuseNode[i] = mSceneManager.CreateTextureNode();
		mTexture[i].Initialize(("../Assets/Textures/" + mDiffuseTexture[i]).c_str());
		diffuseNode[i]->SetTexture(&mTexture[i]);
		diffuseNode[i]->SetIndex(0);
	}
	for (size_t i = 0; i < mSkinMesh.size(); ++i)
	{
		matNode[mMaterialIndex[i]]->AddChild(diffuseNode[mMaterialIndex[i]]);
		diffuseNode[mMaterialIndex[i]]->AddChild(skinMeshNode[i]);
	}
}

void AnimationModel::Destroy()
{
	for (size_t i = 0; i < mSkinMesh.size(); i++)
	{
		mSkinMesh[i].Destroy();
	}
	if (mMeshBuffer)
	{
		for (size_t i = 0; i < mSkinMesh.size(); i++)
		{
			mMeshBuffer[i].Terminate();
		}
		SafeDeleteArray(mMeshBuffer);
	}
	for (auto& texture : mTexture)
	{
		texture.Terminate();
	}
	mDiffuseTexture.clear();
}