#include "Precompiled.h"
#include "Model.h"
#include "SceneNodeInc/MaterialNode.h"

using namespace SWGE;
using namespace Graphics;

struct ModelData
{
	uint32_t meshCount;
	uint32_t materialCount;
	uint32_t textureCount;
	uint32_t boneCount;
};

struct MeshData
{
	uint32_t vertexCount;
	uint32_t indexCount;
	uint32_t materialIndex;
	uint32_t boneCount;

};

Model::Model()
{
}

Model::~Model()
{
	ASSERT(mMeshBuffer == nullptr, "Did not terminate");
}
void Model::SaveModel(const char* filename)
{
	std::ofstream ofs(filename, std::ios::binary | std::ios::out);
	if (ofs.fail())
	{
		int i = 0;
	}
	ModelData modelData;
	modelData.meshCount = static_cast<uint32_t>(mMesh.size());
	modelData.materialCount = static_cast<uint32_t>(mMaterial.size());
	modelData.textureCount = static_cast<uint32_t>(mDiffuseTexture.size());
	
	ofs.write(reinterpret_cast<const char*>(&modelData), sizeof(ModelData));
	
	for (size_t i = 0; i < mMesh.size(); i++)
	{
		auto& mesh = mMesh[i];
		MeshData meshData;
		meshData.vertexCount = mesh.GetVertexCount();
		meshData.indexCount = mesh.GetIndexCount();
		meshData.materialIndex = mMaterialIndex[i];

		ofs.write(reinterpret_cast<char*>(&meshData), sizeof(MeshData));

		const auto vertices = mesh.GetVertices();
		ofs.write(reinterpret_cast<char*>(vertices), sizeof(*vertices) * mesh.GetVertexCount());

		const auto indices = mesh.GetIndices();
		ofs.write(reinterpret_cast<char*>(indices), sizeof(*indices) * mesh.GetIndexCount());
	}
	
	ofs.write(reinterpret_cast<char*>(mMaterial.data()), mMaterial.size() * sizeof(mMaterial[0]));

	for (auto& texture : mDiffuseTexture)
	{
		uint32_t size = static_cast<uint32_t>(texture.size());
		ofs.write(reinterpret_cast<char*>(&size), sizeof(uint32_t));
		ofs.write(texture.data(), texture.size());
	}
	
	ofs.close();
}

void Model::LoadModel(const char* filename)
{
	std::ifstream ifs(filename, std::ios::binary | std::ios::in);
	if (ifs.fail())
	{
		int i = 0;
	}
	ModelData modelData;
	ifs.read(reinterpret_cast<char*>(&modelData), sizeof(ModelData));

	mMesh.resize(modelData.meshCount);
	mMaterialIndex.resize(modelData.meshCount);
	mMaterial.resize(modelData.materialCount);
	mDiffuseTexture.resize(modelData.textureCount);

	for (size_t i = 0; i < modelData.meshCount; i++)
	{
		auto& mesh = mMesh[i];
		MeshData meshData;

		ifs.read(reinterpret_cast<char*>(&meshData), sizeof(MeshData));

		mesh.Allocate(meshData.vertexCount, meshData.indexCount);
		mMaterialIndex[i] = meshData.materialIndex;

		auto vertices = mesh.GetVertices();
		ifs.read(reinterpret_cast<char*>(mesh.GetVertices()), sizeof(*vertices) * mesh.GetVertexCount());

		auto indices = mesh.GetIndices();
		ifs.read(reinterpret_cast<char*>(mesh.GetIndices()), sizeof(*indices) * mesh.GetIndexCount());
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

	ifs.close();
}


void Model::Initialize(SceneManager& mSceneManager)
{
	ModelData modelData;
	modelData.meshCount = static_cast<uint32_t>(mMesh.size());
	modelData.materialCount = static_cast<uint32_t>(mMaterial.size());
	modelData.textureCount = static_cast<uint32_t>(mDiffuseTexture.size());

	std::vector<MeshNode*> meshNode;
	meshNode.resize(modelData.meshCount);
	std::vector<MaterialNode*> matNode;
	matNode.resize(modelData.materialCount);
	std::vector<TextureNode*> diffuseNode;
	diffuseNode.resize(modelData.textureCount);
	mTexture.resize(modelData.textureCount);
	mMeshBuffer = new MeshBuffer[modelData.meshCount];
	rootNode = mSceneManager.CreateEmptySceneNode();

	for (size_t i = 0; i < modelData.materialCount; i++)
	{
		matNode[i] = mSceneManager.CreateMaterialNode(mMaterial[i]);
		rootNode->AddChild(matNode[i]);
	}
	for (size_t i = 0; i < modelData.meshCount; i++)
	{
		meshNode[i] = mSceneManager.CreateMeshNode();
		mMeshBuffer[i].Initialize(mMesh[i], false);
		meshNode[i]->SetRenderMesh(&mMeshBuffer[i]);
	}
	for (size_t i = 0; i < modelData.textureCount; i++)
	{
		diffuseNode[i] = mSceneManager.CreateTextureNode();
		mTexture[i].Initialize(("../Assets/Textures/" + mDiffuseTexture[i]).c_str());
		diffuseNode[i]->SetTexture(&mTexture[i]);
		diffuseNode[i]->SetIndex(0);
	}
	for (size_t i = 0; i < mMesh.size();++i)
	{
		matNode[mMaterialIndex[i]]->AddChild(diffuseNode[mMaterialIndex[i]]);
		diffuseNode[mMaterialIndex[i]]->AddChild(meshNode[i]);
	}
}

void Model::Destroy()
{
	for (size_t i = 0; i < mMesh.size(); i++)
	{
		mMesh[i].Destroy();
	}
	if (mMeshBuffer)
	{
		for (size_t i = 0; i < mMesh.size(); i++)
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